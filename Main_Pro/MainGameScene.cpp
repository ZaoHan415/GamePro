#include "MainGameScene.h"
#include <Hexagon.h>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include <QTimer>
#include "end.h"

MainGameScene::MainGameScene()
{

    //初始化猫老鼠位置
    miceStartPos = QPoint(2-mapWidth,-2);
    catStartPos = QPoint(2-mapWidth,2);
    miceEndPos.append( QPoint(0,5) );
    miceEndPos.append( QPoint(mapWidth-1,-5) );

    //障碍物位置
    barrierPos.append(QPoint(0,3));
    barrierPos.append(QPoint(-1,-2));
    barrierPos.append(QPoint(3,-4));

    //食物位置
    foodPos.append(QPoint(5,-2));
    foodPos.append(QPoint(-3,2));

    //捕鼠夹位置
    killerPos.append(QPoint(0,-4));
    killerPos.append(QPoint(-2,1));

    drawFloor();

    //添加猫
    cat = new animalCat(catStartPos,this);
    animalCat *cat_p = static_cast<animalCat *>(cat );
    connect(cat_p,SIGNAL(catwins(int )),this,SLOT(gameOver(int )));
    addItem(cat_p);

    //添加老鼠
    mice = new animalMice(miceStartPos,this);
    animalMice *mice_p = static_cast<animalMice *>(mice );
    connect(mice_p,SIGNAL(mousewins(int )),this,SLOT(gameOver(int )));
    connect(mice_p,SIGNAL(mouselose(int )),this,SLOT(gameOver(int )));
    addItem(mice_p);
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
                switch (blockTypeDetermine(QPoint(i,j))) {
                case kind::exit:
                    temp = new Hexagon(kind::exit,pixelPostionInMap(QPoint(i,j)),blockWidth);
                    break;
                case kind::floor:
                    temp = new Hexagon(kind::floor,pixelPostionInMap(QPoint(i,j)),blockWidth);
                    break;
                case kind::barrier:
                    temp = new Hexagon(kind::barrier,pixelPostionInMap(QPoint(i,j)),blockWidth);
                    break;
                case kind::entrance:
                    temp = new Hexagon(kind::entrance,pixelPostionInMap(QPoint(i,j)),blockWidth);
                    break;
                case kind::food:
                    temp = new Hexagon(kind::food,pixelPostionInMap(QPoint(i,j)),blockWidth);
                    break;
                case kind::killer:
                    temp = new Hexagon(kind::killer,pixelPostionInMap(QPoint(i,j)),blockWidth);
                    break;
                }
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
    Hexagon temp(kind::floor, QPointF(0,0),blockWidth);
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

void MainGameScene::gameOver(int x)
{
    mice->stop();
    cat->stop();
    if(x == 1){
        lose *lose_ui = new lose(nullptr,volume);
        lose_ui->show();
    }
    if(x == 3)
    {
        win *win_ui =new win(nullptr,volume);
        win_ui->show();
    }
    emit stop();
}

QPoint MainGameScene::getMicePositon()
{
    return mice->position;
}

kind MainGameScene::blockTypeDetermine(QPoint p)
{
    if( p == miceStartPos ){
        return kind::entrance;
    }
    for(int i = 0 ; i < miceEndPos.size();i++){
        if( p == miceEndPos.at(i) ){
            return kind::exit;
        }

    }
    for(int i = 0 ; i < barrierPos.size();i++){
        if( p == barrierPos.at(i) ){
            return kind::barrier;
        }

    }
    for(int i = 0 ; i < foodPos.size();i++){
        if( p == foodPos.at(i) ){
            return kind::food;
        }

    }
    for(int i = 0 ; i < killerPos.size();i++){
        if( p == killerPos.at(i) ){
            return kind::killer;
        }

    }

    return kind::floor;
}

bool MainGameScene::isPassable(QPoint p)
{
    return inThisMap(p) && ( blockTypeDetermine(p) != kind::barrier);
}

MainGameScene::~MainGameScene()
{
    delete mice;
    delete cat;
    QList<QGraphicsItem*> l = items();
    for(int i = 0; i < l.size() ;i ++){
        delete l[i];
    }
}
