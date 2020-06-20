#ifndef MESSENGER_H
#define MESSENGER_H

#include <QMqttClient>

#include "SectionWidget/section.h"

class Messenger : public QMqttClient
{
    Q_OBJECT
public:
    static void createInstance(){
        if(instance_ == nullptr) instance_= new Messenger();
    }

    static Messenger* instance(){
        if(instance_ == nullptr) createInstance();
        return instance_;
    }

public slots:
    void sendMessage(QString topic, QString message);

protected:
    Messenger(QObject *parent = nullptr);

private:
    static Messenger* instance_;
    QMqttClient *m_mqttClient;

private slots:
    void slotErrorChanged(const QMqttClient::ClientError e);
    void slotStateChanged();
    void slotDisconnected();
    void slotConnected();

signals:
    void signalNewParamsFromGreenhouse(GreenhouseData parameters);
};

#endif // MESSENGER_H
