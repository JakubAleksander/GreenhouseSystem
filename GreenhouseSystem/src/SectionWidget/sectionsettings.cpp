#include "sectionsettings.h"
#include "ui_sectionsettings.h"

SectionSettings::SectionSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SectionSettings)
{
    ui->setupUi(this);
}

void SectionSettings::setParameters(const Parameters &parameters)
{
    ui->le_sectionName->setText(parameters.section_name);
    ui->sb_id->setValue(parameters.sectionID);
    ui->sb_timeHours->setValue(parameters.time_hours);
    ui->sb_timeMinutes->setValue(parameters.time_minutes);
    ui->sb_maxTemp->setValue(parameters.temperature_expected);
    ui->sb_minHum->setValue(parameters.humidity_expected);
    ui->sb_minIns->setValue(parameters.insolation_expected);
}

Parameters SectionSettings::downloadParameters() const
{
    Parameters parameters;
    parameters.section_name = ui->le_sectionName->text();
    parameters.sectionID = ui->sb_id->value();
    parameters.time_hours = ui->sb_timeHours->value();
    parameters.time_minutes = ui->sb_timeMinutes->value();
    parameters.temperature_expected = ui->sb_maxTemp->value();
    parameters.humidity_expected = ui->sb_minHum->value();
    parameters.insolation_expected = ui->sb_minIns->value();
    return parameters;
}

SectionSettings::~SectionSettings()
{
    delete ui;
}
