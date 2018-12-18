#include "animalcat.h"
#include<QPainter>
#include <QDebug>
animalCat::animalCat(QPoint pos):
    myAnimal (pos)
{

}

int animalCat::turnAroundKey(int x)
{

    if(x == -1)
        return 65;//key "A"
    if(x == 1)
        return 68;//key "D"

    throw std::runtime_error("key error");
}

void animalCat::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(Qt::white);
    painter->setPen(Qt::black);
    painter->drawEllipse(QRectF(0,0,10,10));
}

void animalCat::advance(int phase)
{
    if(phase == 1){
        update();
    }
}

QRectF animalCat::boundingRect() const
{
    return  QRectF(0,0,10,10);
}
