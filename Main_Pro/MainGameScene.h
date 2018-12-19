#ifndef MAINGAMESCENE_H
#define MAINGAMESCENE_H

#include <QGraphicsScene>
#include "myAnimal.h"
#include "animalCat.h"
class MainGameScene : public QGraphicsScene
{
public:
    MainGameScene();

    //检测一个点在不在地图里
    bool inThisMap(QPoint);
    QPointF pixelPostionInMap(QPoint);
    myAnimal *mice;
    myAnimal *cat;
    QTimer * timer;
    bool eventFilter(QObject *obj, QEvent *event) override;
private:
    void drawFloor();

    //地图宽度
    const int mapWidth = 6;
    const qreal blockWidth = 20;

    //老鼠入口
    QPoint miceStartPos;

    //老鼠出口
    QList<QPoint> miceEndPos;

    //猫入口
    QPoint catStartPos;

};

#endif // MAINGAMESCENE_H
