#include "include/bll/bot.h"
#include "include/dal/listener.h"
#include "include/entities/networkdata.h"
#include "include/entities/userdata.h"
#include "include/bll/commandprocessor.h"
#include "include/dal/jsonparser.h"
#include <QTcpSocket>

Bot::Bot(QObject *parent) : QObject(parent)
{
    network = new NetworkData;
    socket = new QTcpSocket;
    listener = new Listener(this, socket);
    writer = new Writer(this, socket);

    processor = new CommandProcessor;

    connect(listener, &Listener::getData,
            this, &Bot::receiveData);
    connect(processor, &CommandProcessor::pingArrived,
            this, &Bot::replyToPing);
}

void Bot::setUserData(UserData ud)
{
    user = ud;
}

UserData Bot::getUserData()
{
    return user;
}

void Bot::connectToServer() {
    socket->connectToHost(
                network->getHost(),
                network->getPort()
                );
    socket->waitForConnected();
    authBot();
}

void Bot::receiveData(QString data) {
    auto aMessages = data.split(QString("\r\n"));
    foreach (QString msg, aMessages)
        if (!msg.isEmpty()) {
            processor->processCommand(msg);
        }
}

void Bot::replyToPing() {
    QByteArray buffer;
    buffer.append("PONG");
    writer->writeData(&buffer);
}

void Bot::authBot() {
    QByteArray buffer;
    buffer.append("PASS oauth:");
    buffer.append(user.getTokenOauth());
    writer->writeData(&buffer);

    buffer.clear();
    buffer.append("NICK ");
    buffer.append(user.getUsername());
    writer->writeData(&buffer);

    buffer.clear();
    buffer.append("CAP REQ :twitch.tv/commands");
    writer->writeData(&buffer);

    buffer.clear();
    buffer.append("JOIN #");
    buffer.append(user.getChannel());
    writer->writeData(&buffer);
}

CommandProcessor *Bot::getProcessor() const
{
    return processor;
}

void Bot::sendComment(QString text) {
    QByteArray buffer;
    buffer.append("PRIVMSG #");
    buffer.append(user.getUsername());
    buffer.append(": " + text);
    writer->writeData(&buffer);
}

