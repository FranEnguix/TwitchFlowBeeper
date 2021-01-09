#ifndef NETWORKDATA_H
#define NETWORKDATA_H

#include <QString>

class NetworkData
{
public:
    NetworkData();

    int getPort() const;
    void setPort(int value);

    QString getHost() const;
    void setHost(const QString &value);

private:
    QString host;
    int port;
};

#endif // NETWORKDATA_H
