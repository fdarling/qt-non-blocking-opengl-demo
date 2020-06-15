#include "OpenGLThread.h"
#include <QDebug>

OpenGLThread::OpenGLThread(FrameFunc callback, QObject *parent)
    : QThread(parent),
    _callback(callback)
{
    qDebug() << "OpenGLThread : " << "constructed";
//    setTerminationEnabled(false);
}

OpenGLThread::~OpenGLThread()
{
    qDebug() << "OpenGLThread : " << "distructed";
}

void OpenGLThread::stop()
{
    qDebug() << "OpenGLThread : " << "stoping";

    requestInterruption();
    wait();

    qDebug() << "OpenGLThread : " << "stopped";
}

void OpenGLThread::run()
{
    while(!isInterruptionRequested()) {
        qDebug() << "OpenGLThread : " << "pre run";
        _callback();
        qDebug() << "OpenGLThread : " << "post run";
    }
}
