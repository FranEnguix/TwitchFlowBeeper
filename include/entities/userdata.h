#ifndef USERDATA_H
#define USERDATA_H

#include <QString>

class UserData
{
public:
    UserData();
    QString getUsername() const;
    void setUsername(const QString &value);

    QString getTokenOauth() const;
    void setTokenOauth(const QString &value);

    QString getChannel() const;
    void setChannel(const QString &value);

private:
    QString username;
    QString tokenOauth;
    QString channel;
};

#endif // USERDATA_H
