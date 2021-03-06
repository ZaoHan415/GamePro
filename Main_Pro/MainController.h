#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H
#include <QDialog>
#include <QThread>
#include "ui_MainController.h"
#include "MainWindow.h"
#include "Control.h"

class MainController : public QDialog
{
    Q_OBJECT

public:
    MainController( QWidget *parent = Q_NULLPTR );
    ~MainController();
    MainWindow *w;
    Control c;

    int bgmVolume = 50;
    int isVolume = 50;
    int micespeed = 5;
    int catspeed = 5;

    QMediaPlayer *player01;
    QMediaPlaylist* list;

    bool isAi {false};

private:
    Ui::MainController ui;

private slots:
    void onSureB();
    void onSureS();
    void onSureQ();
    void onSureD();//单人模式
    void stopPlay();
signals:
    void finalVolume(int );
};

#endif // MAINCONTROLLER_H
