#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include <QObject>
#include <QOpenGLContext>
#include "OpenGLWindow.h"
#include <QOpenGLFunctions_3_0>

class OpenGLRenderer : public QObject
{
    Q_OBJECT
public:
    explicit OpenGLRenderer();

    bool create();
    void start();
    void run();
    void stop();

    void resizeGL(int w, int h);

    QWidget* createWidget(QWidget* parent);

protected:
    virtual void paintGL(QOpenGLFunctions_3_0 * const glFunc) = 0;
    virtual void swapGL() = 0;

    int _width, _height;

private:
    QOpenGLContext *_glContext;
    OpenGLWindow *_glWindow;

    QElapsedTimer _frameTimer;

    int _targetFPS = 60;

    std::atomic<bool> _running;
    QThread *_glThread;
};

#endif // OPENGLRENDERER_H
