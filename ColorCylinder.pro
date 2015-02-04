#-------------------------------------------------
#
# Project created by QtCreator 2015-02-03T11:13:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ColorCylinder
TEMPLATE = app

INCLUDEPATH += "C:/Assimp-3.1.1/include"
LIBS += "C:/Assimp-3.1.1/libs/libassimp.dll"


SOURCES += main.cpp\
        Dialog.cpp \
    Scene.cpp \
    LoaderOfCylinder.cpp \
    Cylinder.cpp

HEADERS  += Dialog.h \
    Scene.h \
    LoaderOfCylinder.h \
    Cylinder.h

FORMS    += Dialog.ui

RESOURCES += \
    Shaders.qrc
