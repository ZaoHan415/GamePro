#include "myAnimal.h"
#include "Hexagon.h"
#include <QDebug>
#include "MainGameScene.h"
#include <QTimer>
myAnimal::myAnimal(QPoint p,QObject* pa,bool _aiMode)
{
    //新建并连接计时器
    m_timer = new QTimer(this);
    //m_timer->setSingleShot(true);
    connect(m_timer,SIGNAL(timeout()),this,SLOT(moveOneStep()));
    connect(m_timer,SIGNAL(timeout()),this,SLOT(restartTimer()));
    m_timer->start(0);
    //初始化其父类
    m_parent = pa;

    //初始位置
    position=p;
    m_hex=new Hexagon();

    aiMode = _aiMode;
}


void myAnimal::move_to_next()
{
    MainGameScene *t = static_cast<MainGameScene*>(m_parent);
    direction = temp_direction;
    QPoint step = m_hex->baseVecToNext(direction);
    if(t->isPassable(position + step)){
        position = position + step;
    }
}

void myAnimal::change_direction(int x)
{
    temp_direction=(temp_direction+x+6)%6;
}

QPointF myAnimal::posInMap()
{
    MainGameScene *t = static_cast<MainGameScene*>(m_parent);
    return t->pixelPostionInMap(position);
}

myAnimal::~myAnimal()
{
    delete m_hex;
    if(m_timer != nullptr)
        delete m_timer;
}

void myAnimal::stop()
{
    m_timer->stop();
}

void myAnimal::restartTimer()
{
    m_timer->setInterval(time_per_step);
}

void myAnimal::modifyInterval(int msec)
{
    time_per_step = msec;
}


int myAnimal::calcDirection(QPoint p)
{
    for(int i = 0 ;i<6;i++){
        if(p == m_hex->baseVecToNext(i)){
            return i;
        }
    }
    throw std::out_of_range("Wrong step for animal");
}
