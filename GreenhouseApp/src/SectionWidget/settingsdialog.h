#ifndef SECTIONSETTINGS_H
#define SECTIONSETTINGS_H

#include <QDialog>
#include <QFileDialog>

namespace Ui {
class SectionSettings;
}

struct SectionSettings{
    quint8 sectionID = 0;
    QString section_name = "Section";
    QString picture_path;
    quint8 temperature_expected = 0;
    quint8 humidity_expected = 0;
    quint8 insolation_expected = 0;
    quint8 time_hours = 0;
    quint8 time_minutes = 0;
};

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);

    void setParameters(const SectionSettings &sectionSettings);

    SectionSettings downloadParameters() const;

    ~SettingsDialog();

private slots:
    void on_toolButton_clicked();

private:
    Ui::SectionSettings *ui;
};

#endif // SECTIONSETTINGS_H
