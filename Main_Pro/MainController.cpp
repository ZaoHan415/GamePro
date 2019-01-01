#include "MainController.h"
#include "Control.h"
#include <QFile>

MainController::MainController( QWidget *parent)
    :QDialog (parent)
{
    ui.setupUi(this);

    connect(ui.BButton,SIGNAL(clicked()),this,SLOT(onSureB()));
    connect(ui.SZ,SIGNAL(clicked()),this,SLOT(onSureS()));
    connect(ui.Quit,SIGNAL(clicked()),this,SLOT(onSureQ()));
    QFile file01("win.wav");
    player01 = new QMediaPlayer;
    player01->setMedia(QUrl("qrc:/win.wav"));
    player01->setVolume(c.isVolume);
    player01->play();
}

MainController::~MainController()
{

}

void MainController::onSureB()
{
    w = new MainWindow(this);
    connect(this, SIGNAL( finalVolume(int) ),w,SIGNAL(VolumeSet(int)));
    emit finalVolume(isVolume);
    w->show();
    this->hide();
    QFile file("bgm.wav");
    player01->setMedia(QUrl("qrc:/bgm.wav"));
    player01->setVolume(c.bgmVolume);
    player01->play();
}

void MainController::onSureS()
{
    //c = new Control(this);
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
