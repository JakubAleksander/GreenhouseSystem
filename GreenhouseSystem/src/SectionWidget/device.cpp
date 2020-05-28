#include "device.h"

void Device::setTopic(QString new_topic){
    topic = new_topic;
}

void Device::changeStatus(){
    status = !status;
}
