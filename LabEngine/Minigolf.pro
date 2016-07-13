QT += core gui opengl multimedia

LIBS    += -lOpengl32

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

TARGET = Minigolf
#CONFIG += console
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
    PhysicsBox.cpp \
    PhysicsSphere.cpp \
    GLWidget.cpp \
    MainWindow.cpp \
    PhysicsThread.cpp

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
    PhysicsObject.h \
    GLWidget.h \
    MainWindow.h \
    LabEngine.h \
    Models.h \
    PhysicsThread.h

FORMS += \
    MainWindow.ui

DISTFILES += \
    Resources/Shaders/simple.frag \
    Resources/Shaders/simple.vert \
    Resources/Models/Sphere.obj \
    Resources/Models/Floor.obj \
    Resources/Models/Crate/Crate.obj

RESOURCES += \
    Resources.qrc
