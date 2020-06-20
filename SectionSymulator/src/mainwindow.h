#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDateTime>
#include "mqttclient.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = Q_NULLPTR);
    ~MainWindow();

  private:
    Ui::MainWindow *ui;
    QTimer * m_tm1s {Q_NULLPTR};
    quint32 m_cnt {0};
    MqttClient * m_mqttClient { Q_NULLPTR };

  private slots :
    void slotTm1s();
    void on_btnStart_clicked();
    void slotBtnStop();
};

#endif // MAINWINDOW_H
