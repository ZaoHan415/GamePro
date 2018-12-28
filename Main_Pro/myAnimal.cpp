#include "myAnimal.h"
#include "Hexagon.h"
#include <QDebug>
#include "MainGameScene.h"
#include <QTimer>
myAnimal::myAnimal(QPoint p,QObject* pa)
{
    //新建并连接计时器
    m_timer = new QTimer(this);
    m_timer->start(time_per_step);
    connect(m_timer,SIGNAL(timeout()),this,SLOT(moveOneStep()));

   /* //计时画图
    QTimer *change_direction = new QTimer(this);
    connect(change_direction,SIGNAL(timeout()),this,SLOT(chang_new_pic()));
    change_direction->start(1000);*/

    //初始化其父类
    m_parent = pa;

    //初始位置
    position=p;
    m_hex=new Hexagon(QPointF(0,0));
}

void myAnimal::paint_new_pic()
{

}
void myAnimal::move_to_next()
{
    //qDebug() <<"direction:"<<direction;
    QPoint step = m_hex->baseVecToNext(direction);
    position = position + step;
}

void myAnimal::change_direction(int x)
{
    direction=(direction+x+6)%6;
    //emit direction_changed(direction);
}

QPointF myAnimal::posInMap()
{
    MainGameScene *t = static_cast<MainGameScene*>(m_parent);

    if(t->inThisMap(position))
    {
        emit alive(false);
    }
    return t->pixelPostionInMap(position);
}

/*void myAnimal::out_of_border()
{
    if(position.x()+position.y()>10){
        emit alive(false);
    }
}*/

myAnimal::~myAnimal()
{
    delete m_hex;
    delete m_timer;
}
