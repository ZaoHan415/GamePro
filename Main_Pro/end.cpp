#include "end.h"
#include "MainController.h"
#include "Control.h"
#include <QFile>
win::win(QWidget *parent,int _volume)
    :QDialog (parent)
{
    ui.setupUi(this);

    connect(ui.w,SIGNAL(clicked()),this,SLOT(onSure()));
    QFile file01("win.wav");
    QMediaPlayer *player01;
    player01 = new QMediaPlayer;
    player01->setMedia(QUrl("qrc:/win.wav"));
    player01->setVolume(_volume);
    player01->play();
}

win::~win()
{

}

void win::onSure()
{
    accept();
}

lose::lose(QWidget *parent,int _volume)
    :QDialog (parent)
{
    ui.setupUi(this);

    connect(ui.l,SIGNAL(clicked()),this,SLOT(onSure()));
    QFile file02("lose.wav");
    QMediaPlayer *player02;
    player02 = new QMediaPlayer;
    player02->setMedia(QUrl("qrc:/lose.wav"));
    player02->setVolume(_volume);
    player02->play();
}

lose::~lose()
{

}

void lose::onSure()
{
    accept();
}
