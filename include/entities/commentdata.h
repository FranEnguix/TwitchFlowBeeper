#ifndef COMMENTDATA_H
#define COMMENTDATA_H

#include <QString>
#include <QTime>

class CommentData
{
public:
    CommentData();

    QString getUsername() const;
    void setUsername(const QString &value);

    QString getComment() const;
    void setComment(const QString &value);

    QTime *getTime() const;
    void setTime(QTime *value);

private:
    QString username;
    QString comment;
    QTime *time;
};

#endif // COMMENTDATA_H
