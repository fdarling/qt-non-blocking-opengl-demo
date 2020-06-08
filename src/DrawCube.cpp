#include "DrawCube.h"

#include <QOpenGLFunctions_3_0>

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
