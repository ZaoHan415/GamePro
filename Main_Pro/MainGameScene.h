#ifndef MAINGAMESCENE_H
#define MAINGAMESCENE_H

#include <QGraphicsScene>
#include "myAnimal.h"
#include "animalMice.h"
#include "animalcat.h"
#include "MusicController.h"

class MainGameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MainGameScene();
    ~MainGameScene() override;
    //检测一个点在不在地图里
    bool inThisMap(QPoint);

    //一个点在地图上且不是障碍物时返回true，检测动物是否出界时直接调用
    bool isPassable(QPoint);

    QPointF pixelPostionInMap(QPoint);
    myAnimal *mice;
    myAnimal *cat;
    bool eventFilter(QObject *obj, QEvent *event) override;
    QPoint getMicePositon();
    kind blockTypeDetermine(QPoint);

    int volume = 50;

private:
    void drawFloor();

    //地图宽度
    const int mapWidth = 5;
    const qreal blockWidth = 35;

    //老鼠入口
    QPoint miceStartPos;

    //老鼠出口
    QList<QPoint> miceEndPos;

    //障碍物
    QList<QPoint> barrierPos;

    //食物
    QList<QPoint> foodPos;

    //猫入口
    QPoint catStartPos;

public slots:
    void gameOver(int x);
    void setVolume(int x){
        volume = x;
        //qDebug() << "volume:"<<x;
    }
signals:
    void stop();
};

#endif // MAINGAMESCENE_H
