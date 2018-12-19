#include "animalMice.h"
#include<QPainter>
#include <QDebug>

animalMice::animalMice(QPoint pos,QObject * pa):
    myAnimal (pos,pa)
{
    setPos(this->posInMap());
}

int animalMice::turnAroundKey(int x)
{

    if(x == -1)
        return 74;//key "J"
    if(x == 1)
        return 76;//key "L"

    throw std::runtime_error("key error");
}

void animalMice::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(Qt::green);
    painter->setPen(Qt::blue);
    painter->drawEllipse(QRectF(-5,-5,10,10));
}

/*void animalCat::advance(int phase)
{
    if(phase == 1){
        move_to_next();
           }
}*/

QRectF animalMice::boundingRect() const
{
    return  QRectF(-10,-10,20,20);
}

void animalMice::moveOneStep()
{
    qDebug() <<"moving";
    move_to_next();
    QPointF now_pos = posInMap();
    setPos( now_pos );
    update();

}
void animalMice::mouse_escape()
{
    QPoint p = m_cat->get_position();
    //if(position mouse==p){
    //emit mousewins(true);
}
