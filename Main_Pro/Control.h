#ifndef CONTROL_H
#define CONTROL_H

#include <QDialog>
#include <qstring.h>
#include <QThread>
#include "ui_control.h"
#include "ui_rules.h"
#include "ui_people.h"
#include "SpeedController.h"
#include "MainWindow.h"
#include "MusicController.h"
class People: public QDialog
{
    Q_OBJECT

public:
    People(QWidget *parent = Q_NULLPTR);
    ~People();

private:
    Ui::People ui;

private slots:
    void onSure();

};

class Rules: public QDialog
{
    Q_OBJECT

public:
    Rules(QWidget *parent = Q_NULLPTR);
    ~Rules();

private:
    Ui::Rules ui;

private slots:
    void onSure();

};

class Control: public QDialog
{
    Q_OBJECT

public:
    Control(QWidget *parent = Q_NULLPTR);
    ~Control();

    bool Wopen{false};

    MusicController musiccontroller;
    speedcontroller speedcontroller01;
    People *people;
    Rules *rules;

private:
    Ui::Control ui;

    int bgmVolume{50};
    int isVolume{50};
    int catspeed{5};
    int micespeed{5};

    //QMediaPlayer *player01 = new QMediaPlayer;
    //QMediaPlayer *player02 = new QMediaPlayer;
    //QMediaPlayer *player03 = new QMediaPlayer;

private slots:
    void onSureM();
    void onSureS();
    void onSureP();
    void onSureR();
    void quit();

};




#endif // CONTROL_H
