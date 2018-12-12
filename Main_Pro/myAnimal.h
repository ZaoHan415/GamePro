#ifndef MYANIMAL_H
#define MYANIMAL_H
#include <QGraphicsItem>
#include "Hexagon.h"

class myAnimal : public QObject
{
    Q_OBJECT
public:
    myAnimal();
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
};

#endif // MYANIMAL_H
