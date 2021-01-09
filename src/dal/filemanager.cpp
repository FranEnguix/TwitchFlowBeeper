#include "include/dal/filemanager.h"
#include <QStandardPaths>
#include <QFile>
#include <QDir>
#include <QString>
#include <QDebug>

FileManager::FileManager(QObject *parent) : QObject(parent)
{
    QString path = QStandardPaths::writableLocation(
                    QStandardPaths::AppDataLocation
                    );
    pathAppData = path.left(path.lastIndexOf('/')) + "/RS/Pitiditos";
    userDataFile = pathAppData + "/userData.json";
    userAccountFile = pathAppData + "/account.json";
    setupAppDataFolders();
    QList<QString> files = {userDataFile, userAccountFile};
    setupDataFiles(files);
}

QString FileManager::getPathAppData() const
{
    return pathAppData;
}

QString FileManager::getUserDataFile() const
{
    return userDataFile;
}

QString FileManager::getPathToAccountFile() const
{
    return userAccountFile;
}

void FileManager::setupDataFiles(QList<QString> files) {
    for (const QString &file : files)
        if (!QFile::exists(file))
            createDataFile(file);
}

bool FileManager::existDataFile(QString filename) {
    QString file(pathAppData + "/" + filename);
    return QFile::exists(file);
}

void FileManager::createDataFile(QString file) {
    QString defaultFilename;
    if (file.contains("userData"))
        defaultFilename = ":/data/userData";
    else if (file.contains("account"))
        defaultFilename = ":/data/account";
    else {}
        // TODO: lanzar error

    QFile defaultFile(defaultFilename);
    if (!defaultFile.open(QIODevice::ReadOnly))
        qWarning() << "Error apertura en " + file;
    defaultFile.copy(file);
    QFile::setPermissions(file,
                          QFileDevice::ReadOwner |
                          QFileDevice::WriteOwner |
                          QFileDevice::ReadGroup |
                          QFileDevice::WriteGroup
                          );
}

void FileManager::setupAppDataFolders() {
    QDir dir;
    dir.mkpath(pathAppData);
}
