#-------------------------------------------------
#
# Project created by QtCreator 2017-06-20T16:46:06
#
#-------------------------------------------------
CONFIG += static
QT       += serialport
QT       += core gui
QT       += network
QT       += widgets

#gitversion.pri
#include($(CSG_ENV)/proj/defs.pri)
include(gitversion.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UtilizationDevTesting
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logindialog.cpp \
    paramconfig.cpp \
    mythread.cpp \
    dev_protocol.cpp \
    dev_testprocess.cpp \
    publicdataclass.cpp \
    checksum.cpp \
    testthread.cpp \
    paramset_internet.cpp \
    paramset_gprs.cpp

HEADERS  += mainwindow.h \
    logindialog.h \
    paramconfig.h \
    mythread.h \
    dev_protocol.h \
    dev_testprocess.h \
    publicdataclass.h \
    checksum.h \
    testthread.h \
    paramset_internet.h \
    paramset_gprs.h

FORMS    += mainwindow.ui \
    logindialog.ui \
    paramconfig.ui \
    paramset_internet.ui \
    paramset_gprs.ui

RESOURCES += \
    images/myResourses.qrc
