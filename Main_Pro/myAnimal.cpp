#include "myAnimal.h"
#include "Hexagon.h"
#include <QDebug>
#include "MainGameScene.h"
#include <QTimer>
myAnimal::myAnimal(QPoint p,QObject* parentads)
{
    m_timer = new QTimer(this);
    m_timer->start(time_per_step);
    connect(m_timer,SIGNAL(timeout()),this,SLOT(moveOneStep()));
    m_parent = parentads;
    position=p;
    m_hex=new Hexagon(QPointF(0,0));
}

void myAnimal::move_to_next()
{
    qDebug() <<"direction:"<<direction;
    QPoint step=m_hex->baseVecToNext(direction);
    position=position+step;
}

void myAnimal::change_direction(int x)
{
    direction=(direction+x+6)%6;
    emit direction_changed(direction);
}

QPointF myAnimal::posInMap()
{
    MainGameScene *t = static_cast<MainGameScene*>(m_parent);
    return t->pixelPostionInMap(position);
}
void myAnimal::out_of_border()
{
    if(position.x()+position.y()>10){
        emit alive(false);
    }

}
