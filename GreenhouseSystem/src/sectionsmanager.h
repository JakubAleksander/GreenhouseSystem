#ifndef SECTIONSMANAGER_H
#define SECTIONSMANAGER_H

#include <QTableWidget>
#include <QDebug>
#include <QMap>

#include "SectionWidget/section.h"

class SectionsManager : public QTabWidget
{
public:
    SectionsManager(QWidget *parent = 0);

    void addSection(Section *section);

    void saveSectionToFile(QString path, Section *section);

    void saveAllSectionsToFile(QString path);

private:

private slots:
    void removeSection(int index);
};

#endif // SECTIONSMANAGER_H
