#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include <QObject>
#include <QOpenGLContext>
#include "OpenGLWindow.h"

class OpenGLRenderer : public QObject
{
    Q_OBJECT
public:
    explicit OpenGLRenderer(OpenGLWindow *onGlWindow);

    bool create();
    void start();
    void run();
    void stop();

    void resizeGL(int w, int h);

signals:
    void frameSwapped();

public slots:
    void setScale(float newScale);
    void setLagEnabled(bool on);

private:
    QOpenGLContext *_glContext;
    OpenGLWindow *_glWindow;

    QElapsedTimer _timer;
    QElapsedTimer _frameTimer;

    int _targetFPS = 60;

    float _scale;
    bool _lagEnabled;
    int _width, _height;
    std::atomic<bool> _running;
};

#endif // OPENGLRENDERER_H
