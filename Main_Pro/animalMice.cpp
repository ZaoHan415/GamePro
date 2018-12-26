#include "animalMice.h"
#include<QPainter>
#include <QDebug>
#include <QPixmap>

animalMice::animalMice(QPoint pos,QObject * pa):
    myAnimal (pos,pa)
{
    setPos(this->posInMap());

    QString s = ":/Pic/Pics/Mice";
    for(int i = 1 ;i < 6 ;i ++)
    {
        QString temp(s);
        temp.append(QString::number(i));
        temp.append(".png");
        qDebug() << temp;
        QPixmap pic = QPixmap(temp);
        pic = pic.scaledToWidth(picWidth);
        mice_pics.append(pic);
    }
    connect(&animationTimer,SIGNAL(timeout()),this,SLOT(changePic()));
}

int animalMice::turnAroundKey(int x)
{

    if(x == -1)
        return 74;//key "J"
    if(x == 1)
        return 76;//key "L"

    throw std::runtime_error("key error");
}

void animalMice::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPixmap now = mice_pics.at(phase%5);

    //设置图片中心
    QPointF offset(now.width()/2.0,now.height()/2.0);
    //QPointF offset(0,0);
    painter->translate(+offset);

    painter->rotate(120+60*get_direction());
    painter->drawPixmap(0,0,now);

    painter->translate(-offset);
}


/*void animalCat::advance(int phase)
{
    if(phase == 1){
        move_to_next();
           }
}*/

QRectF animalMice::boundingRect() const
{
    return  QRectF(-1000,-1000,2000,2000);
}

void animalMice::moveOneStep()
{   
    animationTimer.start(picChangeStep);
    //qDebug() <<"moving";
    QPointF now_pos = posInMap();//出发位置
    move_to_next();
    QPointF then_pos = posInMap();//结束位置
    perStep = (then_pos - now_pos)/totalPhase;
}
void animalMice::mouse_escape()
{
    //QPoint p = m_cat->get_position();
    //if(position mouse==p){
    //emit mousewins(true);
}

void animalMice::changePic()
{
    setPos(pos()+perStep);
    update();
    phase ++;
    if(phase > totalPhase)
    {
        animationTimer.stop();
        phase = 1;
    }
}
