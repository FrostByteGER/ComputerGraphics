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

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../Development-Tools/Assimp/assimp-3.2/lib/msvc2015/ -lassimp-vc130-mt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../Development-Tools/Assimp/assimp-3.2/lib/msvc2015/ -lassimp-vc130-mtd

INCLUDEPATH += $$PWD/../../../../../Development-Tools/Assimp/assimp-3.2/include
DEPENDPATH += $$PWD/../../../../../Development-Tools/Assimp/assimp-3.2/include

unix: LIBS += -L$$PWD/../../../../../Development-Tools/Assimp/assimp-3.2/lib/mingw/ -llibassimp.dll

INCLUDEPATH += $$PWD/../../../../../Development-Tools/Assimp/assimp-3.2/include
DEPENDPATH += $$PWD/../../../../../Development-Tools/Assimp/assimp-3.2/include

DISTFILES += \
    Resources/Shaders/simple.frag \
    Resources/Shaders/simple.vert
