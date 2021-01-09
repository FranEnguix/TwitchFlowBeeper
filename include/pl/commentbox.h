#ifndef COMMENTBOX_H
#define COMMENTBOX_H

#include "include/entities/commentdata.h"
#include <QWidget>
#include <QString>
#include <QResizeEvent>

namespace Ui {
class CommentBox;
}

class CommentBox : public QWidget
{
    Q_OBJECT

public:
    explicit CommentBox(QWidget *parent = nullptr);
    ~CommentBox();

    CommentData *getData() const;
    void setData(CommentData *value);

protected:
    void resizeEvent(QResizeEvent *event);

private:
    Ui::CommentBox *ui;
    CommentData *data;
    void adjustCommentBoxHeight(int boxWidth, int boxHeight);
};

#endif // COMMENTBOX_H
