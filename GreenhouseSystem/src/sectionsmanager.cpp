#include "sectionsmanager.h"

SectionsManager::SectionsManager(QWidget *parent) : QTabWidget(parent)
{
    setTabsClosable(true);
    setMovable(true);

    connect(this, &SectionsManager::tabCloseRequested, this, &SectionsManager::removeSection);
}

void SectionsManager::addSection(Section *section)
{
    addTab(section, section->getSectionName());
}

void SectionsManager::saveSectionToFile(QString path, Section *section)
{

}

void SectionsManager::saveAllSectionsToFile(QString path)
{
    for(int i=this->count(); i>0; i--){
        Section *section = qobject_cast<Section*>(widget(i));
        saveSectionToFile(path, section);
    }
}

void SectionsManager::removeSection(int index)
{
    this->widget(index)->deleteLater();
    removeTab(index);
}
