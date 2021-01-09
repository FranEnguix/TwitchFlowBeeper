#include "include/dal/audio.h"

Audio::Audio(QObject *parent) : QObject(parent)
{
    playerDefault = new QMediaPlayer;
    playerHighlight = new QMediaPlayer;
    setMedia();
}

void Audio::setDefaultVolume(int level = 50)
{
    qDebug() << "Default   " + QString::number(level);
    playerDefault->setVolume(level);
}

void Audio::setHighlightVolume(int level = 50)
{
    qDebug() << "Highlight " + QString::number(level);
    playerHighlight->setVolume(level);
}

int Audio::getDefaultSoundLevel()
{
    return playerDefault->volume();
}

int Audio::getHighlightSoundLevel()
{
    return playerHighlight->volume();
}

void Audio::beepDefault()
{
    playerDefault->play();
}

void Audio::beepHighlight()
{
    playerHighlight->play();
}

void Audio::setMedia()
{
    playerDefault->setMedia(QUrl("qrc:/audio/default"));
    playerHighlight->setMedia(QUrl("qrc:/audio/highlight"));
}
