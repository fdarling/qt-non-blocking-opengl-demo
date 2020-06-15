#include "OpenGLRenderer.h"
#include <QOpenGLFunctions_3_0>
#include <QOpenGLFunctions_3_3_Core>
#include <cmath>
#include <QThread>
#include <QDebug>
#include <QWidget>

OpenGLRenderer::OpenGLRenderer()
    : _glContext(nullptr)
{
    _glWindow = new OpenGLWindow(this);

    _glThread = new OpenGLThread(std::bind(&OpenGLRenderer::run, this), this);

    _glThread->start();
}

OpenGLRenderer::~OpenGLRenderer()
{
    _glThread->stop();
}

bool OpenGLRenderer::create()
{
    if(_glContext)
        return true;

    _frameTimer.start();

    _glContext = new QOpenGLContext();
    return _glContext->create();
}

void OpenGLRenderer::resizeGL(int w, int h)
{
    _width = w;
    _height = h;
}

void OpenGLRenderer::run()
{
    if (!create())
        return;

    // Save some cycles and only run if the window is being exposed
    if (_glWindow->isExposed()) {
        _glContext->makeCurrent(_glWindow);

        QOpenGLFunctions_3_0 * const f = _glContext->versionFunctions<QOpenGLFunctions_3_0>();
        paintGL(f);
        _glContext->swapBuffers(_glWindow);
        swapGL();

        if (_targetFPS>0){
            float targetElapsedNsecs = 1.0 / _targetFPS * 1000000000.0;

            if ( targetElapsedNsecs > _frameTimer.nsecsElapsed() )
            {
                QThread::msleep( (targetElapsedNsecs - _frameTimer.nsecsElapsed()) / 1000000.0 );
            }
        }

        _frameTimer.restart();
    }
}

QWidget* OpenGLRenderer::createWidget(QWidget* parent)
{
    return QWidget::createWindowContainer(_glWindow, parent);
}

void OpenGLRenderer::setTargetFPS(int targetFps)
{
    _targetFPS = targetFps;
}
