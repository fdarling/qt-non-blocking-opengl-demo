#include "OpenGLRenderer.h"
#include <QOpenGLFunctions_3_0>
#include <QOpenGLFunctions_3_3_Core>
#include "DrawCube.h"
#include <cmath>
#include <QThread>

OpenGLRenderer::OpenGLRenderer(OpenGLWindow *onGlWindow)
    : _glContext(nullptr), _glWindow(onGlWindow), _scale(1.0), _lagEnabled(false)
{
    _timer.start();
}

bool OpenGLRenderer::create()
{
    _glContext = new QOpenGLContext();
    return _glContext->create();
}

void OpenGLRenderer::setScale(float newScale)
{
    _scale = newScale;
}

void OpenGLRenderer::setLagEnabled(bool on)
{
    _lagEnabled = on;
}

void OpenGLRenderer::stop()
{
    _running = false;
}

void OpenGLRenderer::start()
{
    if (!create()) return;

    _running = true;

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

        f->glViewport(0, 0, _width, _height);
        f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        f->glEnable(GL_CULL_FACE);
        f->glEnable(GL_DEPTH_TEST);
        f->glDepthMask(GL_TRUE);

        f->glMatrixMode(GL_PROJECTION);
        f->glLoadIdentity();

        // Calculate The Aspect Ratio Of The Window
        gldPerspective(f, 45.0f, static_cast<GLfloat>(_width) / static_cast<GLfloat>(_height), 0.1f, 100.0f);

        f->glMatrixMode(GL_MODELVIEW);
        f->glLoadIdentity();

        const float angle = fmodf(static_cast<float>(_timer.elapsed())/100.0f, 360.0f);

        f->glTranslatef(0.0f, 0.0f, -7.0f);
        f->glScalef(_scale, _scale, _scale);

        f->glRotatef(angle, 0.0f, 1.0f, 0.0f); // Rotate The cube around the Y axis
        f->glRotatef(angle, 1.0f, 1.0f, 1.0f);

        DrawCube(f);

        _glContext->swapBuffers(_glWindow);

        emit frameSwapped();

        if (_lagEnabled)
            QThread::msleep(250);
    }
}
