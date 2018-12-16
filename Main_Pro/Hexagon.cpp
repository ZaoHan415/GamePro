#include "Hexagon.h"
#include <stdexcept>
#include <QPainter>
#include <cmath>

Hexagon::Hexagon(QPointF pos,qreal _width)
{
    a = _width;
    setPos(pos);
    color = QColor(200,0,0,100);
}

void Hexagon::advance(int phase)
{
    if(phase == 1)
    {
        update();
    }
}

QPoint Hexagon::baseVecToNext(int i)
{
    QPoint e1(1,0);
    QPoint e2(0,1);
    switch (i)
    {
    case 0:
        return e1;
    case 1:
        return e2;
    case 2:
        return -e1+e2;
    case 3:
        return -e1;
    case 4:
        return -e2;
    case 5:
        return e1-e2;
    default:
        throw std::runtime_error("Invalid use of vecToNext");
    }
}

QPointF Hexagon::vecToNext(int i)
{
    QPointF e1( 1.5*a , 0.5*a*sqrt(3) );
    QPointF e2( 0 , a*sqrt(3) );
    QPoint p = baseVecToNext(i);
    return p.x()*e1 + p.y() *e2;
}

void Hexagon::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                    QWidget *)
{
    const QPointF p[6] ={
        QPointF( -0.5*a, 0.5*a*::sqrt(3)),
        QPointF( +0.5*a, 0.5*a*::sqrt(3)),
        QPointF(  a, 0),
        QPointF( +0.5*a, -0.5*a*::sqrt(3)),
        QPointF( -0.5*a, -0.5*a*::sqrt(3)),
        QPointF( -a, 0),
    };
    painter->setBrush(color);
    painter->setPen(Qt::black);
    painter->drawConvexPolygon(p,6);
}

QRectF Hexagon::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF(-a*2 - penWidth / 2, -a*sqrt(3) - penWidth / 2,
                  4*a + penWidth, 2*a*sqrt(3) + penWidth);
}
