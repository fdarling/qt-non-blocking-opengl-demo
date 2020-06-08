#include "OpenGLWidget.h"
#include "DrawCube.h"

#include <QOpenGLFunctions_3_0>
#include <QThread>
#include <cmath>

static void gldPerspective(QOpenGLFunctions_3_0 *f, GLdouble fovx, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
    // This code is based off the MESA source for gluPerspective
    // *NOTE* This assumes GL_PROJECTION is the current matrix


    GLdouble xmin, xmax, ymin, ymax;
    GLdouble m[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    const auto M = [&m](int i, int j)->GLdouble *
    {
        return (m + j * 4 + i);
    };

    xmax = zNear * tan(fovx * M_PI / 360.0);
    xmin = -xmax;

    ymin = xmin / aspect;
    ymax = xmax / aspect;

    // Set up the projection matrix
    *M(0, 0) = (2.0 * zNear) / (xmax - xmin);
    *M(1, 1) = (2.0 * zNear) / (ymax - ymin);
    *M(2, 2) = -(zFar + zNear) / (zFar - zNear);

    *M(0, 2) = (xmax + xmin) / (xmax - xmin);
    *M(1, 2) = (ymax + ymin) / (ymax - ymin);
    *M(3, 2) = -1.0;

    *M(2, 3) = -(2.0 * zFar * zNear) / (zFar - zNear);

    // Add to current matrix
    f->glMultMatrixd(m);
}

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent), _scale(1.0), _lagEnabled(false)
{
    _timer.start();
}

void OpenGLWidget::setScale(float newScale)
{
    _scale = newScale;
}

void OpenGLWidget::setLagEnabled(bool on)
{
    _lagEnabled = on;
}

void OpenGLWidget::initializeGL()
{
    QOpenGLFunctions_3_0 * const f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_0>();
    f->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void OpenGLWidget::resizeGL(int w, int h)
{
    // Q_UNUSED(w);
    // Q_UNUSED(h);
    /*m_projection.setToIdentity();
    m_projection.perspective(45.0f, w / float(h), 0.01f, 100.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
    glMatrixMode(GL_MODELVIEW);*/

    QOpenGLFunctions_3_0 * const f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_0>();
    f->glViewport(0, 0, w, h);
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    f->glEnable(GL_CULL_FACE);
    f->glEnable(GL_DEPTH_TEST);
    f->glDepthMask(GL_TRUE);

    f->glMatrixMode(GL_PROJECTION);
    f->glLoadIdentity();

    // Calculate The Aspect Ratio Of The Window
    gldPerspective(f, 45.0f, static_cast<GLfloat>(w) / static_cast<GLfloat>(h), 0.1f, 100.0f);

    f->glMatrixMode(GL_MODELVIEW);
    f->glLoadIdentity();
}

void OpenGLWidget::paintGL()
{
    QOpenGLFunctions_3_0 * const f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_0>();
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    const float angle = fmodf(static_cast<float>(_timer.elapsed())/100.0f, 360.0f);
    f->glLoadIdentity();

    f->glTranslatef(0.0f, 0.0f, -7.0f);
    f->glScalef(_scale, _scale, _scale);

    f->glRotatef(angle, 0.0f, 1.0f, 0.0f); // Rotate The cube around the Y axis
    f->glRotatef(angle, 1.0f, 1.0f, 1.0f);
    DrawCube(f);
    if (_lagEnabled)
        QThread::msleep(250);
}
