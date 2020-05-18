#ifndef SECTION_H
#define SECTION_H

#include <QWidget>

#include "sectionsettings.h"

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
    QString getSectionName();
    Parameters getParameter();
    ~Section();

private slots:
    void on_btn_settings_clicked();

public slots:
    void setReseivedParameters(Current_parameters parameters);

private:
    Ui::Section *ui;
    Current_parameters current_parameter;
    Parameters parameters;
};

#endif // SECTION_H
