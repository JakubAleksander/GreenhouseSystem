#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include "SectionWidget/section.h"
#include <QMqttClient>
#include <QMap>
#include "digitalclock.h"
#include "sectionsmanager.h"

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

    void on_btn_addSection_clicked();

    void on_btn_quit_clicked();

signals:
    void signalNewParamsFromGreenhouse(Current_parameters parameters);

private:
    Ui::MainWindow *ui;

    QMqttClient *m_mqttClient;
    QMap<quint8, Section*>sections;

};

#endif // MAINWINDOW_H
