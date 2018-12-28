#include "MainController.h"
#include "Control.h"
#include "end.h"
#include <QMediaPlayer>
#include <QApplication>
#include <QFile>
#include <QDebug>

extern Control *c;//用全局的c（窗口）
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainController m;
    m.show();
    /*lose lose01;
    lose01.show();
    win win01;
    win01.show();
    QMediaPlayer play01;
    play01.setMedia(QUrl::fromLocalFile("qrc:/../bgm.wav"));
    play01.setVolume(50);
    play01.play();*/



/*
    QMediaPlayer *player1 = new QMediaPlayer;
    QMediaPlayer *player2 = new QMediaPlayer;
    QMediaPlayer *player3 = new QMediaPlayer;

    player1->setMedia(QUrl::fromLocalFile("bgm.wav"));
    player2->setMedia(QUrl::fromLocalFile("cat.wav"));
    player3->setMedia(QUrl::fromLocalFile("mice.wav"));

    player1->setVolume(c->bgmVolume);
    player2->setVolume(c->isVolume);
    player3->setVolume(c->isVolume);

    player1->play();//播放bgm
    player2->play();//播放猫叫声
    player3->play();//播放老鼠叫声

*/
/*
    c->micespeed;//猫的速度值
    c->catspeed;//老鼠的速度值
    如果在其他的cpp文件中需要用到速度的值，需要用表示extern Control *c

*/
/*
    win win01;//创建玩家成功的窗口
    lose lose01;//创建玩家失败的窗口
    win01.show();//显示成功的窗口
    lose01.show();//显示失败的窗口
    win01,lose01只是显示界面，不含值，不必要使用全局
*/
    return a.exec();

}
