#include "myAnimal.h"
#include "Hexagon.h"
#include <QDebug>
myAnimal::myAnimal(QPoint p)
{
    position=p;
    m_hex=new Hexagon(QPointF(0,0));
}
void myAnimal::move_to_next()
{
    QPoint step=m_hex->baseVecToNext(direction);
    position=position+step;
}
void myAnimal::change_direction(int x)
{
    direction=(direction+x+6)%6;
    qDebug()<<"cat is turning"<< direction;
    emit direction_changed(direction);
}
