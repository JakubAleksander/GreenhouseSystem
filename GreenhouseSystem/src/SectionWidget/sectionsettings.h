#ifndef SECTIONSETTINGS_H
#define SECTIONSETTINGS_H

#include <QDialog>

namespace Ui {
class SectionSettings;
}

struct Parameters{
    int sectionID = 0;
    QString picture_path;
    QString section_name = "Section";
    int temperature_expected = 0;
    int humidity_expected = 0;
    int insolation_expected = 0;
    int time_hours = 0;
    int time_minutes = 0;
};

class SectionSettings : public QDialog
{
    Q_OBJECT

public:
    explicit SectionSettings(QWidget *parent = 0);

    void setParameters(const Parameters &parameters);

    Parameters downloadParameters() const;

    ~SectionSettings();

private:
    Ui::SectionSettings *ui;
};

#endif // SECTIONSETTINGS_H
