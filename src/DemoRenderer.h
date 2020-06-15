#pragma once

#include <QtGlobal>
#include <QObject>
#include <QWidget>
#include "OpenGLRenderer.h"

class DemoRenderer : public OpenGLRenderer
{
    Q_OBJECT
public:
    explicit DemoRenderer(QObject *parent = nullptr);

    void setScale(float newScale);
    void setLagEnabled(bool on);
protected:
    virtual void paintGL(QOpenGLFunctions_3_0 * const glFunc);

private:
    QElapsedTimer _timer;
    float _scale = 1.0f;
    bool _lagEnabled = false;
};
