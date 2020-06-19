#include "section.h"
#include "ui_section.h"
#include "messenger.h"

Section::Section(Parameters& parameters, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Section), parameters(parameters)
{
    ui->setupUi(this);

    configUI();
    initDevices();

    current_parameter.id = parameters.sectionID;

    connect(SMessenger::instance(), &SMessenger::signalNewParamsFromGreenhouse, this, &Section::setReseivedParameters);
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
    SectionSettings* sectionSettings = new SectionSettings(this);
    sectionSettings->setParameters(parameters);

    if(sectionSettings->exec() == QDialog::Accepted){
        parameters = sectionSettings->downloadParameters();
        setTopicsForNewID(parameters.sectionID);
    }
    delete sectionSettings;
}

void Section::setReseivedParameters(Current_parameters parameters)
{
    if(this->parameters.sectionID == parameters.id ){
        ui->pb_watering->setValue(parameters.humidity);
        ui->pb_lighting->setValue(parameters.insolation);
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
    ui->btn_lighting->setIcon(QIcon(":/Icons/bulb-off.svg"));
    ui->btn_lighting->setCheckable(true);

    ui->btn_watering->setIcon(QIcon(":/Icons/droplet.svg"));
    ui->btn_watering->setCheckable(true);

    ui->btn_fan->setIcon(QIcon(":/Icons/file-plus.svg"));
    ui->btn_fan->setCheckable(true);
}

void Section::initDevices()
{
    pump = new Device(parameters.sectionID, false, "/Section" + QString::number(parameters.sectionID) + "/pump/");
    light = new Device(parameters.sectionID, false, "/Section" + QString::number(parameters.sectionID) + "/light/");
    fan = new Device(parameters.sectionID, false, "/Section" + QString::number(parameters.sectionID) + "/fan/");

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
        ui->btn_lighting->setIcon(QIcon(":/Icons/bulb.svg"));
        light->switchOn();
    }else{
        ui->btn_lighting->setIcon(QIcon(":/Icons/bulb-off.svg"));
        light->switchOff();
    }
}

void Section::on_btn_watering_toggled(bool checked)
{
    if(checked){
        ui->btn_watering->setIcon(QIcon(":/Icons/power.svg"));
        pump->switchOn();
    }else{
        ui->btn_watering->setIcon(QIcon(":/Icons/droplet.svg"));
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
