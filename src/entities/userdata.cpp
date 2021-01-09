#include "include/entities/userdata.h"
#include <QString>

UserData::UserData()
{
    username = "";
    tokenOauth = "";
    channel = "";
}

QString UserData::getUsername() const
{
    return username;
}

void UserData::setUsername(const QString &value)
{
    username = value;
}

QString UserData::getTokenOauth() const
{
    return tokenOauth;
}

void UserData::setTokenOauth(const QString &value)
{
    tokenOauth = value;
}

QString UserData::getChannel() const
{
    return channel;
}

void UserData::setChannel(const QString &value)
{
    channel = value;
}
