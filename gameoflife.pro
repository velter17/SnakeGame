TEMPLATE = app

QT += qml quick

SOURCES += main.cpp \
    CCubeRenderer.cpp \
    CGridRenderer.cpp \
    CGameComponent.cpp \
    CGameOfLife.cpp \
    CCircleRenderer.cpp \
    CSnakeGame.cpp

RESOURCES += qml.qrc

CONFIG += c++11

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    CGridRenderer.h \
    CCubeRenderer.h \
    GameTypes.h \
    CGameComponent.h \
    CGameOfLife.h \
    IGame.h \
    IRenderer.h \
    CCircleRenderer.h \
    CSnakeGame.h

