#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QObject>
#include <QString>
#include <QList>

#include "include/entities/userdata.h"

class JsonParser : public QObject
{
    Q_OBJECT
public:
    explicit JsonParser(QObject *parent = nullptr);

    QString getPathToUserDataFile() const;
    void setPathToUserDataFile(const QString &value);

    QString getPathToAccountFile() const;
    void setPathToAccountFile(const QString &value);

    QList<QString> loadHighlightUsers();
    void saveHighlightUsers(QList<QString> list);

    QList<QString> loadIgnoredUsers();
    void saveIgnoredUsers(QList<QString> list);

    UserData loadAccountData();
    void saveConnectionData(UserData userData);

    int getDefaultVolume();
    int getHighlightVolume();

private:
    QList<QString> loadList(QString listName);
    void saveList(QString listName, QList<QString> list);
    QJsonObject loadPreferences();
    QMap<QString, QVariant> getRootElement(QString pathToFile);
    void saveRootElement(QMap<QString, QVariant> root, QString pathToFile);
    QString pathToUserDataFile;
    QString pathToAccountFile;


signals:

};

#endif // JSONPARSER_H
