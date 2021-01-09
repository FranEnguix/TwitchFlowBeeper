#include "include/dal/customaudio.h"
#include <QDebug>
#include <QtMath>
#include <QBuffer>

CustomAudio::CustomAudio(QObject *parent) : QObject(parent)
{
    format = new QAudioFormat();
    format->setSampleRate(8000);
    format->setSampleSize(8);
    format->setSampleType(QAudioFormat::SignedInt);
    format->setChannelCount(1);
    format->setByteOrder(QAudioFormat::LittleEndian);
    format->setCodec("audio/pcm");

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    if (!info.isFormatSupported(*format)) {
        qWarning() << "Formato de audio no soportado";
    }

    float sec = 0.12;
    float freq = 19100;
    float max_value = 126;

    byteBuffer = new QByteArray();
    byteBuffer->resize(sec * format->sampleRate());
    for (int i = 0; i < (sec * format->sampleRate()); i++) {
        qreal t = (qreal)(freq * i);
        t *= (2.0 * M_PI) / format->sampleRate();
        t = qSin(t);
        // normalize sine wave [-max_value, max_value]
        t *= max_value;
        (*byteBuffer)[i] = (qint8)t;
    }

    audio = new QAudioOutput(*format, this);
}

void CustomAudio::playBeep() {
    QBuffer *input = new QBuffer(byteBuffer);
    input->open(QIODevice::ReadOnly);
    audio->start(input);
}

