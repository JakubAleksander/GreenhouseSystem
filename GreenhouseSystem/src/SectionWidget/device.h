#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>

class Device : public QObject
{
    Q_OBJECT
public:
    Device(quint8 id, bool status, QString topic)
        : id(id), status(status), topic(topic){}

    bool actualStatus(){return status;}

    QString getTopic(){return topic;}

    void setTopic(QString new_topic);

    void changeStatus(const bool new_status);

signals:
    void statusChanged(QString str_status);

private:
    quint8 id;
    bool status;
    QString topic;
};

#endif // DEVICE_H
