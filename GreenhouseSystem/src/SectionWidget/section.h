#ifndef SECTION_H
#define SECTION_H

#include <QWidget>
#include <QString>

#include "sectionsettings.h"
#include "device.h"

namespace Ui {
class Section;
}

struct Current_parameters{
    quint8 id;
    int temperature;
    int insolation;
    int humidity;
    bool pump_status;
    bool light_status;
    bool fan_status;
};

class Section : public QWidget
{
    Q_OBJECT

public:
    explicit Section(Parameters& parameters, QWidget *parent = 0);

    QString getSectionName(){return parameters.section_name;}

    Parameters getParameters(){return parameters;}

    void loadParameters(Parameters& p){parameters = p;}

    ~Section();

private slots:
    void on_btn_settings_clicked();

    void on_btn_lighting_toggled(bool checked);

    void on_btn_watering_toggled(bool checked);

    void on_btn_fan_toggled(bool checked);

public slots:
    void setReseivedParameters(Current_parameters parameters);

signals:
    void requestSwitchDevice(QString topic, bool state);

private:
    Ui::Section *ui;
    Current_parameters current_parameter;
    Parameters parameters;
    Device *pump;
    Device *light;
    Device *fan;

    void setTopicsForNewID(quint8 ID);
    void configUI();
};

#endif // SECTION_H
