#include "MainController.h"
#include "Control.h"
#include <QFile>
#include <QMediaPlaylist>

MainController::MainController( QWidget *parent)
    :QDialog (parent)
{
    ui.setupUi(this);

    connect(ui.BButton,SIGNAL(clicked()),this,SLOT(onSureB()));
    connect(ui.SZ,SIGNAL(clicked()),this,SLOT(onSureS()));
    connect(ui.Quit,SIGNAL(clicked()),this,SLOT(onSureQ()));
    QFile file01("win.wav");
    player01 = new QMediaPlayer();
    player01->setMedia(QUrl("qrc:/win.wav"));
    player01->setVolume(c.isVolume);
    player01->play();
}

MainController::~MainController()
{
    delete w;
    delete player01;
}

void MainController::onSureB()
{
    w = new MainWindow(this);
    connect(this, SIGNAL( finalVolume(int) ),w,SIGNAL(VolumeSet(int)));
    emit finalVolume(isVolume);
    w->show();

    //在这里把开始界面隐藏掉了，注意可能出现的问题
    this->hide();
    list = new QMediaPlaylist();
    list->addMedia(QUrl("qrc:/bgm.wav"));
    player01->setPlaylist(list);
    player01->setVolume(c.bgmVolume);
    player01->play();
    connect(w,SIGNAL(stop()),this,SLOT(stopPlay()));
}

void MainController::onSureS()
{
    c.show();
    int ret = c.exec();
    if(ret==QDialog::Accepted)
    {
        bgmVolume = c.bgmVolume;
        isVolume = c.isVolume;
        catspeed = c.catspeed;
        micespeed = c.micespeed;
    }
}

void MainController::onSureQ()
{
    accept();
}

void MainController::stopPlay()
{
    player01->stop();
}
