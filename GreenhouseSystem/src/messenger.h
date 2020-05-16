#ifndef MESSSENGER_H
#define MESSSENGER_H

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

signals:
    void signalNewParamsFromGreenhouse(Current_parameters parameters);

private:
    QMqttClient *m_mqttClient;
};

#endif // MESSSENGER_H
