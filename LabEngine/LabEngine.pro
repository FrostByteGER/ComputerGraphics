QT += core gui opengl

LIBS    += -lOpengl32

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LabEngine
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    GLWindow.cpp \
    Shader.cpp \
    Mesh.cpp \
    Model.cpp \
    Main.cpp

HEADERS += \
    GLWindow.h \
    Shader.h \
    Mesh.h \
    Model.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/Libraries/Assimp/msvc2015/ -lassimp-vc130-mt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/Libraries/Assimp/msvc2015/ -lassimp-vc130-mtd

INCLUDEPATH += $$PWD/Libraries/Assimp/include
DEPENDPATH += $$PWD/Libraries/Assimp/include

unix: LIBS += -L$$PWD/Libraries/Assimp/mingw/ -llibassimp.dll

INCLUDEPATH += $$PWD/Libraries/Assimp/include
DEPENDPATH += $$PWD/Libraries/Assimp/include

DISTFILES += \
    Resources/Shaders/simple.frag \
    Resources/Shaders/simple.vert
