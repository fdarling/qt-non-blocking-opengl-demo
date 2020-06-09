#include "OpenGLWindow.h"
#include "OpenGLRenderer.h"
#include <QResizeEvent>
#include <QOpenGLFunctions_3_0>
#include <QThread>
#include <cmath>

OpenGLWindow::OpenGLWindow()
    : QWindow()
{
    initializeGL();
}

OpenGLWindow::~OpenGLWindow()
{
    _glRenderer->stop();
}

void OpenGLWindow::setScale(float newScale)
{
    _glRenderer->setScale(newScale);
}

void OpenGLWindow::setLagEnabled(bool on)
{
    _glRenderer->setLagEnabled(on);
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

    _glRenderer = new OpenGLRenderer(this);
    _glThread = new QThread();
    _glRenderer->moveToThread(_glThread);

    connect(_glThread, &QThread::started, _glRenderer, &OpenGLRenderer::start);
    connect(_glThread, &QThread::finished, _glThread, &QObject::deleteLater);

    connect(_glRenderer, &OpenGLRenderer::frameSwapped, this, &OpenGLWindow::onRendererSwapped);

    _glThread->start();
}

void OpenGLWindow::onRendererSwapped()
{
    emit frameSwapped();
}

void OpenGLWindow::resizeEvent(QResizeEvent *ev)
{
    _glRenderer->resizeGL(ev->size().width(), ev->size().height());
}
