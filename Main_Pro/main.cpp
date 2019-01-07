#include "MainController.h"
#include "Control.h"
#include "end.h"
#include <QMediaPlayer>
#include <QApplication>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainController m;
    m.show();




/*

    我把音乐播放器的定义放在了Control.h文件中
    播放直接
    player01->play();
    player02->play();
    player03->play();

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
