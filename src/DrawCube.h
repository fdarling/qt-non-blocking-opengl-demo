#pragma once

#include <QtGlobal>

QT_BEGIN_NAMESPACE
class QOpenGLFunctions_3_0;
QT_END_NAMESPACE

void DrawCube(QOpenGLFunctions_3_0 *f);
void gldPerspective(QOpenGLFunctions_3_0 *f, double fovx, double aspect, double zNear, double zFar);

