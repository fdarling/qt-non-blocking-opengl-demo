#include "OpenGLThread.h"
#include <QDebug>

OpenGLThread::OpenGLThread(FrameFunc callback)
    : _callback(callback)
{
    qDebug() << "OpenGLThread : " << "constructed";
//    setTerminationEnabled(false);
    _running = true;
}

OpenGLThread::~OpenGLThread()
{
    qDebug() << "OpenGLThread : " << "distructed";
}

void OpenGLThread::stop()
{
    qDebug() << "OpenGLThread : " << "stoping";

//    requestInterruption();
    _running = false;
    wait();

    qDebug() << "OpenGLThread : " << "stopped";
}

void OpenGLThread::run()
{
    while(_running) {
        qDebug() << "OpenGLThread : " << "pre run";
        _callback();
        qDebug() << "OpenGLThread : " << "post run";
    }
}
