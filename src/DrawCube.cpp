#include "DrawCube.h"
#include <QOpenGLFunctions_3_0>

#define _USE_MATH_DEFINES
#include <math.h>

void DrawCube(QOpenGLFunctions_3_0 *f)
{
    f->glBegin(GL_QUADS);     // Draw The Cube Using quads
    f->glColor3f(0.0f, 1.0f, 0.0f); // Color Blue
    f->glVertex3f( 1.0f, 1.0f, -1.0f);  // Top Right Of The Quad (Top)
    f->glVertex3f(-1.0f, 1.0f, -1.0f);  // Top Left Of The Quad (Top)
    f->glVertex3f(-1.0f, 1.0f, 1.0f);   // Bottom Left Of The Quad (Top)
    f->glVertex3f( 1.0f, 1.0f, 1.0f);   // Bottom Right Of The Quad (Top)
    f->glColor3f(1.0f, 0.5f, 0.0f); // Color Orange
    f->glVertex3f( 1.0f, -1.0f, 1.0f);  // Top Right Of The Quad (Bottom)
    f->glVertex3f(-1.0f, -1.0f, 1.0f);  // Top Left Of The Quad (Bottom)
    f->glVertex3f(-1.0f, -1.0f, -1.0f); // Bottom Left Of The Quad (Bottom)
    f->glVertex3f( 1.0f, -1.0f, -1.0f); // Bottom Right Of The Quad (Bottom)
    f->glColor3f(1.0f, 0.0f, 0.0f); // Color Red
    f->glVertex3f( 1.0f, 1.0f, 1.0f);   // Top Right Of The Quad (Front)
    f->glVertex3f(-1.0f, 1.0f, 1.0f);   // Top Left Of The Quad (Front)
    f->glVertex3f(-1.0f, -1.0f, 1.0f);  // Bottom Left Of The Quad (Front)
    f->glVertex3f( 1.0f, -1.0f, 1.0f);  // Bottom Right Of The Quad (Front)
    f->glColor3f(1.0f, 1.0f, 0.0f); // Color Yellow
    f->glVertex3f( 1.0f, -1.0f, -1.0f); // Top Right Of The Quad (Back)
    f->glVertex3f(-1.0f, -1.0f, -1.0f); // Top Left Of The Quad (Back)
    f->glVertex3f(-1.0f, 1.0f, -1.0f);  // Bottom Left Of The Quad (Back)
    f->glVertex3f( 1.0f, 1.0f, -1.0f);  // Bottom Right Of The Quad (Back)
    f->glColor3f(0.0f, 0.0f, 1.0f); // Color Blue
    f->glVertex3f(-1.0f, 1.0f, 1.0f);   // Top Right Of The Quad (Left)
    f->glVertex3f(-1.0f, 1.0f, -1.0f);  // Top Left Of The Quad (Left)
    f->glVertex3f(-1.0f, -1.0f, -1.0f); // Bottom Left Of The Quad (Left)
    f->glVertex3f(-1.0f, -1.0f, 1.0f);  // Bottom Right Of The Quad (Left)
    f->glColor3f(1.0f, 0.0f, 1.0f); // Color Violet
    f->glVertex3f( 1.0f, 1.0f, -1.0f);  // Top Right Of The Quad (Right)
    f->glVertex3f( 1.0f, 1.0f, 1.0f);   // Top Left Of The Quad (Right)
    f->glVertex3f( 1.0f, -1.0f, 1.0f);  // Bottom Left Of The Quad (Right)
    f->glVertex3f( 1.0f, -1.0f, -1.0f); // Bottom Right Of The Quad (Right)
    f->glEnd();           // End Drawing The Cube
}


void gldPerspective(QOpenGLFunctions_3_0 *f, GLdouble fovx, GLdouble aspect, GLdouble zNear, GLdouble zFar)
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
