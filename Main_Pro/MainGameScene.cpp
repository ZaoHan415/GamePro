#include "MainGameScene.h"
#include <Hexagon.h>
#include <QDebug>
MainGameScene::MainGameScene()
{
    drawFloor();
}

void MainGameScene::drawFloor()
{
    Hexagon firstHex(QPointF(0,0));
    QPointF e1 = firstHex.vecToNext(1);
    QPointF e2 = firstHex.vecToNext(2);
    //addItem(&firstHex);
    Hexagon *temp;
    for(int i = -mapWidth ; i <= mapWidth ; i++)
    {
        for(int j = -mapWidth ; j <= mapWidth ;j++)
        {
            if(inThisMap(QPoint(i,j)))
            {
                temp = new Hexagon(i*e1+j*e2/*+QPointF(0,0.0001)*/);
                qDebug()<<i<<j;
                addItem(temp);
            }
        }
    }

}

bool MainGameScene::inThisMap(QPoint p)
{
    int x = p.x();
    int y = p.y();
    if(::abs(x+y) > mapWidth)
    {
        return false;
    }
    return true;
}
