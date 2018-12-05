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
    int a = mapWidth - 1 ;
    Hexagon *temp;
    for(int i = 0 ; i <= a ; i++)
    {
        for(int j = -a ; j+i <= a ;j++)
        {
            temp = new Hexagon(QPointF(j*e1+(i-j)*e2));
            qDebug()<<i<<j;
            addItem(temp);
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
