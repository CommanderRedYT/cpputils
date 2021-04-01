#include <QtTest>
#include <QDebug>
#include <QByteArray>

#include <chrono>
#include <string>
#include <algorithm>

#include "cpputilstestutils.h"
#include "cppbitmask.h"

class TstCppBitmask : public QObject
{
    Q_OBJECT

private slots:
    void test_basic_functionality()
    {
        constexpr cpputils::bit_pattern pattern{"10XXX10"};
        QCOMPARE(pattern.expected, 0b1000010);
        QCOMPARE(pattern.mask, 0b1100011);
        QVERIFY(pattern.match(0b1001010));
        QVERIFY(pattern.match(0b1010110));
        QVERIFY(!pattern.match(0b1000000));
        QVERIFY(!pattern.match(0b1100010));
    }

    void test_copy()
    {
        const cpputils::bit_pattern pattern{"10XXX10"};
        const cpputils::bit_pattern patternCopy{pattern};
        QCOMPARE(patternCopy.expected, 0b1000010);
        QCOMPARE(patternCopy.mask, 0b1100011);
    }

    void test_assign()
    {
        const cpputils::bit_pattern pattern{"10XXX10"};
        cpputils::bit_pattern patternCopy{"11110000XXXX"};
        QCOMPARE(patternCopy.expected, 0b111100000000);
        QCOMPARE(patternCopy.mask, 0b111111110000);
        patternCopy = pattern;
        QCOMPARE(patternCopy.expected, 0b1000010);
        QCOMPARE(patternCopy.mask, 0b1100011);
    }

    void test_swap()
    {
        cpputils::bit_pattern pattern0{"10XXX10"};
        cpputils::bit_pattern pattern1{"11110000XXXX"};

        QCOMPARE(pattern0.expected, 0b1000010);
        QCOMPARE(pattern0.mask, 0b1100011);
        QCOMPARE(pattern1.expected, 0b111100000000);
        QCOMPARE(pattern1.mask, 0b111111110000);

        std::swap(pattern0, pattern1);

        QCOMPARE(pattern0.expected, 0b111100000000);
        QCOMPARE(pattern0.mask, 0b111111110000);
        QCOMPARE(pattern1.expected, 0b1000010);
        QCOMPARE(pattern1.mask, 0b1100011);
    }
};

QTEST_APPLESS_MAIN(TstCppBitmask)

#include "tst_cppbitmask.moc"

