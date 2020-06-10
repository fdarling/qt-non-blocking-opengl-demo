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

    _glThread = new QThread();
    moveToThread(_glThread);

    connect(_glThread, &QThread::started, this, &OpenGLRenderer::start);
    connect(_glThread, &QThread::finished, _glThread, &QObject::deleteLater);

    _glThread->start();
}

bool OpenGLRenderer::create()
{
    _glContext = new QOpenGLContext();
    return _glContext->create();
}

void OpenGLRenderer::stop()
{
    _running = false;
}

void OpenGLRenderer::start()
{
    if (!create()) return;

    _running = true;
    _frameTimer.start();

    while(_running) {
        run();
    }
}

void OpenGLRenderer::resizeGL(int w, int h)
{
    _width = w;
    _height = h;
}

void OpenGLRenderer::run()
{
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
    QWidget* glWidget = QWidget::createWindowContainer(_glWindow, parent);

    return glWidget;
}

void OpenGLRenderer::setTargetFPS(int targetFps)
{
    _targetFPS = targetFps;
}