#include "settingsdialog.h"
#include "ui_sectionsettings.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SectionSettings)
{
    ui->setupUi(this);
}

void SettingsDialog::setParameters(const SectionSettings &sectionSettings)
{
    ui->le_sectionName->setText(sectionSettings.section_name);
    ui->sb_id->setValue(sectionSettings.sectionID);
    ui->lbl_fotoPath->setText(sectionSettings.picture_path);
    ui->sb_timeHours->setValue(sectionSettings.time_hours);
    ui->sb_timeMinutes->setValue(sectionSettings.time_minutes);
    ui->sb_maxTemp->setValue(sectionSettings.temperature_expected);
    ui->sb_minHum->setValue(sectionSettings.humidity_expected);
    ui->sb_minIns->setValue(sectionSettings.insolation_expected);
}

SectionSettings SettingsDialog::downloadParameters() const
{
    SectionSettings sectionSettings;
    sectionSettings.section_name = ui->le_sectionName->text();
    sectionSettings.sectionID = ui->sb_id->value();
    sectionSettings.picture_path = ui->lbl_fotoPath->text();
    sectionSettings.time_hours = ui->sb_timeHours->value();
    sectionSettings.time_minutes = ui->sb_timeMinutes->value();
    sectionSettings.temperature_expected = ui->sb_maxTemp->value();
    sectionSettings.humidity_expected = ui->sb_minHum->value();
    sectionSettings.insolation_expected = ui->sb_minIns->value();
    return sectionSettings;
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_toolButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Choose foto"), "$HOME",
                                                tr("Image Files (*.png *.jpg *.bmp)"));
    ui->lbl_fotoPath->setText(path);
}
