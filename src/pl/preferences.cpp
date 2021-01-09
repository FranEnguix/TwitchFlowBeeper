#include "include/pl/preferences.h"
#include "ui_preferences.h"

Preferences::Preferences(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Preferences)
{
    ui->setupUi(this);
    ui->slViewers->setTracking(true);
    ui->slHighlights->setTracking(true);
}

void Preferences::setAudio(Audio *audio)
{
    player = audio;
    ui->slViewers->setSliderPosition(audio->getDefaultSoundLevel());
    ui->slHighlights->setSliderPosition(audio->getHighlightSoundLevel());
}

void Preferences::createConnections()
{
    connect(
                ui->slViewers,
                &QSlider::valueChanged,
                player,
                &Audio::setDefaultVolume
            );
    connect(
                ui->slHighlights,
                &QSlider::valueChanged,
                player,
                &Audio::setHighlightVolume
            );
}


Preferences::~Preferences()
{
    delete ui;
}
