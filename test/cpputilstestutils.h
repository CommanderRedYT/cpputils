#pragma once

#include <QMetaType>
#include <QtTest>

Q_DECLARE_METATYPE(std::string)

#define DECLARE_QDEBUG_OP_FOR_ENUM(Namespace, EnumName) \
    QDebug operator<<(QDebug debug, EnumName val) \
    { \
        QDebugStateSaver saver(debug); \
        debug.nospace() << #EnumName "(" << Namespace toString(val).c_str() << ')'; \
        return debug; \
    }

// only needed if there is a nameclash between std::string *::toString(const T &) and template<typename T> char *QTest::toString(const T &)
#define FIXEDCOMPARE(actual, expected) \
do {\
    if (!fixedCompare(actual, expected, #actual, #expected, __FILE__, __LINE__))\
        return;\
} while (false)

namespace {
template <typename T1, typename T2>
inline bool fixedCompare(T1 const &t1, T2 const &t2, const char *actual, const char *expected,
                         const char *file, int line)
{
    return QTest::compare_helper(t1 == t2, "Compared values are not the same",
                                 ::QTest::toString(t1), ::QTest::toString(t2), actual, expected, file, line);
}
}

namespace QTest {
template<>
char *toString(const std::string &str);
} // namespace QTest
