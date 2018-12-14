#include "myAnimal.h"

myAnimal::myAnimal(QPoint p)
{
    position=p;
    m_hex=new Hexagon(QPointF(0,0));
}
void myAnimal::move_to_next()
{
    QPoint step=my_hex->baseVecToNext(direction);
    position=position+step;
}
