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
    Collision.cpp \
    Transform3D.cpp \
    InputManager.cpp \
    Camera.cpp \
    Shader.cpp \
    PhysicsObject.cpp \
    PhysicsThread.cpp \
    PhysicsBox.cpp \
    PhysicsSphere.cpp \
    GLWidget.cpp \
    MainWindow.cpp

HEADERS += \
    Mesh.h \
    Model.h \
    ShaderManager.h \
    Collision.h \
    Transform3D.h \
    InputManager.h \
    Camera.h \
    Shader.h \
    Light.h \
    PhysicsThread.h \
    PhysicsObject.h \
    GLWidget.h \
    MainWindow.h

FORMS += \
    MainWindow.ui


win32-msvc2015:CONFIG(release, debug|release): LIBS += -L$$PWD/Libraries/Assimp/msvc2015/ -lassimp-vc130-mt
else:win32-msvc2015:CONFIG(debug, debug|release): LIBS += -L$$PWD/Libraries/Assimp/msvc2015/ -lassimp-vc130-mtd

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
