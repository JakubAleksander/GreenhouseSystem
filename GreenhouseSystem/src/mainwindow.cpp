#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_mqttClient = new QMqttClient(this);

    if (m_mqttClient) {
      m_mqttClient->setHostname("localhost");
      m_mqttClient->setPort(1883);
      m_mqttClient->setUsername("guest");
      m_mqttClient->setPassword("guest");

      connect(m_mqttClient, &QMqttClient::stateChanged, this, &MainWindow::slotStateChanged);
      connect(m_mqttClient, &QMqttClient::disconnected, this, &MainWindow::slotDisconnected);
      connect(m_mqttClient, &QMqttClient::connected, this, &MainWindow::slotConnected);
      connect(m_mqttClient, &QMqttClient::errorChanged, this, &MainWindow::slotErrorChanged);

      m_mqttClient->connectToHost();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotConnected()
{
  qDebug() << Q_FUNC_INFO;

  auto sub = m_mqttClient->subscribe(QMqttTopicFilter("/Greenhouse/data/"), 0);

  m_mqttClient->connect(sub, &QMqttSubscription::messageReceived, [this](const QMqttMessage &message) {
    if (message.payload().size() == sizeof(Current_parameters)) {
      Current_parameters param;
      memcpy(&param,&message.payload().data()[0],sizeof(param));
      qDebug() << Q_FUNC_INFO;
      qDebug() << "        id :" << param.id;
      qDebug() << "      Temp :" << param.temperature;
      qDebug() << "Insolation :" << param.insolation;
      qDebug() << "  Humidity :" << param.humidity;
      qDebug() << "\n";
      emit signalNewParamsFromGreenhouse(param);
    }
  });
}

void MainWindow::slotDisconnected()
{
  qDebug() << Q_FUNC_INFO;
}

void MainWindow::slotStateChanged()
{
  const QString content = QDateTime::currentDateTime().toString()
      + QLatin1String(": State Change : ")
      + QString::number(m_mqttClient->state());
  qDebug() << Q_FUNC_INFO << content;
}

void MainWindow::slotErrorChanged(const QMqttClient::ClientError e)
{
  if (e == QMqttClient::NoError) {
    return;
  }

  qDebug() << Q_FUNC_INFO;
  switch (e) {
    case QMqttClient::NoError                :  qDebug() << "NoError"; break;
    case QMqttClient::InvalidProtocolVersion :  qDebug() << "InvalidProtocolVersion";break;
    case QMqttClient::IdRejected             :  qDebug() << "IdRejected";break;
    case QMqttClient::ServerUnavailable      :  qDebug() << "ServerUnavailable";break;
    case QMqttClient::BadUsernameOrPassword  :  qDebug() << "BadUsernameOrPassword";break;
    case QMqttClient::NotAuthorized          :  qDebug() << "NotAuthorized";break;
    case QMqttClient::TransportInvalid       :  qDebug() << "TransportInvalid";break;
    case QMqttClient::ProtocolViolation      :  qDebug() << "ProtocolViolation";break;
    case QMqttClient::UnknownError           :  qDebug() << "UnknownError"; break;
    case QMqttClient::Mqtt5SpecificError     :  qDebug() << "Mqtt5SpecificError";break;
  }

  qWarning() << "Error Occurred:" << e << " Client state :" << m_mqttClient->state();
  m_mqttClient->disconnectFromHost();
}

void MainWindow::on_btn_addSection_clicked()
{
    Parameters parameters;

    SectionSettings* sectionSettings = new SectionSettings(this);
    sectionSettings->setParameters(parameters);

    if(sectionSettings->exec() == QDialog::Accepted){
        parameters = sectionSettings->downloadParameters();
        Section *section = new Section(parameters);
        connect(this, &MainWindow::signalNewParamsFromGreenhouse, section, &Section::setReseivedParameters);
        ui->tabSections->addTab(section, parameters.section_name);
    }
    delete sectionSettings;
}

void MainWindow::on_btn_quit_clicked()
{
    QApplication::quit();
}
