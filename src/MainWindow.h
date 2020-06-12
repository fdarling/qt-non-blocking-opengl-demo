#pragma once

#include <QMainWindow>
#include <QTimer>
#include <QPointer>
#include "DemoRenderer.h"

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
protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void slot_ZoomChanged(int value);
    void slot_LagToggled(bool on);
    void slot_AlexToggled(bool on);
    void slot_TargetFPSChanged(int value);
    void slot_FrameDrawn();
    void slot_UpdateStats();
private:
    DemoRenderer *_demoRenderer;
    QLabel *_cpuLabel;
    QLabel *_fpsLabel;
    int _frameCounter;
    int _oldProcJiffies;
    int _oldAllJiffies;
    bool _metricCPUUsageAlex;
};
