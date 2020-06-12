#ifndef OPENGLTHREAD_H
#define OPENGLTHREAD_H

#include <QThread>
#include <functional>

class OpenGLThread : public QThread
{
public:

    using FrameFunc = std::function<void()>;

    OpenGLThread(FrameFunc callback);
    ~OpenGLThread();

    void stop();

protected:
    void run() override;
    std::atomic<bool> _running;

private:
    FrameFunc _callback;
};

#endif // OPENGLTHREAD_H
