#include "OpenGLThread.h"

OpenGLThread::OpenGLThread(QObject *parent)
    : QThread(parent)
{
    setTerminationEnabled(false);
}
