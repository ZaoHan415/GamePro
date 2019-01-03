#include "Hexagon.h"
#include <stdexcept>
#include <QPainter>
#include <cmath>

bool Hexagon::is_inserted = false;
QMap<kind,QPixmap> Hexagon::pics = QMap<kind,QPixmap>();

Hexagon::Hexagon(kind _k,QPointF pos,qreal _width)
{
    a = _width;
    setPos(pos);
    color = QColor(200,0,0,100);
    m_kind = _k;
    if(!is_inserted){
        pics.insert(kind::entrance,QPixmap(":/Pic/Pics/entrance.png"));
        pics.insert(kind::barrier,QPixmap(":/Pic/Pics/gift.png"));
        pics.insert(kind::floor,QPixmap(":/Pic/Pics/floor.png"));
        pics.insert(kind::exit,QPixmap(":/Pic/Pics/exit.png"));
        pics.insert(kind::killer,QPixmap(":/Pic/Pics/killer.png"));
        pics.insert(kind::food,QPixmap(":/Pic/Pics/cheese.png"));
        for( QMap<kind,QPixmap>::iterator i = pics.begin(); i != pics.end() ; i++){
            if(i.key() == kind::floor)
                i.value() = i.value().scaledToHeight(81);
            else
                i.value() = i.value().scaledToHeight(60);
        }
        is_inserted = true;
    }
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
    painter->setBrush(Qt::NoBrush);
    painter->setPen(Qt::black);

    painter->drawConvexPolygon(p,6);

    int w1 = int ( -1.32*a );
    int w2 = int ( -1.1 * a);
    painter->drawPixmap(w1,w2,pics[kind::floor]);
    if(m_kind != kind::floor){
        QPixmap& now = pics[m_kind];
        QPointF offset(now.width()/2.0,now.height()/2.0);
        painter->drawPixmap(-offset,now);
    }
    /*if (m_kind == kind::entrance){
        QPixmap entrance(":/Pic/Pics/entrance.png");
        entrance = entrance.scaledToHeight(60);
        QPointF offset(entrance.width()/2.0,entrance.height()/2.0);
        painter->drawPixmap(-offset,entrance);
    }else if(m_kind == kind::exit){
        QPixmap ent(":/Pic/Pics/exit.png");
        ent = ent.scaledToHeight(60);
        QPointF offset(ent.width()/2.0,ent.height()/2.0);
        painter->drawPixmap(-offset,ent);
    }else if(m_kind == kind::barrier){
        QPixmap gift(":/Pic/Pics/gift.png");
        gift = gift.scaledToHeight(60);
        QPointF offset(gift.width()/2.0,gift.height()/2.0);
        painter->drawPixmap(-offset,gift);
    }else if(m_kind == kind::food){
        QPixmap food(":/Pic/Pics/cheese.png");
        food = food.scaledToHeight(60);
        QPointF offset(food.width()/2.0,food.height()/2.0);
                painter->drawPixmap(-offset,food);
    }else if(m_kind == kind::killer){
    QPixmap killer(":/Pic/Pics/Cat0.png");
    killer = killer.scaledToHeight(60);
    QPointF offset(killer.width()/2.0,killer.height()/2.0);
            painter->drawPixmap(-offset,killer);
    }*/

}


QRectF Hexagon::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF(-a*2 - penWidth / 2, -a*sqrt(3) - penWidth / 2,
                  4*a + penWidth, 2*a*sqrt(3) + penWidth);
}
