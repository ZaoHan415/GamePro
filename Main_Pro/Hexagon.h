#ifndef HEXAGON_H
#define HEXAGON_H
#include <QGraphicsItem>

class Hexagon : public QGraphicsItem
{
private:
    qreal a;
    QColor color;
    enum class kind{entrance=0,floor,barrier,exit,food};

public:
    Hexagon(QPointF x = QPointF(0,0),qreal _width = 20);
    void advance(int phase) override;
    class exit;
//    class floor{};
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget) override;


    QRectF boundingRect() const override;

    //六边形边长


    //返回晶格基矢，i取1到6
    QPoint baseVecToNext(int i);
    QPointF vecToNext(int i);


};

#endif // HEXAGON_H
