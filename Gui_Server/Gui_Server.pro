#-------------------------------------------------
#
# Project created by QtCreator 2018-06-10T03:10:42
#
#-------------------------------------------------

QT += core
QT += gui
QT += widgets
QT += network
QT += core
QT += core gui
QT += multimedia
CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Gui_Server
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    data_storage.cpp

HEADERS  += mainwindow.h \
    data_storage.h

FORMS    += mainwindow.ui

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv
