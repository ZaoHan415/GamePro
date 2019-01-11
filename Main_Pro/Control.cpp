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
    connect(ui.RButton,SIGNAL(clicked()),this,SLOT(onSureR()));//规则按钮
    connect(ui.TButton,SIGNAL(clicked()),this,SLOT(quit()));//退出按钮

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
        bgmVolume = musiccontroller.bgmVolume;
        isVolume = musiccontroller.isvolume;
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

void Control::quit()
{
    accept();
}
