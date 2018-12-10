#ifndef MYANIMAL_H
#define MYANIMAL_H
#include <QGraphicsItem>

class myAnimal : public QGraphicsItem
{
public:
    myAnimal();
private:
    int direction;
};

#endif // MYANIMAL_H
