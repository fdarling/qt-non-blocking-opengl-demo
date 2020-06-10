QT += core gui widgets
CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += src src/lib

SOURCES += \
    src/DemoRenderer.cpp \
    src/MainWindow.cpp \
    src/lib/OpenGLWindow.cpp \
    src/lib/OpenGLRenderer.cpp \
    src/main.cpp

HEADERS += \
    src/DemoRenderer.h \
    src/MainWindow.h \
    src/lib/OpenGLWindow.h \
    src/lib/OpenGLRenderer.h

