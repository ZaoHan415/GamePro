#ifndef MAINGAMESCENE_H
#define MAINGAMESCENE_H

#include <QGraphicsScene>

class MainGameScene : public QGraphicsScene
{
public:
    MainGameScene();
    void drawFloor();
};

#endif // MAINGAMESCENE_H
