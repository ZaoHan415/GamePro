#include "animalMice.h"
#include<QPainter>
#include <QDebug>
#include <QPixmap>
#include "MainGameScene.h"

animalMice::animalMice(QPoint pos,QObject * pa):
    myAnimal (pos,pa)
{
    setPos(this->posInMap());

    QString s = ":/Pic/Pics/Mice";
    for(int i = 0 ;i < 5 ;i ++)
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

    QPointF offset(now.width()/2.0,now.height()/2.0);

    //int x1,y1,x2,y2;

    //QRect t = now.rect();
    //t.getCoords(&x1,&y1,&x2,&y2);

    painter->rotate(120+60*get_direction());
    //painter->drawRect(now.rect());
    //painter->drawLine(QLineF(x1,y1,x2,y2));
    //painter->drawLine(QLineF(x1,y2,x2,y1));

    painter->drawPixmap(-offset,now);
}


/*void animalCat::advance(int phase)
{
    if(phase == 1){
        move_to_next();
           }
}*/

QRectF animalMice::boundingRect() const
{
    return  QRectF(-100,-100,200,200);
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
    if(this->position==QPoint(0,6))
    {
        MainGameScene* scene = static_cast<MainGameScene*>(m_parent);
        scene->gameOver(3);
    }
}

void animalMice::changePic()
{
    setPos(posInMap() + perStep*phase - perStep*totalPhase);
    update();
    phase ++;
    if(phase > totalPhase)
    {
        animationTimer.stop();
   /*     if(this->position==exit_position)
        {
            this->mouse_escape();
        }
        if(this->position==barrier_position)
        {
            this->stop();
        }*/
        phase=0;
    }
}

void animalMice::out_of_border()
{

}
