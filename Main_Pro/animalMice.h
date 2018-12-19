#ifndef ANIMALMICE_H
#define ANIMALMICE_H

#include <QGraphicsItem>
#include "myAnimal.h"

class animalMice:public myAnimal,public QGraphicsItem
{
public:
    animalMice(QPoint,QObject* pa);
    int turnAroundKey(int x) override;
    //void advance(int phase) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) override;
    QRectF boundingRect() const override;
    myAnimal *m_cat;

public slots:
    void moveOneStep() override;
    void mouse_escape();
signals:
    void mousewins(bool);
    //让它初始化为false
private:

};

#endif // ANIMALMICE_H
