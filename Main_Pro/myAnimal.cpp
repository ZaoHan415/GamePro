#include "myAnimal.h"

myAnimal::myAnimal(QPoint p)
{
    position = p;
    m_hex = new Hexagon(QPointF(0,0));
}

void myAnimal::moveToNext()
{
    QPoint step = m_hex->baseVecToNext(direction);
    position = position + step;
}

void myAnimal::changeDirection(int x)
{
    direction = x;
    emit directionChanged(x);
}
