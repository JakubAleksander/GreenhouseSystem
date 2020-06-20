#include "mqttclient.h"
#include <QDateTime>
#include <QDebug>

#include "../../../GreenhouseSystem/src/SectionWidget/section.h"

MqttClient::MqttClient(QObject *parent) : QObject(parent)
{
  m_mqttClient = new QMqttClient(this);
  if (m_mqttClient) {
    m_mqttClient->setHostname("localhost");
    m_mqttClient->setPort(1883);
    m_mqttClient->setUsername("guest");
    m_mqttClient->setPassword("guest");

    connect(m_mqttClient, &QMqttClient::stateChanged, this, &MqttClient::slotStateChanged);
    connect(m_mqttClient, &QMqttClient::disconnected, this, &MqttClient::slotDisconnected);
    connect(m_mqttClient, &QMqttClient::connected, this, &MqttClient::slotConnected);
    connect(m_mqttClient, &QMqttClient::errorChanged, this, &MqttClient::slotErrorChanged);


    m_mqttClient->connectToHost();
  }
}

void MqttClient::setParameters(quint8 id, quint8 temperature, quint8 insolation, quint8 humidity)
{
  if (m_mqttClient) {
    Current_parameters param;
    param.id = id;
    param.temperature = temperature;
    param.insolation = insolation;
    param.humidity = humidity;

    m_mqttClient->publish(QMqttTopicName("/Greenhouse/data/"),
                          QByteArray(reinterpret_cast<char *>(&param), sizeof(param)));
  }
}

/*!
 * \brief MqttClient::slotConnected
 */
void MqttClient::slotConnected()
{
  qDebug() << Q_FUNC_INFO;
  emit signalConnected();
}

/*!
 * \brief MqttClient::slotDisconnected
 */
void MqttClient::slotDisconnected()
{
  qDebug() << Q_FUNC_INFO;
  emit signalDisconnected();
}

/*!
 * \brief MqttClient::slotStateChanged
 */
void MqttClient::slotStateChanged()
{
  const QString content = QDateTime::currentDateTime().toString()
      + QLatin1String(": State Change : ")
      + QString::number(m_mqttClient->state());
  qDebug() << Q_FUNC_INFO << content;
}

/*!
 * \brief MqttClient::slotErrorChanged
 * \param e
 */
void MqttClient::slotErrorChanged(const QMqttClient::ClientError e)
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
