#include "testsection.h"

void TestSection::testConstructor()
{
    SectionSettings settings;
    Section sections(settings);
}

QTEST_MAIN(TestSection)
