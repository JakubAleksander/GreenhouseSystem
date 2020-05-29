#include "device.h"

void Device::setTopic(QString new_topic){
    topic = new_topic;
}

void Device::changeStatus(){
    status = !status;
    QString str_status = status? "ON":"OFF";
    emit statusChanged(str_status);
}
