#include "sectionsmanager.h"

SectionsManager::SectionsManager(QWidget *parent) : QTabWidget(parent)
{
    setTabsClosable(true);

    connect(this, &SectionsManager::tabCloseRequested, this, &SectionsManager::removeSection);
}

void SectionsManager::addSection(Section *section)
{
    addTab(section, section->getSectionName());
    sectionsMap.insert(indexOf(section),section);
    qDebug() << sectionsMap.size();
}

void SectionsManager::removeSection(int index)
{
    delete widget(index);
    removeTab(index);
    sectionsMap.remove(index);
    qDebug() << sectionsMap.size();
}
