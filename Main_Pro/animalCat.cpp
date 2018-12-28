#include "animalcat.h"
#include <QPainter>
#include <QDebug>
#include <QPixmap>
#include "MainGameScene.h"
#include "end.h"
#include <math.h>
#include <QVector>
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
    int theta = 120+60*get_direction();
    painter->rotate(theta);

    //painter->drawLine(QLineF(x1,y1,x2,y2));
    //painter->drawLine(QLineF(x1,y2,x2,y1));

    painter->drawPixmap(-offset,now);
    painter->rotate(-theta);
    const double pi = ::asin(1)*2;
    double the = -double(theta)*pi/180.0;
    QPointF points[4] = {
          QPointF(+8.5*cos(the)-60.0*sin(the), -60.0*cos(the)-8.5*sin(the)),
          QPointF(-16.5*cos(the)-60.0*sin(the), -60.0*cos(the)+16.5*sin(the)),
          QPointF(-16.5*cos(the)-30.0*sin(the), -30.0*cos(the)+16.5*sin(the)),
          QPointF(+8.5*cos(the)-30.0*sin(the), -30.0*cos(the)-8.5*sin(the))
      };
    painter->drawConvexPolygon(points, 4);
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
    //QPoint p = m_mice->get_position();
    //if(position cat==p){
    // emit catwins(true);
}

void animalCat::changePic()
{
    setPos(posInMap() + perStep*phase - perStep*totalPhase);
    update();
    phase ++;
    if(phase > totalPhase)
    {
        animationTimer.stop();
        animalMice * mi = static_cast<animalMice*>(getMice()) ;
        if(collidesWithItem(mi))
        {
            qDebug() << "catched";
            emit catwins(1);
        }
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
