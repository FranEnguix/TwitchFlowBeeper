#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>
#include <QFile>
#include <QString>
#include <QIODevice>
#include <QList>
#include <QVariant>
#include <QJsonArray>
#include <QStringList>

#include <include/dal/jsonparser.h>

JsonParser::JsonParser(QObject *parent) : QObject(parent)
{
}

QList<QString> JsonParser::loadIgnoredUsers() {
    return loadList("ignorados");
}

void JsonParser::saveIgnoredUsers(QList<QString> list) {
    saveList("ignorados", list);
}

QList<QString> JsonParser::loadHighlightUsers() {
    return loadList("destacados");
}

void JsonParser::saveHighlightUsers(QList<QString> list) {
    saveList("destacados", list);
}

UserData JsonParser::loadAccountData() {
    UserData userData;
    QMap<QString, QVariant> root = getRootElement(pathToAccountFile);
    userData.setUsername(root["username"].toString());
    userData.setChannel(root["channel"].toString());
    userData.setTokenOauth(root["tokenOauth"].toString());
    /*QJsonValue connectionValue = QJsonValue::fromVariant(root["conexion"]);
    QJsonObject connection = connectionValue.toObject();
    userData.setUsername(connection.value("username").toString());
    userData.setChannel(connection.value("channel").toString());
    userData.setTokenOauth(connection.value("tokenOauth").toString());*/
    return userData;
}

void JsonParser::saveConnectionData(UserData userData) {
    QMap<QString, QVariant> root = getRootElement(pathToAccountFile);
    root["username"] = QVariant(userData.getUsername());
    root["channel"] = QVariant(userData.getUsername());
    root["tokerOauth"] = QVariant(userData.getUsername());
    saveRootElement(root, pathToAccountFile);
    // Cargar datos del archivo de configuración
    // QJsonObject connection = QJsonValue::fromVariant(root["conexion"]).toObject();
    /*QJsonObject connection;
    QJsonValue username = QJsonValue(userData.getUsername());
    QJsonValue channel = QJsonValue(userData.getChannel());
    QJsonValue token = QJsonValue(userData.getTokenOauth());
    connection.insert("username", username);
    connection.insert("channel", channel);
    connection.insert("tokenOauth", token);
    root["conexion"] = connection;*/
}

void JsonParser::saveList(QString listName, QList<QString> list) {
    QMap<QString, QVariant> root = getRootElement(pathToUserDataFile);
    QStringList userListRaw(list);
    QJsonArray userList = QJsonArray::fromStringList(userListRaw);
    root[listName] = userList;
    saveRootElement(root, pathToUserDataFile);
}

QList<QString> JsonParser::loadList(QString listName) {
    QMap<QString, QVariant> root = getRootElement(pathToUserDataFile);
    QList<QVariant> aRawList = root[listName].toList();
    QList<QString> aList;
    for (int i = 0; i < aRawList.size(); i++)
    {
        QString user = aRawList.at(i).toString();
        aList.append(user);
    }
    return aList;
}

QString JsonParser::getPathToUserDataFile() const
{
    return pathToUserDataFile;
}

void JsonParser::setPathToUserDataFile(const QString &value)
{
    pathToUserDataFile = value;
}

QString JsonParser::getPathToAccountFile() const
{
    return pathToAccountFile;
}

void JsonParser::setPathToAccountFile(const QString &value)
{
    pathToAccountFile = value;
}

int JsonParser::getDefaultVolume() {
    QMap<QString, QVariant> root = getRootElement(pathToUserDataFile);
    QJsonObject volume = root["volumen"].toJsonObject();
    return volume.value("espectadores").toInt();
}

int JsonParser::getHighlightVolume() {
    QMap<QString, QVariant> root = getRootElement(pathToUserDataFile);
    QJsonObject volume = root["volumen"].toJsonObject();
    return volume.value("destacados").toInt();
}

QJsonObject JsonParser::loadPreferences() {
    QMap<QString, QVariant> root = getRootElement(pathToUserDataFile);
    return root["preferencias"].toJsonObject();
}

QMap<QString, QVariant> JsonParser::getRootElement(QString pathToFile)
{
    QFile userDataFile(pathToFile);
    if (!userDataFile.open(QIODevice::ReadOnly)) {}
        // TODO: mandar error
    QByteArray userDataBytes = userDataFile.readAll();
    userDataFile.close();
    QJsonDocument userDataJson = QJsonDocument::fromJson(userDataBytes);
    return userDataJson.toVariant().toMap();
}

void JsonParser::saveRootElement(QMap<QString, QVariant> root, QString pathToFile)
{
    QFile userDataFile(pathToFile);
    QJsonDocument userDataJson = QJsonDocument::fromVariant(root);
    QByteArray userDataBytes = userDataJson.toJson(QJsonDocument::Indented);

    if (!userDataFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {}
        // TODO: mandar error
    userDataFile.write(userDataBytes);
    userDataFile.flush();
    userDataFile.close();
}
