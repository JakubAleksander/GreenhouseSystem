#ifndef SECTION_H
#define SECTION_H

#include <QWidget>
#include <QString>

#include "sectionsettings.h"
#include "device.h"

namespace Ui {
class Section;
}

struct GreenhouseData{
    quint8 id;
    quint8 temperature;
    quint8 insolation;
    quint8 humidity;
};

class Section : public QWidget
{
    Q_OBJECT

public:
    explicit Section(SectionSettings& sectionSettings, QWidget *parent = nullptr);

    QString getSectionName(){return sectionSettings.section_name;}

    SectionSettings getParameters(){return sectionSettings;}

    void loadParameters(SectionSettings& newSettings){sectionSettings = newSettings;}

    ~Section();

private slots:
    void on_btn_settings_clicked();

    void on_btn_lighting_toggled(bool checked);

    void on_btn_watering_toggled(bool checked);

    void on_btn_fan_toggled(bool checked);

public slots:
    void setReseivedParameters(const GreenhouseData& data);

signals:
    void requestSwitchDevice(const QString& topic, const bool state);

private:
    Ui::Section *ui;
    GreenhouseData greenhouseData;
    SectionSettings sectionSettings;
    Device *pump;
    Device *light;
    Device *fan;

    void setTopicsForNewID(quint8 ID);
    void configUI();
    void initDevices();
};

#endif // SECTION_H
