#include "messenger.h"

Messenger::Messenger(QObject *parent): QMqttClient(parent)
{
    m_mqttClient = new QMqttClient();

    if (m_mqttClient) {
      m_mqttClient->setHostname("localhost");
      m_mqttClient->setPort(1883);
      m_mqttClient->setUsername("guest");
      m_mqttClient->setPassword("guest");

      connect(m_mqttClient, &QMqttClient::stateChanged, this, &Messenger::slotStateChanged);
      connect(m_mqttClient, &QMqttClient::disconnected, this, &Messenger::slotDisconnected);
      connect(m_mqttClient, &QMqttClient::connected, this, &Messenger::slotConnected);
      connect(m_mqttClient, &QMqttClient::errorChanged, this, &Messenger::slotErrorChanged);

      m_mqttClient->connectToHost();
    }
}

Messenger::~Messenger()
{
    delete m_mqttClient;
}

void Messenger::slotConnected()
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

void Messenger::sendMsgToDevice(QString topic, bool state)
{
    QString message = state? "OFF":"ON";
    m_mqttClient->publish(QMqttTopicName(topic), message.toUtf8());
}

void Messenger::slotDisconnected()
{
  qDebug() << Q_FUNC_INFO;
}

void Messenger::slotStateChanged()
{
  const QString content = QDateTime::currentDateTime().toString()
      + QLatin1String(": State Change : ")
      + QString::number(m_mqttClient->state());
  qDebug() << Q_FUNC_INFO << content;
}

void Messenger::slotErrorChanged(const QMqttClient::ClientError e)
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






SMessenger::SMessenger(QObject *parent) : QMqttClient(parent)
{
    m_mqttClient = new QMqttClient();

    if (m_mqttClient) {
      m_mqttClient->setHostname("localhost");
      m_mqttClient->setPort(1883);
      m_mqttClient->setUsername("guest");
      m_mqttClient->setPassword("guest");

      connect(m_mqttClient, &QMqttClient::stateChanged, this, &SMessenger::slotStateChanged);
      connect(m_mqttClient, &QMqttClient::disconnected, this, &SMessenger::slotDisconnected);
      connect(m_mqttClient, &QMqttClient::connected, this, &SMessenger::slotConnected);
      connect(m_mqttClient, &QMqttClient::errorChanged, this, &SMessenger::slotErrorChanged);

      m_mqttClient->connectToHost();
    }
}

void SMessenger::slotConnected()
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

void SMessenger::sendMsgToDevice(QString topic, bool state)
{
    QString message = state? "OFF":"ON";
    m_mqttClient->publish(QMqttTopicName(topic), message.toUtf8());
}

void SMessenger::slotDisconnected()
{
  qDebug() << Q_FUNC_INFO;
}

void SMessenger::slotStateChanged()
{
  const QString content = QDateTime::currentDateTime().toString()
      + QLatin1String(": State Change : ")
      + QString::number(m_mqttClient->state());
  qDebug() << Q_FUNC_INFO << content;
}

void SMessenger::slotErrorChanged(const QMqttClient::ClientError e)
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

SMessenger* SMessenger::instance_ = nullptr;
