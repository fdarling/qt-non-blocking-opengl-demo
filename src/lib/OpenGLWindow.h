#pragma once

#include <QWindow>
#include <QElapsedTimer>

class OpenGLRenderer;

class OpenGLWindow : public QWindow
{
    Q_OBJECT
public:
    OpenGLWindow(OpenGLRenderer *glRenderer);
    ~OpenGLWindow();

protected:
    void resizeEvent(QResizeEvent *ev);
    void initializeGL() ;
    void paintGL() ;

    OpenGLRenderer *_glRenderer;
};
