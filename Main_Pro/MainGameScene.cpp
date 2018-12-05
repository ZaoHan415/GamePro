#include "MainGameScene.h"
#include <Hexagon.h>

MainGameScene::MainGameScene()
{

}

void MainGameScene::drawFloor()
{
    static Hexagon firstHex(QPointF(0,0));
    QPointF e1 = firstHex.vecToNext(1);
    QPointF e2 = firstHex.vecToNext(2);
}
