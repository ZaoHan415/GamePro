#include "Control.h"
#include <QFile>

Rules::Rules(QWidget *parent)
    :QDialog (parent)
{
    ui.setupUi(this);

    connect(ui.pushButton,SIGNAL(clicked()),this,SLOT(onSure()));
}

Rules::~Rules()
{

}

void Rules::onSure()
{
    accept();
}

People::People(QWidget *parent)
    :QDialog (parent)
{
    ui.setupUi(this);

    connect(ui.pushButton,SIGNAL(clicked()),this,SLOT(onSure()));
}

People::~People()
{

}

void People::onSure()
{
    accept();
}

Control::Control(QWidget *parent)
    :QDialog (parent)
{
    ui.setupUi(this);

    connect(ui.PButton,SIGNAL(clicked()),this,SLOT(onSureP()));//制作人员按钮
    connect(ui.MButton,SIGNAL(clicked()),this,SLOT(onSureM()));//音乐按钮
    connect(ui.SButton,SIGNAL(clicked()),this,SLOT(onSureS()));//速度控制按钮
    connect(ui.RButton,SIGNAL(clicked()),this,SLOT(onSureR()));//规则按钮
    connect(ui.TButton,SIGNAL(clicked()),this,SLOT(quit()));//退出按钮

    QFile play01("bgm.wav");
    player01->setMedia(QUrl::fromLocalFile("bgm.wav"));
    QFile play02("cat.wav");
    player02->setMedia(QUrl::fromLocalFile("cat.wav"));
    QFile play03("mice.wav");
    player03->setMedia(QUrl::fromLocalFile("mice.wav"));

    player01->setVolume(50);
    player02->setVolume(50);
    player03->setVolume(50);

}

Control::~Control()
{

}

void Control::onSureM()
{
    musiccontroller.show();
    int ret = musiccontroller.exec();
    if(ret == QDialog::Accepted)
    {
        player01->setVolume(musiccontroller.bgmVolume);
        player02->setVolume(musiccontroller.isvolume);
        player03->setVolume(musiccontroller.isvolume);
    }
}

void Control::onSureP()
{
    people = new People;
    people->show();
}

void Control::onSureR()
{
    rules = new Rules;
    rules->show();
}

void Control::onSureS()
{
    speedcontroller01.show();
    int ret = speedcontroller01.exec();
    if(ret==QDialog::Accepted)
    {
        catspeed = speedcontroller01.catspeed;
        micespeed = speedcontroller01.micespeed;
    }
}

void Control::quit()
{
    accept();
}
