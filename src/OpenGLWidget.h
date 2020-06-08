#pragma once

#include <QOpenGLWidget>
#include <QElapsedTimer>

class OpenGLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    OpenGLWidget(QWidget *parent = nullptr);
public slots:
    void setScale(float newScale);
    void setLagEnabled(bool on);
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    QElapsedTimer _timer;
    float _scale;
    bool _lagEnabled;
};
