#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTextStream>
#include <QDateTime>
#include <QStringList>
#include <QDir>
#include <QSettings>
#include "topclass.h"
#include "qtservice.h"

class winakhDeamon : public QtService<QCoreApplication>
{
public:
    winakhDeamon(int argc, char **argv)
    : QtService<QCoreApplication>(argc, argv, "HAP Windows")
    {
        setServiceDescription("HAP, Human Applicance Portal autohotkey deamon");
        setServiceFlags(QtServiceBase::CanBeSuspended);
    }

protected:
    void start()
    {
        QCoreApplication *app = application();
        Q_UNUSED(app);
        topclass = new TopClass();
    }

    void pause()
    {
    topclass->pause();
    }

    void resume()
    {
    topclass->resume();
    }

    void stop()
    {
        QCoreApplication::quit();
    }

private:
    TopClass *topclass;
};



int main(int argc, char **argv)
{
#ifndef BUILDASNONSERVER
#if !defined(Q_OS_WIN)
    // QtService stores service settings in SystemScope, which normally require root privileges.
    // To allow testing this example as non-root, we change the directory of the SystemScope settings file.
    QSettings::setPath(QSettings::NativeFormat, QSettings::SystemScope, QDir::tempPath());
    qWarning("(Example uses dummy settings file: %s/QtSoftware.conf)", QDir::tempPath().toLatin1().constData());
#endif
    winakhDeamon service(argc, argv);
    return service.exec();
#else
    QCoreApplication app(argc, argv);
    TopClass top;
    top.start();
    return app.exec();
#endif
}








