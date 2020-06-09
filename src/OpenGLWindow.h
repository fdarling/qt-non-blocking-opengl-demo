#pragma once

#include <QWindow>
#include <QElapsedTimer>

class OpenGLRenderer;

class OpenGLWindow : public QWindow
{
    Q_OBJECT
public:
    OpenGLWindow();
    ~OpenGLWindow();
public slots:
    void setScale(float newScale);
    void setLagEnabled(bool on);
    void onRendererSwapped();

signals:
    void frameSwapped();

protected:
    void resizeEvent(QResizeEvent *ev);
    void initializeGL() ;
    void paintGL() ;

    OpenGLRenderer *_glRenderer;
    QThread *_glThread;
};
