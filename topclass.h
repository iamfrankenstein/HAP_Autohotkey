#ifndef TOPCLASS_H
#define TOPCLASS_H

#include <QObject>
#include <QThread>
#include <QtNetwork>
#include <simplecrypt.h>

class SimpleCrypt;

class TopClass : public QThread
{
    Q_OBJECT
public:
    explicit TopClass(QObject *parent = 0);
    bool ahkSend(QString pipeName ,QString data="");
    void pause()    {disabled = true;}
    void resume()   {disabled = false;}

private slots:
    void processPendingDatagrams();

private:
        QUdpSocket *udpSocket;
        QLocalSocket *ahkSocket;
        QMutex *ahkMutex;
        QString pcName;
        bool disabled;
};

#endif // TOPCLASS_H
