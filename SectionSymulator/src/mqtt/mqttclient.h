#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <QObject>
#include <QMqttClient>


struct Current_parameter{
    quint8 id;
    int temperature;
    int insolation;
    int humidity;
    bool actual_pump_status;
    bool actual_light_status;
    bool actual_fan_status;
};

/*!
 * \brief The MqttClient class
 */
class MqttClient : public QObject
{
    Q_OBJECT

  public:
    explicit MqttClient(QObject *parent = nullptr);
    void setParameters(
      quint8 id,
      int temperature,
      int insolation,
      int humidity,
      bool actual_pump_status,
      bool actual_light_status,
      bool actual_fan_status
    );

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
