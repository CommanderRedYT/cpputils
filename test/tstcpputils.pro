TEMPLATE = app

QT += core testlib
QT -= gui widgets

CONFIG += c++17 qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

SOURCES += \
    tst_cppbitmask.cpp

CPPUTILS_DIR = $$PWD/..

include($$CPPUTILS_DIR/cpputils.pri)
include($$CPPUTILS_DIR/cpputils_src.pri)
include($$CPPUTILS_DIR/test/cpputilstestutils.pri)
include($$CPPUTILS_DIR/test/cpputilstestutils_src.pri)

equals(CLONE_EXPECTED, 1) {
    EXPECTED_DIR = $$PWD/expected

    message("Checking out expected...")
    exists($$EXPECTED_DIR/.git): {
        system("git -C $$EXPECTED_DIR pull")
    } else {
        system("git clone https://github.com/0xFEEDC0DE64/expected.git $$EXPECTED_DIR")
    }
} else: exists($$PWD/../../expected/include) {
    EXPECTED_DIR = $$PWD/../../expected
} else {
    error("expected not found, please run git submodule update --init")
}

include($$EXPECTED_DIR/expected.pri)

equals(CLONE_FMT, 1) {
    FMT_DIR = $$PWD/fmt

    message("Checking out fmt...")
    exists($$FMT_DIR/.git): {
        system("git -C $$FMT_DIR pull")
    } else {
        system("git clone https://github.com/0xFEEDC0DE64/fmt.git $$FMT_DIR")
    }
} else: exists($$PWD/../../fmt/include) {
    FMT_DIR = $$PWD/../../fmt
} else {
    error("fmt not found, please run git submodule update --init")
}

include($$FMT_DIR/fmt.pri)
include($$FMT_DIR/fmt_src.pri)

QMAKE_CXXFLAGS += -Wno-missing-field-initializers
