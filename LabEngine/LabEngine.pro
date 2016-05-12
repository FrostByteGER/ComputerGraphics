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
    Mesh.cpp \
    Model.cpp \
    Main.cpp \
    ShaderManager.cpp

HEADERS += \
    GLWindow.h \
    Mesh.h \
    Model.h \
    ShaderManager.h


win32-msvc2015:CONFIG(release, debug|release): LIBS += -L$$PWD/Libraries/Assimp/msvc2015/ -lassimp-vc130-mt
else:win32-msvc2015:CONFIG(debug, debug|release): LIBS += -L$$PWD/Libraries/Assimp/msvc2015/ -lassimp-vc130-mtd

win32-g++: LIBS += -L$$PWD/Libraries/Assimp/mingw/ -llibassimp.dll

unix: LIBS += -L$$PWD/Libraries/Assimp/mingw/ -llibassimp.dll

INCLUDEPATH += $$PWD/Libraries/Assimp/include
DEPENDPATH += $$PWD/Libraries/Assimp/include

DISTFILES += \
    Resources/Shaders/simple.frag \
    Resources/Shaders/simple.vert \
    Resources/Models/cube.obj
