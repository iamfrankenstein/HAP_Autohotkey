#include <QCoreApplication>
#include "topclass.h"
#include <QDebug>
#include "simplecrypt.h"
#include "TopClass.h"

TopClass::TopClass(QObject *parent) :
    QThread(parent)
{
    ahkMutex = new QMutex(QMutex::NonRecursive);

    udpSocket = new QUdpSocket(this);
    udpSocket->bind(45454, QUdpSocket::ShareAddress);

    ahkSocket = new QLocalSocket(this);

    pcName = "Supperlappie";
    disabled = false;

    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(processPendingDatagrams()));
}

bool TopClass::ahkSend(QString pipeName, QString data)
{
    ahkMutex->lock();
    ahkSocket->connectToServer(pipeName,QIODevice::ReadWrite| QIODevice::Unbuffered);
    if (ahkSocket->error() == QLocalSocket::ServerNotFoundError)
    {
        qDebug()<<"Connection error";
        qDebug()<<ahkSocket->errorString() << ahkSocket->error();
        return false;
    }
    else
        qDebug()<<"Connection succesfull";

    ahkSocket->write(data.toLocal8Bit());
    ahkSocket->flush();
    ahkSocket->disconnectFromServer();
    delete ahkSocket;
    ahkSocket = new QLocalSocket(this);
    ahkMutex->unlock();
    return true;
}

void TopClass::processPendingDatagrams()
{
    if (disabled)
        return;

    SimpleCrypt crypto(Q_UINT64_C(0x0c2ad4a4acb9f023)); //some random number
    QString buffer;

    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());
        buffer = QString(datagram);
    }

    QStringList Data(crypto.decryptToString(buffer).split("|"));
    if (!QString::compare(Data.first(),pcName))
            ahkSend("ahkSend",Data.last());
}
