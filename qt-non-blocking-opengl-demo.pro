QT += core gui widgets
CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    src/DrawCube.cpp \
    src/MainWindow.cpp \
    src/OpenGLWindow.cpp \
    src/OpenGLRenderer.cpp \
    src/main.cpp

HEADERS += \
    src/DrawCube.h \
    src/MainWindow.h \
    src/OpenGLWindow.h \
    src/OpenGLRenderer.h

