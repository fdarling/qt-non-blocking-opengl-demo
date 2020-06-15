#include "MainWindow.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QSlider>
#include <QPushButton>
#include <QCheckBox>
#include <QStatusBar>
#include <QTimer>
#include <QFile>
#include <QCoreApplication>
#include <QThread>
#include <QSpinBox>
#include <QDebug>
#include "cpuusage.h"

static const int FPS_COUNTER_INTERVAL_MS = 1000;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), _cpuLabel(nullptr), _fpsLabel(nullptr), _frameCounter(0), _oldProcJiffies(0), _oldAllJiffies(0), _metricCPUUsageAlex(false)
{
    _demoRenderer = new DemoRenderer();

    QWidget * const dummy = new QWidget;
    {
        QVBoxLayout * const vbox = new QVBoxLayout(dummy);

        vbox->addWidget(_demoRenderer->createWidget(this), 1);

        connect(_demoRenderer, SIGNAL(frameSwapped()), this, SLOT(slot_FrameDrawn()));

        QSlider * const slider = new QSlider;
        slider->setOrientation(Qt::Horizontal);
        slider->setRange(1, 100);
        slider->setValue(50);
        connect(slider, SIGNAL(valueChanged(int)), this, SLOT(slot_ZoomChanged(int)));
        vbox->addWidget(slider);

        QHBoxLayout * const hbox = new QHBoxLayout(dummy);
        vbox->addLayout(hbox);

        QCheckBox * const lagCheckbox = new QCheckBox("Enable OpenGL Lag");
        connect(lagCheckbox, SIGNAL(toggled(bool)), this, SLOT(slot_LagToggled(bool)));
        hbox->addWidget(lagCheckbox);

        QCheckBox * const alexCheckbox = new QCheckBox("CPU Usage like Alexzk");
        connect(alexCheckbox, SIGNAL(toggled(bool)), this, SLOT(slot_AlexToggled(bool)));
        hbox->addWidget(alexCheckbox);

        QSpinBox *spinBox = new QSpinBox;
        spinBox->setRange(0, 240);
        spinBox->setSingleStep(1);
        spinBox->setValue(60);
        connect(spinBox, SIGNAL(valueChanged(int)), this, SLOT(slot_TargetFPSChanged(int)));
        hbox->addWidget(spinBox);
    }
    setCentralWidget(dummy);
    {
        QStatusBar * const statusBar = new QStatusBar;
        _cpuLabel = new QLabel("CPU: 20%");
        _fpsLabel = new QLabel("FPS: 32.4");
        statusBar->insertPermanentWidget(0, _cpuLabel);
        statusBar->insertPermanentWidget(1, _fpsLabel);
        setStatusBar(statusBar);
    }
    resize(640, 480);

    QTimer * const timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(slot_UpdateStats()));
    timer->start(FPS_COUNTER_INTERVAL_MS);
}

MainWindow::~MainWindow()
{
    qDebug() << "MainWindow : destruted";

    delete _demoRenderer;
}

void MainWindow::slot_ZoomChanged(int value)
{
    _demoRenderer->setScale(static_cast<float>(value) / 50.0);
}

void MainWindow::slot_LagToggled(bool on)
{
    _demoRenderer->setLagEnabled(on);
}

void MainWindow::slot_AlexToggled(bool on)
{
    _metricCPUUsageAlex = on;
}

void MainWindow::slot_TargetFPSChanged(int value)
{
    _demoRenderer->setTargetFPS(value);
}

void MainWindow::slot_FrameDrawn()
{
    _frameCounter++;

    if (_metricCPUUsageAlex){
        static CpuUsage usage;
        static int64_t u = usage.getCpuUsage() * 100.f;
        static uint64_t cntru = 1;
        if ((++cntru) % 10 == 0)
            u = usage.getCpuUsage() * 100.f;

        _cpuLabel->setText(QStringLiteral("CPU: %1%").arg(u));
    }
}

// https://stackoverflow.com/questions/1420426/how-to-calculate-the-cpu-usage-of-a-process-by-pid-in-linux-from-c

static int getTotalJiffies()
{
    QFile allStat(QString("/proc/stat"));
    if (!allStat.open(QIODevice::ReadOnly | QIODevice::Text))
        return 0;
    while (true)
    {
        const QString line = allStat.readLine();
        if (line.isNull())
            break;
        const QStringList words = line.split(' ');
        if (words.size() == 0)
            continue;
        if (words.at(0) == "cpu")
        {
            int totalJiffies = 0;
            for (int i = 1; i < words.size(); i++)
                totalJiffies += words.at(i).toInt();
            return totalJiffies;
        }
    }
    return 0;
}

static int getProcessJiffies(int pid)
{
    const QString pidString = QString::number(pid);
    QFile pidStat(QString("/proc/") + pidString + QString("/stat"));
    if (!pidStat.open(QIODevice::ReadOnly | QIODevice::Text))
        return 0;
    const QString line = pidStat.readLine();
    const QStringList words = line.split(' ');
    if (words.size() < 14)
        return 0;
    if (words.at(0) != pidString)
        return 0;
    return words.at(13).toInt() + words.at(14).toInt();
}

void MainWindow::slot_UpdateStats()
{
    char buffer[32];

    if (!_metricCPUUsageAlex){
        const int pid = QCoreApplication::applicationPid();
        const int newProcJiffies = getProcessJiffies(pid);
        const int newAllJiffies = getTotalJiffies();
        const int procDelta = newProcJiffies - _oldProcJiffies;
        const int allDelta = newAllJiffies - _oldAllJiffies;
        if (allDelta != 0)
        {
            const double cpuUsage = static_cast<double>(procDelta) / static_cast<double>(allDelta);
            snprintf(buffer, sizeof(buffer), "CPU: %3.1f%%", 100.0*QThread::idealThreadCount()*cpuUsage);
            _cpuLabel->setText(QString(buffer));
            _oldProcJiffies = newProcJiffies;
            _oldAllJiffies = newAllJiffies;
        }
    }
    snprintf(buffer, sizeof(buffer), "FPS: %3.1f", static_cast<double>(_frameCounter)*(1000.0/static_cast<double>(FPS_COUNTER_INTERVAL_MS)));
    _fpsLabel->setText(QString(buffer));
    _frameCounter = 0;
}
