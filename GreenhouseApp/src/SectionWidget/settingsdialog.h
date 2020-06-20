#ifndef SECTIONSETTINGS_H
#define SECTIONSETTINGS_H

#include <QDialog>

namespace Ui {
class SectionSettings;
}

struct SectionSettings{
    quint8 sectionID = 0;
    QString picture_path;
    QString section_name = "Section";
    int temperature_expected = 0;
    int humidity_expected = 0;
    int insolation_expected = 0;
    int time_hours = 0;
    int time_minutes = 0;
};

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);

    void setParameters(const SectionSettings &sectionSettings);

    SectionSettings downloadParameters() const;

    ~SettingsDialog();

private:
    Ui::SectionSettings *ui;
};

#endif // SECTIONSETTINGS_H
