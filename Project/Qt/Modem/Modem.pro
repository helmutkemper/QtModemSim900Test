#-------------------------------------------------
#
# Project created by QtCreator 2014-10-08T11:17:51
#
#-------------------------------------------------

include ( ../../../Project/Qt/SerialPort/qextserialport.pri )
include ( ../../../commun/types.pri )

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Modem
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    serialdialog.cpp \
    buffer.cpp \
    atmodem.cpp \
    eeprom.cpp \
    unicodetoascii.cpp \
    dtmf.cpp \
    arduino.cpp \
    statemachine.cpp \
    stackenum.cpp \
    copy.cpp

HEADERS  += mainwindow.h \
    serialdialog.h \
    buffer.h \
    atmodem.h \
    eeprom.h \
    unicodetoascii.h \
    dtmf.h \
    arduino.h \
    statemachine.h \
    stackenum.h \
    copy.h

FORMS    += mainwindow.ui \
    serialdialog.ui \
    dtmf.ui \
    arduino.ui

RESOURCES += \
    icons.qrc
