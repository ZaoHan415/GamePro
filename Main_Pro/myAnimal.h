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
    ~myAnimal();
    QPoint get_position() { return position; }
    int get_direction(){ return direction; }

    //在子类中override，返回让它转弯的两个键，这样myAnimal类可以保证这个东西真的会转弯
    virtual int turnAroundKey(int direction) = 0;

    QPointF posInMap();

private:
    QPoint position;
    int direction = 0;//0 to 5
    int time_per_step=1000;//msecs

    //用来控制行进速度
    QTimer* m_timer;

    //新建一个临时的地板砖，用来获取地板砖的基向量
    Hexagon* m_hex;

    //指向每一个animal所在的Scene，根据需要将这个指针转换为MainGameScene类型指针
    QObject * m_parent;

protected:

public slots:
    //x=1or-1,while 1 means clockwise
    void change_direction(int x);

    void move_to_next();

   // void out_of_border();

    //纯虚函数，继承它并实现每个小动物特色的走路方式
    virtual void moveOneStep() = 0;

signals:
    void direction_changed(int x);
    void alive(bool);
};

#endif // MYANIMAL_H
