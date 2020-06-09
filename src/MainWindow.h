#pragma once

#include <QMainWindow>
#include <QTimer>
#include <QPointer>

// #include "example_surface.h"
// #include "threadedopenglcontainer.h"
// #include "imagewidget.h"

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

class OpenGLWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void slot_ZoomChanged(int value);
    void slot_LagToggled(bool on);
    // void slot_ResetClicked();
    void slot_FrameDrawn();
    void slot_UpdateStats();
private:
    OpenGLWindow *_openglWidget;
    QLabel *_cpuLabel;
    QLabel *_fpsLabel;
    int _frameCounter;
    int _oldProcJiffies;
    int _oldAllJiffies;
};
