#include "device.h"
#include "messenger.h"

void Device::setTopic(QString new_topic){
    topic = new_topic;
}

void Device::switchOn()
{
    QString message = "ON";
    SMessenger::instance()->sendMessage(topic, message);
    status = true;
    emit statusChanged(QString("ON"));
}

void Device::switchOff()
{
    QString message = "OFF";
    SMessenger::instance()->sendMessage(topic, message);
    status = false;
    emit statusChanged(QString("OFF"));
}
