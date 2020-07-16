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

bool SectionsManager::loadSection(const QString& path, Section *section)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)){
        return false;
    }
    SectionSettings parameters;

    QDataStream readStream(&file);
    readStream >> parameters;

    section->loadSettings(parameters);
    return true;
}

void SectionsManager::saveSectionToFile(QString& path, Section *section)
{
    SectionSettings parameters = section->getSettings();

    if(path.back() != '/') path.push_back('/');
    QString filename(path + parameters.section_name + ".section");

    QFile file(filename);
    if(!file.open(QFile::WriteOnly)){
        QMessageBox msgBox;
        msgBox.setText("Can't open file to save");
        msgBox.setInformativeText("File path:  " + filename);
        msgBox.exec();
        return;
    }
    QDataStream writeStream(&file);
    writeStream << parameters;

    file.close();
}

void SectionsManager::saveAllSectionsToFile(QString path)
{
    for(int i=0; i<=this->count(); i++){
        if(Section *section = qobject_cast<Section*>(widget(i))){
            saveSectionToFile(path, section);
        }
    }
}

void SectionsManager::removeSection(int index)
{
    this->widget(index)->deleteLater();
    removeTab(index);
}
