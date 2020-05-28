#ifndef MESSENGER_H
#define MESSENGER_H

#include <QMqttClient>

#include "SectionWidget/section.h"

class Messenger : public QMqttClient
{
    Q_OBJECT
public:
    Messenger(QObject *parent = nullptr);

    ~Messenger();

private slots:
    void slotErrorChanged(const QMqttClient::ClientError e);
    void slotStateChanged();
    void slotDisconnected();
    void slotConnected();

public slots:
    void sendMsgToDevice(QString topic, bool state);

signals:
    void signalNewParamsFromGreenhouse(Current_parameters parameters);

private:
    QMqttClient *m_mqttClient;
};

#endif // MESSENGER_H