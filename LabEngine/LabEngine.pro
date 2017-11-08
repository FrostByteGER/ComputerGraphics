QT += core gui opengl multimedia

LIBS    += -lOpengl32

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LabEngine
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    Mesh.cpp \
    Model.cpp \
    Main.cpp \
    ShaderManager.cpp \
    Transform3D.cpp \
    InputManager.cpp \
    Camera.cpp \
    Shader.cpp \
    GLWidget.cpp \
    MainWindow.cpp

HEADERS += \
    Mesh.h \
    Model.h \
    ShaderManager.h \
    Transform3D.h \
    InputManager.h \
    Camera.h \
    Shader.h \
    Light.h \
    GLWidget.h \
    MainWindow.h

FORMS += \
    MainWindow.ui


win32-msvc2017:CONFIG(release, debug|release): LIBS += -L$$PWD/Libraries/Assimp/msvc2017/ -lassimp-vc140-mt
else:win32-msvc2017:CONFIG(debug, debug|release): LIBS += -L$$PWD/Libraries/Assimp/msvc2017/ -lassimp-vc140-mtd

win32-g++: LIBS += -L$$PWD/Libraries/Assimp/mingw/ -llibassimp.dll

unix: LIBS += -L$$PWD/Libraries/Assimp/mingw/ -llibassimp.dll

INCLUDEPATH += $$PWD/Libraries/Assimp/include
DEPENDPATH += $$PWD/Libraries/Assimp/include

DISTFILES += \
    Resources/Shaders/simple.frag \
    Resources/Shaders/simple.vert \
    Resources/Models/sphere.obj \
    Resources/Models/nanosuit.obj \
    Resources/Models/nanosuit/nanosuit.obj \
    Resources/Models/crate/Crate.obj
