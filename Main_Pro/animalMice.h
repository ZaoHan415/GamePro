#ifndef ANIMALMICE_H
#define ANIMALMICE_H

#include <QGraphicsItem>
#include "myAnimal.h"

class animalMice:public myAnimal,public QGraphicsItem
{
    Q_OBJECT
public:
    animalMice(QPoint,QObject* pa,bool _aiMode = 0);
    int turnAroundKey(int x) override;

    //void advance(int phase) override;

    //从GraphicsItem里面重载两个函数

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    myAnimal *m_cat;
private:
    //存图
    QList<QPixmap> mice_pics;
    QTimer animationTimer;
    int picWidth = 25;
    int picChangeStep = 30;
    int phase = 0;
    QPointF perStep;

    qreal totalPhase = 10;

    int speedChangePhase = 0;

    //速度上（下）界
    int speed = 500;
    double sup;
    double inf;

    int supSpeed;
    int infSpeed;
    //速度衰减共用的格数
    const int totalSpeedPhase = 15;

    void changeSpeed();
    void resetSpeed();
public slots:
    //重载move函数
    void moveOneStep() override;
    //void mouse_escape();
    void changePic();
signals:
    void mousewins(int);
    //void mouselose(int);

};

#endif // ANIMALMICE_H
