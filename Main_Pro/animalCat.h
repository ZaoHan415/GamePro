#ifndef ANIMALCAT_H
#define ANIMALCAT_H

#include <QGraphicsItem>
#include "myAnimal.h"

class animalCat:public myAnimal,public QGraphicsItem
{
public:

    animalCat(QPoint,QObject* pa);

    int turnAroundKey(int x) override;

    //void advance(int phase) override;

    //从GraphicsItem里面重载两个函数
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) override;
    QRectF boundingRect() const override;

    myAnimal *m_mice;
public slots:

    //重载move函数
    void moveOneStep() override;
    void catchmouse();
signals:
    void catwins(bool);
    //让它初始化为false
private:

};

#endif // ANIMALCAT_H
