#ifndef AUDIO_H
#define AUDIO_H

#include <QObject>
#include <QAudioFormat>
#include <QAudioBuffer>
#include <QAudioOutput>

class CustomAudio : public QObject
{
    Q_OBJECT
public:
    explicit CustomAudio(QObject *parent = nullptr);
    void playBeep();

private:
    QByteArray *byteBuffer;
    QAudioFormat *format;
    QAudioOutput *audio;

signals:

};

#endif // AUDIO_H
