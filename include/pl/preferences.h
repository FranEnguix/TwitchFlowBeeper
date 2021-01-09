#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDialog>

#include "include/dal/audio.h"

namespace Ui {
class Preferences;
}

class Preferences : public QDialog
{
    Q_OBJECT

public:
    explicit Preferences(QWidget *parent = nullptr);
    void setAudio(Audio *audio);
    void createConnections();
    ~Preferences();

private:
    Ui::Preferences *ui;
    Audio *player;
};

#endif // PREFERENCES_H
