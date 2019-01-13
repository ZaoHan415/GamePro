#ifndef MYANIMAL_H
#define MYANIMAL_H
#include <QTimer>
#include "Hexagon.h"
#include <QGraphicsItem>

class myAnimal : public QObject
{
    Q_OBJECT
public:
    myAnimal(QPoint,QObject *,bool _aiMode = false);
    ~myAnimal();
    QPoint get_position() { return position; }
    int get_direction() const{ return direction; }
    int get_speed() const {return time_per_step; }
    //在子类中override，返回让它转弯的两个键，这样myAnimal类可以保证这个东西真的会转弯
    virtual int turnAroundKey(int direction) = 0;

    QPointF posInMap();

    int currant_direction{0};
    QPoint position;

    void stop();

    //修改速度
    void modifyInterval(int msec);

    void setDirection(int );

private:
    int direction = 0;//0 to 5
    int time_per_step = 500;//msecs
    int temp_direction = 0;
    //用来控制行进速度
    QTimer* m_timer;

    //新建一个临时的地板砖，用来获取地板砖的基向量
    Hexagon* m_hex;
protected:
    //指向每一个animal所在的Scene，根据需要将这个指针转换为MainGameScene类型指针
    QObject * m_parent;
    bool aiMode = false;

    //根据距离反解出转向角度，供AI使用
    int calcDirection(QPoint );
public slots:
    //x=1or-1,while 1 means clockwise
    void change_direction(int x);

    void move_to_next();


    //纯虚函数，继承它并实现每个小动物特色的走路方式
    virtual void moveOneStep() = 0;
    void restartTimer();

signals:
    void direction_changed(int x);
    void alive(bool);

};

#endif // MYANIMAL_H
