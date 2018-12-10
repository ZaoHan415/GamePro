#ifndef MYANIMAL_H
#define MYANIMAL_H
#include <QTimer>
#include "Hexagon.h"
class myAnimal : public QObject
{
    Q_OBJECT
public:
    myAnimal(QPoint);
    //virtual void advance(int phase) override;
    QPoint PosT()
    {
        return position;
    }
    int Direction()
    {
        return direction;
    }
private:
    QPoint position;
    //move one unit after [time_step] mseconds
    qreal time_step = 1000;
    int direction;//from 1 to 6
    QTimer* m_timer;
    Hexagon* m_hex;
public slots:
    //intially, -1 means counter clock-wise
    //+1 means clock-wise
    void changeDirection(int x);
    void moveToNext();
    //void outOfBorder();
signals:
    void directionChanged(int x);
};

#endif // MYANIMAL_H
