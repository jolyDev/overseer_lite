#-------------------------------------------------
#
# Project created by QtCreator 2018-05-21T16:05:12
#
#-------------------------------------------------

QT += network
QT += core network
QT += core
QT += core gui
QT += widgets
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Kursova
TEMPLATE = app


SOURCES += main.cpp\
        cam_control.cpp \
    emergency_dialog.cpp \
    videoplayer.cpp \
    overwatch.cpp \
    timesetdialog.cpp \
    player.cpp \
    video_writer.cpp \
    server_interaction.cpp

HEADERS  += cam_control.h \
    emergency_dialog.h \
    videoplayer.h \
    overwatch.h \
    timesetdialog.h \
    player.h \
    video_writer.h \
    server_interaction.h

FORMS    += cam_control.ui \
    emergency_dialog.ui \
    videoplayer.ui \
    timesetdialog.ui \
    server_interaction.ui \
    mainwindow.ui

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv

CONFIG += c++14
