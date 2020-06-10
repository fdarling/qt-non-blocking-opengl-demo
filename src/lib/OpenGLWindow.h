#pragma once

#include <QWindow>

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

    OpenGLRenderer *_glRenderer;
};
