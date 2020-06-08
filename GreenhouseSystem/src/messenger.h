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



class SMessenger : public QMqttClient
{
    Q_OBJECT
public:
    static SMessenger* instance(){
        if(!instance_) instance_ = new SMessenger();
        assert(instance_ != NULL);
        return instance_;
    }
public slots:
    void sendMsgToDevice(QString topic, bool state);

protected:
    SMessenger(QObject *parent = nullptr);
private:
    //SMessenger(SMessenger const&);
    //SMessenger& operator=(SMessenger const&);

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
