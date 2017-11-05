QT += core gui opengl

LIBS    += -lOpengl32

CONFIG += c++17

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

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
    InputManager.cpp \
    Camera.cpp \
    Scene.cpp \
    Shader.cpp \
    Player.cpp \
    PhysicsObject.cpp \
    PhysicsThread.cpp \
    PhysicsBox.cpp \
    PhysicsSphere.cpp \
    GLWidget.cpp \
    VTransform.cpp

HEADERS += \
    Mesh.h \
    Model.h \
    ShaderManager.h \
    Collision.h \
    InputManager.h \
    Camera.h \
    Scene.h \
    Shader.h \
    Player.h \
    Light.h \
    PointLight.h \
    PhysicsThread.h \
    PhysicsObject.h \
    GLWidget.h \
    VTransform.h

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
