#ifndef WRITER_H
#define WRITER_H

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>

class Writer : public QObject
{
    Q_OBJECT
public:
    explicit Writer(QObject *parent = nullptr, QTcpSocket *socket = nullptr);
    bool writeData(QByteArray *buffer);

signals:



private:
    QTcpSocket *socket;

};

#endif // WRITER_H
