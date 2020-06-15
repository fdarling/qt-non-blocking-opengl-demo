#include <QtGlobal>
#include <QFile>

#include "cpuusage.h"
#include <chrono>

#ifdef Q_OS_LINUX
    #include <sys/vfs.h>
    #include <sys/types.h>
    #include <unistd.h>

    //USER_HZ detection, from openssl code
    #ifndef HZ
        #if defined(_SC_CLK_TCK) \
            && (!defined(OPENSSL_SYS_VMS) || __CTRL_VER >= 70000000)
            #define HZ ((double)sysconf(_SC_CLK_TCK))
        #else
            #ifndef CLK_TCK
                #ifndef _BSD_CLK_TCK_ /* FreeBSD hack */
                    #define HZ  100.0
                #else /* _BSD_CLK_TCK_ */
                    #define HZ ((double)_BSD_CLK_TCK_)
                #endif
            #else /* CLK_TCK */
                #define HZ ((double)CLK_TCK)
            #endif
        #endif
    #endif
#endif

CpuUsage::CpuUsage()
{
}

double CpuUsage::getCpuUsage()
{
    constexpr static double ALPHA = 0.1;

    using namespace std::chrono;
    auto old  = cputime;
    auto oldt = lastCheck;

    lastCheck = Clock::now();
    updateStatFromFs();

    const auto dt = std::max(1l, std::abs(duration_cast<milliseconds>(lastCheck - oldt).count()));

    const double sample = 1.0 * (cputime - old) / dt;

    if (cpu_usage < 0)
        cpu_usage = std::abs(sample);
    else
        cpu_usage = (1.0 - ALPHA) * cpu_usage + ALPHA * sample;

    if (cpu_usage < 0)
        cpu_usage = std::abs(sample);

    return cpu_usage;
}

int CpuUsage::updateStatFromFs()
{
#ifdef Q_OS_LINUX
    const QString pidString = QString::number(getpid());
    QFile pidStat(QString("/proc/") + pidString + QString("/stat"));
    if (!pidStat.open(QIODevice::ReadOnly | QIODevice::Text))
        return -1;
    const QString line = pidStat.readLine();
    const QStringList words = line.split(' ');
    if (words.size() < 14)
        return -1;
    if (words.at(0) != pidString)
        return -1;
    cputime = (words.at(13).toInt() + words.at(14).toInt()) * 1000 / HZ;
#else
#error "Not Implemented for this OS"
#endif
    return 0;
}
