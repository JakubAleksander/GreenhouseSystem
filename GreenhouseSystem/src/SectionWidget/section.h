#ifndef SECTION_H
#define SECTION_H

#include <QWidget>

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
    explicit Section(quint8 id, QWidget *parent = 0);
    ~Section();

private slots:
    void on_btn_settings_clicked();

public slots:
    void setReseivedParameters(Current_parameters parameters);

private:
    Ui::Section *ui;
    Current_parameters *current_parameter;
    quint8 id;
};

#endif // SECTION_H
