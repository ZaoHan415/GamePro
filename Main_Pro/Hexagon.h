#ifndef HEXAGON_H
#define HEXAGON_H
#include <QGraphicsItem>

class Hexagon : public QGraphicsItem
{
public:
    Hexagon(QPointF);
    void advance(int phase) override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget) override;

    QRectF boundingRect() const override;

    //六边形边长
    const qreal a = 20;

    //返回晶格基矢，i取1到6
    QPointF vecToNext(int i);

    QColor color;
};

#endif // HEXAGON_H
