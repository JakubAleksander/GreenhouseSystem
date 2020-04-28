#ifndef SECTION_H
#define SECTION_H

#include <QWidget>

namespace Ui {
class Section;
}

struct Current_parameter{
    quint8 id;
    int temperature;
    int insolation;
    int humidity;
    bool actual_pump_status;
    bool actual_light_status;
    bool actual_fan_status;
};

class Section : public QWidget
{
    Q_OBJECT

public:
    explicit Section(QWidget *parent = 0);
    ~Section();

private:
    Ui::Section *ui;
};

#endif // SECTION_H
