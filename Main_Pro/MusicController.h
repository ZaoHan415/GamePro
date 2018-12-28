#ifndef MUSICCONTROLLER_H
#define MUSICCONTROLLER_H
#include <QDialog>
#include "ui_MusicController.h"
#include <qstring.h>
#include <QThread>
#include <QMediaPlayer>

class MusicController : public QDialog
{
    Q_OBJECT

public:
    MusicController(QWidget *parent = Q_NULLPTR);
    ~MusicController();
    int bgmVolume{50};
    int isvolume{50};

private:
    Ui::MusicController ui;

private slots:
    void onSureMusic();
    void setBackgroundValue(int value);
    void setISsound(int value);
};
#endif // MUSICCONTROLLER_H
