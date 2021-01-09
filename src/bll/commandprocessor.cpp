#include "include/bll/commandprocessor.h"
#include "include/entities/commentdata.h"
#include <QRegularExpression>
#include <QTime>
#include <QDebug>

CommandProcessor::CommandProcessor(QObject *parent) : QObject(parent)
{

}


void CommandProcessor::processCommand(QString command)
{
    if (command.startsWith("PING"))
        emit pingArrived();
    else
    {
    CommentData *commentData = new CommentData;
    // reg captures user and comment
    QRegularExpression reg("^:([^!]+)![^:]+:(.*)$");
    QRegularExpressionMatch match = reg.match(command);

    QString user = match.captured(1);
    if (user != NULL)
    {
        commentData->setUsername(user);
        QString comment = match.captured(2);
        if (comment != NULL)
        {
            commentData->setComment(comment);
            QTime time = QTime::currentTime();
            commentData->setTime(&time);
            emit commentArrived(commentData);
        }
    }
    }
}
