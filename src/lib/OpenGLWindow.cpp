#include "OpenGLWindow.h"
#include "OpenGLRenderer.h"
#include <QResizeEvent>
#include <QOpenGLFunctions_3_0>
#include <QThread>
#include <cmath>

OpenGLWindow::OpenGLWindow(OpenGLRenderer *glRenderer)
    : QWindow(), _glRenderer(glRenderer)
{
    initializeGL();
}

OpenGLWindow::~OpenGLWindow()
{
    _glRenderer->stop();
}

void OpenGLWindow::initializeGL()
{
    setFlags(Qt::Widget);
    setSurfaceType(QSurface::OpenGLSurface);

    QSurfaceFormat format = QSurfaceFormat::defaultFormat();
    format.setVersion(3, 3);
    format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);

    setFormat(format);
    create();
}

void OpenGLWindow::resizeEvent(QResizeEvent *ev)
{
    _glRenderer->resizeGL(ev->size().width(), ev->size().height());
}
