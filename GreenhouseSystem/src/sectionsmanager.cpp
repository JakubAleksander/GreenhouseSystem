#include "sectionsmanager.h"

SectionsManager::SectionsManager(QWidget *parent) : QTabWidget(parent)
{
    setTabsClosable(true);

    connect(this, &SectionsManager::tabCloseRequested, this, &SectionsManager::removeSection);
}

void SectionsManager::addSection(Section *section)
{
    addTab(section, section->getSectionName());
    sectionsMap.insert(indexOf(section), section);
    qDebug() << sectionsMap.size();
}

void SectionsManager::removeSection(int index)
{
    removeTab(index);
    sectionsMap.remove(index);
    delete widget(index-1);
    qDebug() << sectionsMap.size();
}
