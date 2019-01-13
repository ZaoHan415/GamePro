#include "end.h"
#include "MainController.h"
#include "Control.h"
#include <QFile>
#include <qprocess.h>
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
    delete w;
}

void win::onSure()
{
    qApp->quit();
    QProcess::startDetached(qApp->applicationFilePath(), QStringList());
/*
    accept();
    w = new MainWindow(this);
    this->close();
    maincontroller.show();
*/
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
    delete w;
}

void lose::onSure()
{
    qApp->quit();
    QProcess::startDetached(qApp->applicationFilePath(), QStringList());
    /*
    accept();
    w = new MainWindow(this);
    maincontroller.show();
    this->hide();
    */
}
