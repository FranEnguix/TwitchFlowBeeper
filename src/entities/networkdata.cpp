#include "include/entities/networkdata.h"

NetworkData::NetworkData()
{
    host = "irc.twitch.tv";
    port = 6667;
}

int NetworkData::getPort() const
{
    return port;
}

void NetworkData::setPort(int value)
{
    port = value;
}

QString NetworkData::getHost() const
{
    return host;
}

void NetworkData::setHost(const QString &value)
{
    host = value;
}
