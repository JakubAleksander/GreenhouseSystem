#include "section.h"
#include "ui_section.h"

Section::Section(Parameters& parameters, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Section), parameters(parameters)
{
    ui->setupUi(this);
    configUI();

    current_parameter.id = parameters.sectionID;

    pump = new Device(parameters.sectionID, false, "/Section" + QString::number(parameters.sectionID) + "/pump/");
    light = new Device(parameters.sectionID, false, "/Section" + QString::number(parameters.sectionID) + "/light/");
    fan = new Device(parameters.sectionID, false, "/Section" + QString::number(parameters.sectionID) + "/fan/");

    connect(pump, &Device::statusChanged, ui->lbl_pumpStatus, &QLabel::setText);
    connect(light, &Device::statusChanged, ui->lbl_lightStatus, &QLabel::setText);
    connect(fan, &Device::statusChanged, ui->lbl_fanStatus, &QLabel::setText);
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

void Section::on_btn_lighting_toggled(bool checked)
{
    if(checked){
        ui->btn_lighting->setIcon(QIcon(":/Icons/bulb.svg"));
    }else{
        ui->btn_lighting->setIcon(QIcon(":/Icons/bulb-off.svg"));
    }

    light->changeStatus(checked);
    emit requestSwitchDevice(light->getTopic(), !light->actualStatus());
}

void Section::on_btn_watering_toggled(bool checked)
{
    if(checked){
        ui->btn_watering->setIcon(QIcon(":/Icons/power.svg"));
    }else{
        ui->btn_watering->setIcon(QIcon(":/Icons/droplet.svg"));
    }

    pump->changeStatus(checked);
    emit requestSwitchDevice(pump->getTopic(), !pump->actualStatus());
}

void Section::on_btn_fan_toggled(bool checked)
{
    if(checked){
        ui->btn_fan->setIcon(QIcon(":/Icons/power.svg"));
    }else{
        ui->btn_fan->setIcon(QIcon(":/Icons/droplet.svg"));
    }

    fan->changeStatus(checked);
    emit requestSwitchDevice(fan->getTopic(), !fan->actualStatus());
}
