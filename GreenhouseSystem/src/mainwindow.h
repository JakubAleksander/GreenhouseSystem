#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMqttClient>

namespace Ui {
class MainWindow;
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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //Mqtt slots
    void slotErrorChanged(const QMqttClient::ClientError e);
    void slotStateChanged();
    void slotDisconnected();
    void slotConnected();

private:
    Ui::MainWindow *ui;

    QMqttClient *m_mqttClient;
};

#endif // MAINWINDOW_H
