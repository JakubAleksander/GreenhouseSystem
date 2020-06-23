#include "section.h"
#include "ui_section.h"
#include "../messenger.h"

Section::Section(SectionSettings& parameters, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Section), sectionSettings(parameters)
{
    ui->setupUi(this);

    configUI();
    initDevices();

    greenhouseData.id = parameters.sectionID;

    connect(Messenger::instance(), &Messenger::signalNewParamsFromGreenhouse, this, &Section::setReseivedParameters);
}

void Section::setPicture(const QString &path)
{
    QPixmap picture(path);
    int labelWidth=(ui->lbl_picture->width());
    int labelHeight=(ui->lbl_picture->height());
    ui->lbl_picture->setPixmap(picture.scaled(labelWidth, labelHeight, Qt::KeepAspectRatio));
}

Section::~Section()
{
    delete ui;
    delete pump;
    delete light;
    delete fan;
}

void Section::on_btn_settings_clicked()
{
    SettingsDialog* settingsDialog = new SettingsDialog(this);
    settingsDialog->setParameters(sectionSettings);

    if(settingsDialog->exec() == QDialog::Accepted){
        sectionSettings = settingsDialog->downloadParameters();
        setTopicsForNewID(sectionSettings.sectionID);
        setPicture(sectionSettings.picture_path);
    }
    delete settingsDialog;
}

void Section::setReseivedParameters(const GreenhouseData& data)
{
    if(sectionSettings.sectionID == data.id ){
        ui->lbl_actualTemp->setText(QString::number(data.temperature)+" °C");
        ui->lbl_actualHumidity->setText(QString::number(data.humidity) + " %");
        ui->lbl_actualInsolation->setText(QString::number(data.insolation) + " %");
    }
}

void Section::setTopicsForNewID(quint8 ID)
{
    pump->setTopic("/Section" + QString::number(ID) + "/pump/");
    light->setTopic("/Section" + QString::number(ID) + "/light/");
    fan->setTopic("/Section" + QString::number(ID) + "/fan/");
}

void Section::configUI()
{
    ui->btn_lighting->setIcon(QIcon(":/Icons/section_lighting_off.svg"));
    ui->btn_lighting->setCheckable(true);

    ui->btn_watering->setIcon(QIcon(":/Icons/section_watering_off.svg"));
    ui->btn_watering->setCheckable(true);

    ui->btn_fan->setIcon(QIcon(""));
    ui->btn_fan->setCheckable(true);
}

void Section::initDevices()
{
    pump = new Device(sectionSettings.sectionID, false, "/Section" + QString::number(sectionSettings.sectionID) + "/pump/");
    light = new Device(sectionSettings.sectionID, false, "/Section" + QString::number(sectionSettings.sectionID) + "/light/");
    fan = new Device(sectionSettings.sectionID, false, "/Section" + QString::number(sectionSettings.sectionID) + "/fan/");

    connect(pump, &Device::statusChanged, ui->lbl_pumpStatus, &QLabel::setText);
    connect(light, &Device::statusChanged, ui->lbl_lightStatus, &QLabel::setText);
    connect(fan, &Device::statusChanged, ui->lbl_fanStatus, &QLabel::setText);

    pump->switchOff();
    light->switchOff();
    fan->switchOff();
}

void Section::on_btn_lighting_toggled(bool checked)
{
    if(checked){
        ui->btn_lighting->setIcon(QIcon(":/Icons/section_lighting_on.svg"));
        light->switchOn();
    }else{
        ui->btn_lighting->setIcon(QIcon(":/Icons/section_lighting_off.svg"));
        light->switchOff();
    }
}

void Section::on_btn_watering_toggled(bool checked)
{
    if(checked){
        ui->btn_watering->setIcon(QIcon(":/Icons/section_watering_on.svg"));
        pump->switchOn();
    }else{
        ui->btn_watering->setIcon(QIcon(":/Icons/section_watering_off.svg"));
        pump->switchOff();
    }
}

void Section::on_btn_fan_toggled(bool checked)
{
    if(checked){
        ui->btn_fan->setIcon(QIcon(":/Icons/power.svg"));
        fan->switchOn();
    }else{
        ui->btn_fan->setIcon(QIcon(":/Icons/droplet.svg"));
        fan->switchOff();
    }
}
