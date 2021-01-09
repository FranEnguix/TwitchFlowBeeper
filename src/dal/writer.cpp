#include "include/dal/writer.h"
#include <QTcpSocket>
#include <QAbstractSocket>

Writer::Writer(QObject *parent, QTcpSocket *socket) : QObject(parent)
{
    this->socket = socket;

}


bool Writer::writeData(QByteArray *buffer) {
    if (socket->state() == QAbstractSocket::ConnectedState) {
        buffer->append("\r\n");
        socket->write(*buffer);
        return socket->waitForBytesWritten();
    }
    else
        return false;
}
