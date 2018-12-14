#ifndef MYANIMAL_H
#define MYANIMAL_H
#include <QGraphicsItem>
#include "Hexagon.h"

class myAnimal : public QObject
{
    Q_OBJECT
public:
    myAnimal(QPoint);
    QPoint get_position()
    {
        return position;
    }
    int get_direction()
    {
        return direction;
    }
private:
    QPoint position;
    int direction;//0 to 5
    qreal time_per_step=1000;
    QTimer* m_timer;
    Hexagon* m_hex;
public slots:
    void change_direction(int x);
    //x=1or-1,while 1 means clockwise
    void move_to_next();
    void out_of_border();
signals:
    void direction_changed(int x);
};

#endif // MYANIMAL_H
