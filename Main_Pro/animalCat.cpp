#include "animalCat.h"
#include <QPainter>
#include <QDebug>
#include <QPixmap>
#include "end.h"
/*
lose *lose01;
lose01=new lose;
lose01->show();*/
animalCat::animalCat(QPoint pos,QObject * pa):
    myAnimal (pos,pa)
{
    setPos(this->posInMap());
    QString s = ":/Pic/Pics/Cat";
    for(int i = 0 ;i < 5 ;i ++)
    {
        QString temp(s);
        temp.append(QString::number(i));
        temp.append(".png");
        qDebug() << temp;
        QPixmap pic = QPixmap(temp);
        pic = pic.scaledToWidth(picWidth);
        cat_pics.append(pic);
    }
    connect(&animationTimer,SIGNAL(timeout()),this,SLOT(changePic()));
}

int animalCat::turnAroundKey(int x)
{

    if(x == -1)
        return 65;//key "A"
    if(x == 1)
        return 68;//key "D"

    throw std::runtime_error("key error");
}

void animalCat::change_new_pic()
{
    //计时画图
    QTimer *change_direction = new QTimer(this);
    connect(change_direction,SIGNAL(timeout()),this,SLOT(picture_rotate()));
    change_direction->start(1000);
}

void animalCat::picture_rotate()
{
    update();

}

void animalCat::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPixmap now = cat_pics.at(phase%5);

    //设置图片中心
    QPointF offset(now.width()/1.8,now.height()/2.5);
    //QPointF offset(0,0);
    painter->translate(+offset);

    painter->rotate(120+60*get_direction());
    painter->drawPixmap(0,0,now);

    painter->translate(-offset);
}

QRectF animalCat::boundingRect() const
{
    return  QRectF(-1000,-1000,2000,2000);
}

void animalCat::moveOneStep()
{
    animationTimer.start(picChangeStep);
    //qDebug() <<"moving";
    QPointF now_pos = posInMap();//出发位置
    move_to_next();
    QPointF then_pos = posInMap();//结束位置
    perStep = (then_pos - now_pos)/totalPhase;
}
void animalCat::catchmouse()
{
    //QPoint p = m_mice->get_position();
    //if(position cat==p){
    // emit catwins(true);
}

void animalCat::changePic()
{
    setPos(pos()+perStep);
    update();
    phase ++;
    if(phase > totalPhase)
    {
        animationTimer.stop();
        phase = 0;
    }
}
