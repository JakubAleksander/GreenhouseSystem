#include "section.h"
#include "ui_section.h"

Section::Section(Parameters& parameters, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Section), parameters(parameters)
{
    ui->setupUi(this);
    current_parameter.id = parameters.sectionID;
}

Section::~Section()
{
    delete ui;
}

void Section::on_btn_settings_clicked()
{
    SectionSettings* sectionSettings = new SectionSettings(this);
    sectionSettings->setParameters(parameters);

    if(sectionSettings->exec() == QDialog::Accepted){
        parameters = sectionSettings->downloadParameters();
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
