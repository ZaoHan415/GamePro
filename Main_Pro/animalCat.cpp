#include "animalcat.h"
#include <QPainter>
#include <QDebug>
#include <QPixmap>
#include "MainGameScene.h"
#include <math.h>
#include <QVector>
animalCat::animalCat(QPoint pos,QObject * pa,bool _aiMode):
    myAnimal (pos,pa,_aiMode)
{
    setPos(this->posInMap());
    QString s = ":/Pic/Pics/Cat";
    for(int i = 0 ;i < 5 ;i ++)
    {
        QString temp(s);
        temp.append(QString::number(i));
        temp.append(".png");
        QPixmap pic = QPixmap(temp);
        pic = pic.scaledToWidth(picWidth);

        cat_pics.append(pic);

    }
    connect(&animationTimer,SIGNAL(timeout()),this,SLOT(changePic()));
    if(aiMode){
        //这里初始化一个ai出来
        catAi = new autocat(std::vector<int> ,)
    }
}

int animalCat::turnAroundKey(int x)
{

    if(x == -1)
        return 65;//key "A"
    if(x == 1)
        return 68;//key "D"

    throw std::runtime_error("key error");
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

    int theta = 120+60*get_direction();
    painter->rotate(theta);
    painter->drawPixmap(-offset,now);
    painter->rotate(-theta);
}

QRectF animalCat::boundingRect() const
{
    return  QRectF(-100,-100,200,200);
}

void animalCat::moveOneStep()
{
    animationTimer.start(picChangeStep);
    QPointF now_pos = posInMap();//出发位置
    if(aiMode){

    }
    move_to_next();
    QPointF then_pos = posInMap();//结束位置
    perStep = (then_pos - now_pos)/totalPhase;
}

void animalCat::changePic()
{
    setPos(posInMap() + perStep*phase - perStep*totalPhase);
    update();
    phase ++;
    animalMice * mi = static_cast<animalMice*>(getMice()) ;
    if(collidesWithItem(mi))
    {
        //qDebug() << "catched";
        animationTimer.stop();
        emit catwins(1);
    }
    if(phase >= totalPhase)
    {
        animationTimer.stop();
        phase = 0;
    }
}

myAnimal* animalCat::getMice()
{
    MainGameScene* scene = static_cast<MainGameScene*>(m_parent);
    return scene->mice;
}

QPainterPath animalCat::shape() const
{
    QPainterPath path;
    QVector<QPointF> list;
    int theta = 120+60*get_direction();
    double the = -double(theta)*::asin(1)*2/180.0;
    list.append(QPointF(+8.5*cos(the)-60.0*sin(the), -60.0*cos(the)-8.5*sin(the)));
    list.append(QPointF(-16.5*cos(the)-60.0*sin(the), -60.0*cos(the)+16.5*sin(the)));
    list.append(QPointF(-16.5*cos(the)-30.0*sin(the), -30.0*cos(the)+16.5*sin(the)));
    list.append(QPointF(+8.5*cos(the)-30.0*sin(the), -30.0*cos(the)-8.5*sin(the)));
    path.addPolygon(QPolygonF(list));
    path.closeSubpath();

    return path;
}
