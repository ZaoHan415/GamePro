#ifndef MAINGAMESCENE_H
#define MAINGAMESCENE_H

#include <QGraphicsScene>

class MainGameScene : public QGraphicsScene
{
public:
    MainGameScene();
    void drawFloor();

    //地图宽度
    const int mapWidth = 7;
    const qreal blockWidth = 15;

    //检测一个点在不在地图里
    bool inThisMap(QPoint);
    QPointF pixelPostionInMap(QPoint);
};

#endif // MAINGAMESCENE_H
