#ifndef ANIMALMICE_H
#define ANIMALMICE_H

#include <QGraphicsItem>
#include "myAnimal.h"

class animalMice:public myAnimal,public QGraphicsItem
{
    Q_OBJECT
public:
    animalMice(QPoint,QObject* pa);
    int turnAroundKey(int x) override;

    //void advance(int phase) override;

    //从GraphicsItem里面重载两个函数

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) override;
    QRectF boundingRect() const override;
    myAnimal *m_cat;

    //存图
    QList<QPixmap> mice_pics;
    QTimer animationTimer;
    int picWidth = 25;
    const int picChangeStep = 30;
    int phase = 0;
    QPointF perStep;

    qreal totalPhase = 10;

public slots:
    //重载move函数
    void moveOneStep() override;
    void mouse_escape();
    void changePic();

    void out_of_border() override;
signals:
    void mousewins(bool);
    //让它初始化为false
private:

};

#endif // ANIMALMICE_H
