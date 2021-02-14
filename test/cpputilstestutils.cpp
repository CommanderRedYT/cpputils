#include "cpputilstestutils.h"

namespace QTest {
template<>
char *toString(const std::string &str)
{
    return ::QTest::toString(QString::fromStdString(str));
}
} // namespace QTest
