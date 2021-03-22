TEMPLATE = app

QT += core testlib
QT -= gui widgets

CONFIG += c++17 qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

SOURCES += tst_cppbitmask.cpp

CPPUTILS_DIR = $$PWD/..

include($$CPPUTILS_DIR/cpputils.pri)
include($$CPPUTILS_DIR/cpputils_src.pri)
include($$CPPUTILS_DIR/test/cpputilstestutils.pri)
include($$CPPUTILS_DIR/test/cpputilstestutils_src.pri)

QMAKE_CXXFLAGS += -Wno-missing-field-initializers
