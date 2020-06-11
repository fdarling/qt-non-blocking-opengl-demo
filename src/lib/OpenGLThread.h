#ifndef OPENGLTHREAD_H
#define OPENGLTHREAD_H

#include <QThread>

class OpenGLThread : public QThread
{
    Q_OBJECT
public:
    explicit OpenGLThread(QObject *parent = nullptr);

signals:

};

#endif // OPENGLTHREAD_H
