#ifndef ANIMALCAT_H
#define ANIMALCAT_H

#include <QGraphicsItem>
#include "myAnimal.h"

class animalCat:public myAnimal,public QGraphicsItem
{
    Q_OBJECT
public:

    animalCat(QPoint,QObject* pa);

    int turnAroundKey(int x) override;

    //void advance(int phase) override;

    //从GraphicsItem里面重载两个函数
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) override;
    QRectF boundingRect() const override;

    myAnimal *m_mice;

    //存图
    QList<QPixmap> cat_pics;
    QTimer animationTimer;
    int picWidth = 35;
    const int picChangeStep = 200;
    int phase = 0;
    QPointF perStep;

    qreal totalPhase = 20;
public slots:
    //重载move函数
    void moveOneStep() override;
    void catchmouse();
    void changePic();
signals:
    void catwins(bool);
    //让它初始化为false
private:

};

#endif // ANIMALCAT_H
