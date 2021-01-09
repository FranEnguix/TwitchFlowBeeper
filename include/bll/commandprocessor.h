#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H

#include "include/entities/commentdata.h"
#include <QObject>

class CommandProcessor : public QObject
{
    Q_OBJECT
public:
    explicit CommandProcessor(QObject *parent = nullptr);
    void processCommand(QString command);

signals:
    void commentArrived(CommentData *data);
    void pingArrived();

};

#endif // COMMANDPROCESSOR_H
