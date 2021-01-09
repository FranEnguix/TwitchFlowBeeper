#ifndef AUDIO_H
#define AUDIO_H

#include <QObject>
#include <QMediaPlayer>

class Audio : public QObject
{
    Q_OBJECT
public:
    explicit Audio(QObject *parent = nullptr);
    void setDefaultVolume(int level);
    void setHighlightVolume(int level);
    int getDefaultSoundLevel();
    int getHighlightSoundLevel();
    void beepDefault();
    void beepHighlight();

private:
    void setMedia();
    QMediaPlayer *playerDefault;
    QMediaPlayer *playerHighlight;

signals:

};

#endif // AUDIO_H
