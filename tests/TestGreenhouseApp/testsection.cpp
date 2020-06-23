#include "testsection.h"

void TestSection::testSectionConstructor()
{
    SectionSettings settings;
    Section section(settings);

    QVERIFY(section.getParameters() == settings);
}

QTEST_MAIN(TestSection)
