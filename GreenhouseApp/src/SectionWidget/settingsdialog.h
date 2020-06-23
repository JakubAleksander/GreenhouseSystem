#ifndef SECTIONSETTINGS_H
#define SECTIONSETTINGS_H

#include <QDialog>
#include <QFileDialog>

namespace Ui {
class SectionSettings;
}

struct SectionSettings{
    quint8 sectionID;
    QString section_name;
    QString picture_path;
    quint8 temperature_expected;
    quint8 humidity_expected;
    quint8 insolation_expected;
    quint8 time_hours;
    quint8 time_minutes;

    SectionSettings(quint8 id = 0,
                    QString name = "Section",
                    QString path = "",
                    quint8 temp = 0,
                    quint8 hum = 0,
                    quint8 ins = 0,
                    quint8 hours = 0,
                    quint8 minutes = 0)
         :sectionID(id),
          section_name(name),
          picture_path(path),
          temperature_expected(temp),
          humidity_expected(hum),
          insolation_expected(ins),
          time_hours(hours),
          time_minutes(minutes){}

    bool operator ==(const SectionSettings &s){
        if((this->sectionID == s.sectionID) &&
                (this->section_name == s.section_name) &&
                (this->picture_path == s.picture_path) &&
                (this->temperature_expected == s.temperature_expected) &&
                (this->humidity_expected == s.humidity_expected) &&
                (this->insolation_expected == s.insolation_expected) &&
                (this->time_hours == s.time_hours) &&
                (this->time_minutes == s.time_minutes)){
            return true;
        }else{
            return false;
        }
    }

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
