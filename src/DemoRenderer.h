#pragma once

#include <QtGlobal>

QT_BEGIN_NAMESPACE
class QOpenGLFunctions_3_0;
QT_END_NAMESPACE

void DrawCube(QOpenGLFunctions_3_0 *f);
void gldPerspective(QOpenGLFunctions_3_0 *f, double fovx, double aspect, double zNear, double zFar);

#include <QObject>
#include <QWidget>
#include "OpenGLRenderer.h"

class DemoRenderer : public OpenGLRenderer
{
    Q_OBJECT
public:
    explicit DemoRenderer() = default;

signals:
    void frameSwapped();

public slots:
    void setScale(float newScale);
    void setLagEnabled(bool on);

protected:
    virtual void paintGL(QOpenGLFunctions_3_0 * const glFunc);
    virtual void swapGL();

private:
    QElapsedTimer _timer;
    float _scale = 1.0f;
    bool _lagEnabled = false;
};
