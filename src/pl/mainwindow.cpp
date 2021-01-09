#include <QScrollBar>
#include <QFile>
#include <QUrl>
#include <Qt>
#include <QAction>
#include <QInputDialog>
#include <QDebug>
#include <QThread>

#include "include/pl/preferences.h"
#include "include/pl/mainwindow.h"
#include "ui_mainwindow.h"
#include "include/bll/bot.h"
#include "include/bll/commandprocessor.h"
#include "include/entities/commentdata.h"
#include "include/dal/filemanager.h"
#include "include/dal/jsonparser.h"
#include "include/dal/audio.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    loadStyles();
    player = new Audio;
    bot = new Bot;
    FileManager fm;

    jp = new JsonParser;
    jp->setPathToUserDataFile(fm.getUserDataFile());
    jp->setPathToAccountFile(fm.getPathToAccountFile());
    aIgnoredUsers = jp->loadIgnoredUsers();
    aHighlightUsers = jp->loadHighlightUsers();
    UserData userData = jp->loadAccountData();

    ui->setupUi(this);
    bot->setUserData(userData);
    bot->connectToServer();

    setupSignalsSlots();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::askForUser() {
    bool isValid;
    QString username = QInputDialog::getText(
                this, "Agregar usuario a destacados",
                "Nombre usuario", QLineEdit::Normal,
                "", &isValid);
    if (isValid && !username.isEmpty())
    {
        username = username.toLower();
        aHighlightUsers.append(username);
        jp->saveHighlightUsers(aHighlightUsers);
    }
}

void MainWindow::askForUserIgnored() {
    bool isValid;
    QString username = QInputDialog::getText(
                this, "Agregar usuario a ignorados",
                "Nombre usuario", QLineEdit::Normal,
                "", &isValid);
    if (isValid && !username.isEmpty()) {
        username = username.toLower();
        aIgnoredUsers.append(username);
        jp->saveIgnoredUsers(aIgnoredUsers);
    }
}

void MainWindow::showPreferences()
{
    Preferences p(this);
    p.setAudio(player);
    p.createConnections();
    p.exec();
}

void MainWindow::moveScrollBarToBottom(int min, int max) {
    Q_UNUSED(min);
    ui->scrollPane->verticalScrollBar()->setValue(max);
}

void MainWindow::addComment(CommentData *data) {
    if (!aIgnoredUsers.contains(data->getUsername()))
    {
        CommentBox *commentBox = new CommentBox;
        commentBox->setData(data);
        commentBox->setAttribute(Qt::WA_StyledBackground, true);
        ui->comments->addWidget(commentBox);
        if (aHighlightUsers.contains(data->getUsername()))
            player->beepHighlight();
        else
            player->beepDefault();
    }
}

void MainWindow::loadStyles()
{
    QFile styleFile(":/css/style");
    styleFile.open(QFile::ReadOnly);
    QString style = styleFile.readAll();
    qApp->setStyleSheet(style);
}

void MainWindow::setupSignalsSlots()
{
    connect(
                ui->scrollPane->verticalScrollBar(),
                SIGNAL(rangeChanged(int, int)),
                this,
                SLOT(moveScrollBarToBottom(int, int))
                );
    connect(
                ui->actionDestacarAgregar,
                &QAction::triggered,
                this,
                &MainWindow::askForUser
                );
    connect(
                ui->actionIgnorarAgregar,
                &QAction::triggered,
                this,
                &MainWindow::askForUserIgnored
                );
    connect(
                ui->actionPreferencias,
                &QAction::triggered,
                this,
                &MainWindow::showPreferences
                );
    connect(
                bot->getProcessor(),
                &CommandProcessor::commentArrived,
                this,
                &MainWindow::addComment
                );
}
