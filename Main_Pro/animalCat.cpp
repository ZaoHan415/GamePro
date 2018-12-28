#include "animalcat.h"
#include <QPainter>
#include <QDebug>
#include <QPixmap>
#include "MainGameScene.h"
#include "end.h"

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
    QPointF offset(now.width()/2.0,now.height()/2.0);

    //int x1,y1,x2,y2;

    //QRect t = now.rect();
    //t.getCoords(&x1,&y1,&x2,&y2);

    painter->rotate(120+60*get_direction());
    //painter->drawRect(boundingRect());
    //painter->drawLine(QLineF(x1,y1,x2,y2));
    //painter->drawLine(QLineF(x1,y2,x2,y1));

    painter->drawPixmap(-offset,now);
}

QRectF animalCat::boundingRect() const
{
    return  QRectF(-100,-100,200,200);
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
    MainGameScene* scene = static_cast<MainGameScene*>(m_parent);
    scene->gameOver(1);
}

void animalCat::changePic()
{
    setPos(posInMap() + perStep*phase - perStep*totalPhase);
    update();
    phase ++;
    if(phase > totalPhase)
    {
        animationTimer.stop();
        if(this->position == getMicePos()){
            this->catchmouse();
        }
        phase = 0;
    }
   // QPoint p=this->position;
    //QDebug()<<p;
}

void animalCat::out_of_border()
{
    lose *lose_ui = new lose();
    lose_ui->show();
}

QPoint animalCat::getMicePos()
{
    MainGameScene* scene = static_cast<MainGameScene*>(m_parent);
    return scene->getMicePositon();
}
