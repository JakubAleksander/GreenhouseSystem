#ifndef MESSENGER_H
#define MESSENGER_H

#include <QMqttClient>

#include "SectionWidget/section.h"

class SMessenger : public QMqttClient
{
    Q_OBJECT
public:
    static void createInstance(){
        if(instance_ == nullptr) instance_= new SMessenger();
    }

    static SMessenger* instance(){
        if(instance_ == nullptr) createInstance();
        return instance_;
    }

public slots:
    void sendMsgToDevice(QString topic, bool state);

protected:
    SMessenger(QObject *parent = nullptr);

private:
    static SMessenger* instance_;
    QMqttClient *m_mqttClient;

private slots:
    void slotErrorChanged(const QMqttClient::ClientError e);
    void slotStateChanged();
    void slotDisconnected();
    void slotConnected();

signals:
    void signalNewParamsFromGreenhouse(Current_parameters parameters);
};

#endif // MESSENGER_H
