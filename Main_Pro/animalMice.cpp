#include "animalMice.h"
#include<QPainter>
#include <QDebug>
#include <QPixmap>
#include "MainGameScene.h"
#include <cmath>
#include "myinputstream.h"

animalMice::animalMice(QPoint pos,QObject * pa,bool _aiMode):
    myAnimal (pos,pa,_aiMode)
{
    myInputStream str;
    QPoint p = str.getPos(myInput::dataType::speedDecaySetting).at(0);
    sup = p.x() / 100.0;
    inf = p.y() / 100.0;
    supSpeed = int ( sup * speed );
    infSpeed = int ( inf * speed );
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
    MainGameScene* scene = dynamic_cast<MainGameScene*>(m_parent);
    m_cat = scene->cat;
}

int animalMice::turnAroundKey(int x)
{

    if(x == 1)
        return 76;//key "L"
    if(x == -1)
        return 74;//key "J"

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
    MainGameScene* scene = dynamic_cast<MainGameScene*>(m_parent);
    if(scene->blockTypeDetermine(position) == kind::food){
        resetSpeed();
        //qDebug() << "now speed:" << get_speed();
    }
    if(scene->blockTypeDetermine(position) == kind::exit){
        emit mousewins(3);
    }
    else if(scene->blockTypeDetermine(position) == kind::killer){
        emit mousewins(1);
    }
    else{

        animationTimer.start(picChangeStep);
        //qDebug() <<"moving";
        QPointF now_pos = posInMap();//出发位置
        if(aiMode){
            automouse miceAI(get_position(),m_cat->get_position(),scene->miceEndPos[0],scene->miceEndPos[1]);
            QPoint net  = miceAI.nextstep(get_position().x(),get_position().y());
            setDirection(calcDirection(net - get_position()));
        }
        move_to_next();
        QPointF then_pos = posInMap();//结束位置
        perStep = (then_pos - now_pos)/totalPhase;
    }
}


//这段是不是没用了？
/*
void animalMice::mouse_escape()
{
    if(this->position==QPoint(-2,-5))
    {
        MainGameScene* scene = static_cast<MainGameScene*>(m_parent);
        scene->gameOver(3);
    }
}
*/

void animalMice::changePic()
{
    animationTimer.setInterval(picChangeStep);
    setPos(posInMap() + perStep*phase - perStep*totalPhase);
    update();
    phase ++;
    if(phase >= totalPhase)
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
    list.append(QPointF(-16.5*cos(the)+50.0*sin(the), +40.0*cos(the)+16.5*sin(the)));
    list.append(QPointF(+8.5*cos(the)+50.0*sin(the), +40.0*cos(the)-8.5*sin(the)));
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
    }
    picChangeStep = int ( double(get_speed()-100)/(totalPhase + 1.0) ) ;
}
