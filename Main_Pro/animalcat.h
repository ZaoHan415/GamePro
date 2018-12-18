#ifndef ANIMALCAT_H
#define ANIMALCAT_H

#include <QGraphicsItem>
#include "myAnimal.h"

class animalCat:public myAnimal,public QGraphicsItem
{
public:
    animalCat(QPoint,QObject* pa);
    int turnAroundKey(int x) override;

    void advance(int phase) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) override;
    QRectF boundingRect() const override;
public slots:
    //void move_to_next() override;
private:

};

#endif // ANIMALCAT_H
