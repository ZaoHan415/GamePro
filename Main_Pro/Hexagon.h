#ifndef HEXAGON_H
#define HEXAGON_H

#include <QGraphicsItem>
#include <QMap>

//地板砖的种类标识
enum class kind{entrance,floor,barrier,exit,food,killer};


class Hexagon : public QGraphicsItem
{
private:
    //六边形边长
    qreal a;
    QColor color;
public:
    kind m_kind = kind::floor;
    Hexagon(kind _k = kind::floor,QPointF x = QPointF(0,0),qreal _width = 20);
    void advance(int phase) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget) override;


    QRectF boundingRect() const override;

    static QMap<kind,QPixmap> pics;
    static bool is_inserted;
    //返回晶格基矢，i取1到6
    QPoint baseVecToNext(int i);
    QPointF vecToNext(int i);
};

#endif // HEXAGON_H
