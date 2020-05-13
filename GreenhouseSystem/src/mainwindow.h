#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "SectionWidget/section.h"
#include <QMqttClient>

namespace Ui {
class MainWindow;
}

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
