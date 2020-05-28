#include "section.h"
#include "ui_section.h"

Section::Section(Parameters& parameters, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Section), parameters(parameters)
{
    ui->setupUi(this);
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

void Section::on_btn_watering_clicked()
{
    emit requestSwitchDevice(pump->getTopic(), !pump->actualStatus());
    pump->changeStatus();
}
