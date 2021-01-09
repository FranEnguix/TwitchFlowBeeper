#include "include/entities/commentdata.h"

CommentData::CommentData()
{

}

QString CommentData::getUsername() const
{
    return username;
}

void CommentData::setUsername(const QString &value)
{
    username = value;
}

QString CommentData::getComment() const
{
    return comment;
}

void CommentData::setComment(const QString &value)
{
    comment = value;
}

QTime *CommentData::getTime() const
{
    return time;
}

void CommentData::setTime(QTime *value)
{
    time = value;
}
