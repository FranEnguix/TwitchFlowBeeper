#ifndef BOT_H
#define BOT_H

#include <QObject>
#include <QString>
#include "include/dal/listener.h"
#include "include/dal/writer.h"
#include "include/entities/networkdata.h"
#include "include/entities/userdata.h"
#include "commandprocessor.h"

class Bot : public QObject
{
    Q_OBJECT
public:
    explicit Bot(QObject *parent = nullptr);

    void setUserData(UserData ud);
    UserData getUserData();
    void connectToServer();
    void sendComment(QString text);

    CommandProcessor *getProcessor() const;

signals:

private slots:
    void receiveData(QString data);
    void replyToPing();

private:
    void authBot();

    NetworkData *network;
    UserData user;

    CommandProcessor *processor;
    QTcpSocket *socket;
    Listener *listener;
    Writer *writer;
};

#endif // BOT_H
