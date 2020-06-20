#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <QObject>
#include <QMqttClient>


/*!
 * \brief The MqttClient class
 */
class MqttClient : public QObject
{
    Q_OBJECT

  public:
    explicit MqttClient(QObject *parent = nullptr);
    void setParameters(quint8 id, quint8 temperature, quint8 insolation, quint8 humidity);

  signals:
    void signalConnected();
    void signalDisconnected();

  public slots:
		
  private slots:
    void slotConnected();
    void slotDisconnected();
    void slotStateChanged();
    void slotErrorChanged(const QMqttClient::ClientError e);

  private :
    QMqttClient *m_mqttClient { Q_NULLPTR };
};

#endif // MQTTCLIENT_H
