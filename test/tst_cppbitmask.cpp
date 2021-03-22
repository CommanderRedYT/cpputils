#include <QtTest>
#include <QDebug>
#include <QByteArray>

#include <chrono>
#include <string>

#include "cpputilstestutils.h"
#include "cppbitmask.h"

class TstCppBitmask : public QObject
{
    Q_OBJECT

private slots:
    void test_simple()
    {
        constexpr cpputils::bit_pattern pattern{"11XXX10"};
        QVERIFY(0b1101010 == pattern);
        QVERIFY(0b1110110 == pattern);
        QVERIFY(!(0b1100000 == pattern));
        QVERIFY(!(0b1000010 == pattern));
    }
};

QTEST_APPLESS_MAIN(TstCppBitmask)

#include "tst_cppbitmask.moc"

