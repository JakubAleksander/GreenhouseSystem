#ifndef SECTIONSMANAGER_H
#define SECTIONSMANAGER_H

#include <QTableWidget>
#include <QDebug>
#include <QMap>
#include <QFile>
#include "QMessageBox"
#include "QDataStream"

#include "SectionWidget/section.h"

inline QDataStream &operator<<(QDataStream& out, const Parameters& p){
return out << p.sectionID << p.picture_path << p.section_name << p.temperature_expected
           << p.humidity_expected << p.insolation_expected << p.time_hours << p.time_minutes;
}
inline QDataStream &operator>>(QDataStream& in, Parameters& p){
return in >> p.sectionID >> p.picture_path >> p.section_name >> p.temperature_expected
          >> p.humidity_expected >> p.insolation_expected >> p.time_hours >> p.time_minutes;
}

class SectionsManager : public QTabWidget
{
public:
    SectionsManager(QWidget *parent = 0);

    void addSection(Section *section);

    bool loadSection(QString path, Section *section);

    void saveSectionToFile(QString path, Section *section);

    void saveAllSectionsToFile(QString path);

private:

private slots:
    void removeSection(int index);
};

#endif // SECTIONSMANAGER_H
