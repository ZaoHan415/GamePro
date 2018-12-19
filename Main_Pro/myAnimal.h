#ifndef MYANIMAL_H
#define MYANIMAL_H
#include <QTimer>
#include "Hexagon.h"
#include <QGraphicsItem>

class myAnimal : public QObject
{
    Q_OBJECT
public:
    myAnimal(QPoint,QObject *);
    QPoint get_position() { return position; }
    int get_direction(){ return direction; }

    //在子类中override，返回让它转弯的两个键
    virtual int turnAroundKey(int direction) = 0;
    QPointF posInMap();

private:
    QPoint position;
    int direction = 0;//0 to 5
    int time_per_step=1000;//msecs
    QTimer* m_timer;
    Hexagon* m_hex;
    QObject * m_parent;
protected:

public slots:
    void change_direction(int x);
    //x=1or-1,while 1 means clockwise
    void move_to_next();
    void out_of_border();
    virtual void moveOneStep() = 0;
signals:
    void direction_changed(int x);
    void alive(bool);
};

#endif // MYANIMAL_H
