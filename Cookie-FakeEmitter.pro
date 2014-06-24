#-------------------------------------------------
#
# Project created by QtCreator 2014-06-25T00:11:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Cookie-FakeEmitter
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    serial.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    serial.h

FORMS    += mainwindow.ui \
    dialog.ui


CONFIG += serialport
