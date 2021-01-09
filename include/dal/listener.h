#ifndef LISTENER_H
#define LISTENER_H

#include <QObject>
#include <QTcpSocket>

class Listener : public QObject
{
    Q_OBJECT
public:
    explicit Listener(QObject *parent = nullptr, QTcpSocket *socket = nullptr);

signals:
    void getData(QString data);

public slots:
    void readData();

private:
    QTcpSocket *socket;

};

#endif // LISTENER_H
