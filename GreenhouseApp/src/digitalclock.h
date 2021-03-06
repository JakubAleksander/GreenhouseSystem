#ifndef DIGITALCLOCK_H
#define DIGITALCLOCK_H

#include <QTime>
#include <QTimer>
#include <QLCDNumber>

class DigitalClock : public QLCDNumber
{
    Q_OBJECT
public:
    explicit DigitalClock(QWidget *parent = nullptr);

private slots:
    void showTime();
};

#endif // DIGITALCLOCK_H
