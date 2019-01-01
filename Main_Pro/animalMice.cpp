#include "animalMice.h"
#include<QPainter>
#include <QDebug>
#include <QPixmap>
#include "MainGameScene.h"
#include <cmath>

animalMice::animalMice(QPoint pos,QObject * pa):
    myAnimal (pos,pa)
{
    setPos(this->posInMap());
    resetSpeed();
    QString s = ":/Pic/Pics/Mice";
    for(int i = 0 ;i < 5 ;i ++)
    {
        QString temp(s);
        temp.append(QString::number(i));
        temp.append(".png");
        //qDebug() << temp;
        QPixmap pic = QPixmap(temp);
        pic = pic.scaledToWidth(picWidth);
        mice_pics.append(pic);
    }
    connect(&animationTimer,SIGNAL(timeout()),this,SLOT(changePic()));
   // animationTimer.start(picChangeStep);
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
    int theta = 120+60*get_direction();
    painter->rotate(theta);
    painter->drawPixmap(-offset,now);
}

QRectF animalMice::boundingRect() const
{
    return  QRectF(-100,-100,200,200);
}

void animalMice::moveOneStep()
{   
    changeSpeed();
    MainGameScene* scene = static_cast<MainGameScene*>(m_parent);
    if(scene->blockTypeDetermine(position) == kind::exit){
        emit mousewins(3);
        stop();
    }
    else{
        animationTimer.start(picChangeStep);
        //qDebug() <<"moving";
        QPointF now_pos = posInMap();//出发位置
        move_to_next();
        QPointF then_pos = posInMap();//结束位置
        perStep = (then_pos - now_pos)/totalPhase;
    }
}
void animalMice::mouse_escape()
{
    if(this->position==QPoint(-2,-5))
    {
        MainGameScene* scene = static_cast<MainGameScene*>(m_parent);
        scene->gameOver(3);
    }
}

void animalMice::changePic()
{
    animationTimer.setInterval(picChangeStep);
    setPos(posInMap() + perStep*phase - perStep*totalPhase);
    update();
    phase ++;
    if(phase > totalPhase)
    {
        animationTimer.stop();
        phase=0;
    }
}

QPainterPath animalMice::shape() const
{
    QPainterPath path;
    QVector<QPointF> list;
    int theta = 120+60*get_direction();
    double the = -double(theta)*::asin(1)*2/180.0;
    list.append(QPointF(+8.5*cos(the)-50.0*sin(the), -50.0*cos(the)-8.5*sin(the)));
    list.append(QPointF(-16.5*cos(the)-50.0*sin(the), -50.0*cos(the)+16.5*sin(the)));
    list.append(QPointF(-16.5*cos(the)+60.0*sin(the), +40.0*cos(the)+16.5*sin(the)));
    list.append(QPointF(+8.5*cos(the)+60.0*sin(the), +40.0*cos(the)-8.5*sin(the)));
    path.addPolygon(QPolygonF(list));
    path.closeSubpath();

    return path;
}

void animalMice::resetSpeed()
{
    speedChangePhase = 0;
    modifyInterval(supSpeed);
    picChangeStep = int ( double(get_speed()-200)/(totalPhase + 1.0) ) ;
}

void animalMice::changeSpeed()
{
    if(speedChangePhase <= totalPhase ){
        modifyInterval(supSpeed + (infSpeed - supSpeed)/totalSpeedPhase * speedChangePhase );
        speedChangePhase ++ ;
        //qDebug() << "now speed:" << get_speed();
    }
    picChangeStep = int ( double(get_speed()-200)/(totalPhase + 1.0) ) ;
}
