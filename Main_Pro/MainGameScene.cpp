#include "MainGameScene.h"
#include <Hexagon.h>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include <QTimer>

MainGameScene::MainGameScene()
{

    drawFloor();

    //初始化猫老鼠位置
    miceStartPos = QPoint(0,0);
    catStartPos = QPoint(mapWidth-1,0);
    miceEndPos.append( QPoint(1-mapWidth,0) );

    //添加猫
    cat = new animalCat(catStartPos,this);
    animalCat *cat_p = static_cast<animalCat *>(cat );
    this->addItem(cat_p);
}

void MainGameScene::drawFloor()
{
    Hexagon *temp;
    for(int i = -mapWidth ; i <= mapWidth ; i++)
    {
        for(int j = -mapWidth ; j <= mapWidth ;j++)
        {
            if(inThisMap(QPoint(i,j)))
            {
                temp = new Hexagon(pixelPostionInMap(QPoint(i,j)),blockWidth);
                //qDebug()<<i<<j;
                addItem(temp);
            }
        }
    }

}

bool MainGameScene::inThisMap(QPoint p)
{
    int x = p.x();
    int y = p.y();
    if(x < -mapWidth || x > mapWidth || y < -mapWidth || y > mapWidth)
    {
        return false;
    }
    if(::abs(x+y) > mapWidth)
    {
        return false;
    }
    return true;
}

QPointF MainGameScene::pixelPostionInMap(QPoint p)
{
    Hexagon temp(QPointF(0,0),blockWidth);
    QPointF pos = p.x()*temp.vecToNext(0)+p.y()*temp.vecToNext(1);
    return pos;
}

bool MainGameScene::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::KeyPress){
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        for(int i = -1;i <= 1; i += 2){
            if(cat->turnAroundKey(i) == keyEvent->key()){
                cat->change_direction(i);
                return true;

            }
            else if(mice->turnAroundKey(i) == keyEvent->key()){
                mice->change_direction(i);
                return true;
            }
        }
    }
    return QObject::eventFilter(obj, event);
}
