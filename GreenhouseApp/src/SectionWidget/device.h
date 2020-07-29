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
    const QString getTopic(){return topic;}
    void setTopic(const QString& new_topic);
    void switchOn();
    void switchOff();

signals:
    void statusChanged(const QString& str_status);

private:
    quint8 id;
    bool status;
    QString topic;
};

#endif // DEVICE_H
