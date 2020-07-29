#include "testsection.h"

void TestSection::testSectionConstructor()
{
    SectionSettings settings;
    Section section(settings);

    QVERIFY(section.getSettings() == settings);
}

QTEST_MAIN(TestSection)
