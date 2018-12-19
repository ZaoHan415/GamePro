#include "animalCat.h"
#include <QPainter>
#include <QDebug>
animalCat::animalCat(QPoint pos,QObject * pa):
    myAnimal (pos,pa)
{
    setPos(this->posInMap());
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
    painter->drawEllipse(QRectF(-5,-5,10,10));
}

QRectF animalCat::boundingRect() const
{
    return  QRectF(-10,-10,20,20);
}

void animalCat::moveOneStep()
{
    qDebug() <<"moving";
    move_to_next();
    QPointF now_pos = posInMap();
    setPos( now_pos );
    update();

}
void animalCat::catchmouse()
{
    QPoint p = m_mice->get_position();
    //if(position cat==p){
     // emit catwins(true);
}
