#ifndef TESTSECTION_H
#define TESTSECTION_H

#include <QtTest>
#include <QCoreApplication>

#include "../../GreenhouseApp/src/SectionWidget/section.h"

class TestSection : public QObject
{
    Q_OBJECT

private slots:
    void testConstructor();
};

#endif // TESTSECTION_H
