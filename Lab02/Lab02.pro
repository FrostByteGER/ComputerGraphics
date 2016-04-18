#-------------------------------------------------
#
# Project created by QtCreator 2016-03-04T23:07:51
#
#-------------------------------------------------

QT       += core gui opengl

LIBS    += -lOpengl32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lab02
TEMPLATE = app


SOURCES += main.cpp\
    glwidget.cpp

HEADERS  += \
    glwidget.h

DISTFILES += \
    simple.vert \
    simple.frag

RESOURCES += \
    resources.qrc
