#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  m_tm1s = new QTimer(this);
  if (m_tm1s) {
    connect(m_tm1s, &QTimer::timeout,
            this,&MainWindow::slotTm1s);
    m_tm1s->setInterval(1000);
  }
  connect(ui->btnStop, SIGNAL(clicked()),
          this, SLOT(slotBtnStop()));

  m_mqttClient = new MqttClient(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::slotTm1s()
{
  qDebug() << Q_FUNC_INFO;
  if (m_mqttClient) {
    m_mqttClient->setParameters(quint8(ui->edId->value()),
                                ui->edTemp->value(),
                                ui->edInsolation->value(),
                                ui->edHumid->value(),
                                ui->cbPump->isChecked(),
                                ui->cbLight->isChecked(),
                                ui->cbFan->isChecked()
                                );

  }
}

void MainWindow::on_btnStart_clicked()
{
  if (m_tm1s) {
    if (!m_tm1s->isActive())
      m_tm1s->start();
  }
}

void MainWindow::slotBtnStop()
{
  if (m_tm1s) {
    if (m_tm1s->isActive())
      m_tm1s->stop();
  }
}
