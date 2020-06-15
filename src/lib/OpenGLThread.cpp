#include "OpenGLThread.h"

OpenGLThread::OpenGLThread(FrameFunc callback, QObject *parent)
    : QThread(parent),
    _callback(callback)
{
}

OpenGLThread::~OpenGLThread()
{
    // stop();
}

void OpenGLThread::stop()
{
    requestInterruption();
    wait();
}

void OpenGLThread::run()
{
    while(!isInterruptionRequested()) {
        _callback();
    }
}
