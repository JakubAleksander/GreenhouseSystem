#include "device.h"
#include "../messenger.h"

void Device::setTopic(const QString& new_topic){
    topic = new_topic;
}

void Device::switchOn()
{
    QString message = "ON";
    Messenger::instance()->sendMessage(topic, message);
    status = true;
    emit statusChanged(QString("ON"));
}

void Device::switchOff()
{
    QString message = "OFF";
    Messenger::instance()->sendMessage(topic, message);
    status = false;
    emit statusChanged(QString("OFF"));
}
