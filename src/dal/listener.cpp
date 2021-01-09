#include "include/dal/listener.h"
#include <QTcpSocket>
#include <QByteArray>
#include <QString>

Listener::Listener(QObject *parent, QTcpSocket *socket) : QObject(parent)
{
    this->socket = socket;
    connect(socket, &QTcpSocket::readyRead,
            this, &Listener::readData);
}

void Listener::readData() {
    QByteArray buffer = socket->readAll();
    // buffer empty => error
    if (!buffer.isEmpty())
    {
        QString reply(buffer);
        emit getData(reply);
    }
}
