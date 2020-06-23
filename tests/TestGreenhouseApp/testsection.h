#ifndef TESTSECTION_H
#define TESTSECTION_H

#include <QtTest>
#include <QCoreApplication>
#include <QtWidgets>
#include <QMqttClient>

#include "../../GreenhouseApp/src/SectionWidget/section.h"

class TestSection : public QObject
{
    Q_OBJECT

private slots:
    void testSectionConstructor();
};

#endif // TESTSECTION_H
