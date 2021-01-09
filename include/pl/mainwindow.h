#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "include/dal/audio.h"
#include "include/bll/bot.h"
#include "include/bll/commandprocessor.h"
#include "include/entities/commentdata.h"
#include "include/pl/commentbox.h"
#include "include/dal/jsonparser.h"
#include <QMainWindow>
#include <QString>
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    CommandProcessor *getProcessor() const;

public slots:
    void addComment(CommentData *data);
    void askForUser();
    void askForUserIgnored();
    void showPreferences();

private:
    void loadStyles();
    void setupSignalsSlots();
    Ui::MainWindow *ui;
    JsonParser *jp;
    QList<QString> aIgnoredUsers;
    QList<QString> aHighlightUsers;

    Audio *player;
    Bot *bot;
    CommandProcessor* processor;

private slots:
    void moveScrollBarToBottom(int min, int max);
};
#endif // MAINWINDOW_H
