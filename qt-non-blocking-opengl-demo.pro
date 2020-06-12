QT += core gui widgets
CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += src src/lib src/util

SOURCES += \
    src/DemoRenderer.cpp \
    src/MainWindow.cpp \
    src/lib/OpenGLWindow.cpp \
    src/lib/OpenGLRenderer.cpp \
    src/lib/OpenGLThread.cpp \
    src/main.cpp \
    src/util/cpuusage.cpp

HEADERS += \
    src/DemoRenderer.h \
    src/MainWindow.h \
    src/lib/OpenGLWindow.h \
    src/lib/OpenGLRenderer.h \
    src/lib/OpenGLThread.h \
    src/util/cm_ctors.h \
    src/util/cpuusage.h \
    src/util/lambda_thread.h \
    src/util/strfmt.h

