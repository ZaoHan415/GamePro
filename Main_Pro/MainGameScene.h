#ifndef MAINGAMESCENE_H
#define MAINGAMESCENE_H

#include <QGraphicsScene>
#include "myAnimal.h"
#include "animalMice.h"
#include "animalcat.h"

class MainGameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MainGameScene();

    //检测一个点在不在地图里，检测动物是否出界时直接调用
    bool inThisMap(QPoint);

    QPointF pixelPostionInMap(QPoint);
    myAnimal *mice;
    myAnimal *cat;
    bool eventFilter(QObject *obj, QEvent *event) override;
    QPoint getMicePositon();

private:
    void drawFloor();

    //地图宽度
    const int mapWidth = 6;
    const qreal blockWidth = 35;

    //老鼠入口
    QPoint miceStartPos;

    //老鼠出口
    QList<QPoint> miceEndPos;

    //猫入口
    QPoint catStartPos;

public slots:
    void gameOver(int x);

};

#endif // MAINGAMESCENE_H
