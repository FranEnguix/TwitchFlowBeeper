#include <QRandomGenerator>
#include <QColor>
#include <QTextStream>
#include <QDebug>
#include <QTextCodec>
#include <QFontMetrics>
#include <QResizeEvent>
#include <ui_commentbox.h>
#include "include/pl/commentbox.h"

CommentBox::CommentBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommentBox)
{
    ui->setupUi(this);
    const int max = 360;
    int hue = QRandomGenerator::global()->generateDouble() * max;
    ui->textBox->setTextColor(QColor::fromHsv(hue, 255, 255));
    QPalette palette = ui->username->palette();
    palette.setColor(QPalette::WindowText, QColor::fromHsv(hue, 255, 255));
    ui->username->setPalette(palette);
}

CommentBox::~CommentBox()
{
    delete ui;
}

CommentData *CommentBox::getData() const
{
    return data;
}

void CommentBox::setData(CommentData *value)
{
    data = value;
    ui->username->setText(data->getUsername());
    QString timeMark = QString("%1:%2").arg(
                QString::number(data->getTime()->hour()).rightJustified(2, '0'),
                QString::number(data->getTime()->minute()).rightJustified(2, '0')
                );
    ui->time->setText(timeMark);
    ui->textBox->insertPlainText(value->getComment());
}

void CommentBox::adjustCommentBoxHeight(int boxWidth, int boxHeight)
{
    QFontMetrics fontMetrics(ui->textBox->font());
    int fontHeight = fontMetrics.lineSpacing();

    int numLines = 3 +
            fontMetrics.horizontalAdvance(ui->textBox->toPlainText())
            / boxWidth;
    int totalHeight = fontHeight * numLines;
    ui->textBox->setMinimumHeight(totalHeight);
    ui->textBox->setMaximumHeight(totalHeight);
}

void CommentBox::resizeEvent(QResizeEvent *event)
{
    adjustCommentBoxHeight(
                ui->textBox->geometry().width(),
                ui->textBox->geometry().height()
    );
    QWidget::resizeEvent(event);
}
