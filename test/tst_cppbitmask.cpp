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
        constexpr cpputils::bit_pattern<7> pattern{"10XXX10"};
        QCOMPARE(pattern.expected, 0b1000010);
        QCOMPARE(pattern.mask, 0b1100011);
        QVERIFY(pattern.match(0b1001010));
        QVERIFY(pattern.match(0b1010110));
        QVERIFY(!pattern.match(0b1000000));
        QVERIFY(!pattern.match(0b1100010));
    }

    void test_copy()
    {
        const cpputils::bit_pattern<7> pattern{"10XXX10"};
        const cpputils::bit_pattern<7> patternCopy{pattern};
        QCOMPARE(patternCopy.expected, 0b1000010);
        QCOMPARE(patternCopy.mask, 0b1100011);
    }

    void test_assign()
    {
        const cpputils::bit_pattern<9> pattern{"10XXX10X1"};
        cpputils::bit_pattern<9> patternCopy{"11110000X"};
        QCOMPARE(patternCopy.expected, 0b111100000);
        QCOMPARE(patternCopy.mask, 0b111111110);
        patternCopy = pattern;
        QCOMPARE(patternCopy.expected, 0b100001001);
        QCOMPARE(patternCopy.mask, 0b110001101);
    }

    void test_swap()
    {
        cpputils::bit_pattern<9> pattern0{"10XXX10X1"};
        cpputils::bit_pattern<9> pattern1{"11110000X"};

        QCOMPARE(pattern0.expected, 0b100001001);
        QCOMPARE(pattern0.mask, 0b110001101);
        QCOMPARE(pattern1.expected, 0b111100000);
        QCOMPARE(pattern1.mask, 0b111111110);

        std::swap(pattern0, pattern1);

        QCOMPARE(pattern0.expected, 0b111100000);
        QCOMPARE(pattern0.mask, 0b111111110);
        QCOMPARE(pattern1.expected, 0b100001001);
        QCOMPARE(pattern1.mask, 0b110001101);
    }
};

QTEST_APPLESS_MAIN(TstCppBitmask)

#include "tst_cppbitmask.moc"

