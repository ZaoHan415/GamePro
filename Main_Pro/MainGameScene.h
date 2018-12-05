#ifndef MAINGAMESCENE_H
#define MAINGAMESCENE_H

#include <QGraphicsScene>

class MainGameScene : public QGraphicsScene
{
public:
    MainGameScene();
    void drawFloor();
    const int mapWidth = 10;//地图宽度
    bool inThisMap(QPoint);//检测一对点在不在地图里
};

#endif // MAINGAMESCENE_H
