#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QString>

class FileManager : public QObject
{
    Q_OBJECT
public:
    explicit FileManager(QObject *parent = nullptr);

    QString getPathAppData() const;
    QString getUserDataFile() const;
    QString getPathToAccountFile() const;

signals:

private:
    QString pathAppData;
    QString userAccountFile;
    QString userDataFile;

    void setupAppDataFolders();
    void setupDataFiles(QList<QString> files);
    bool existDataFile(QString filename);
    void createDataFile(QString filename);
};

#endif // FILEMANAGER_H
