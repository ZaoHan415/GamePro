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
    miceStartPos = QPoint(-1,0);
    catStartPos = QPoint(0,1);
    miceEndPos.append( QPoint(1-mapWidth,0) );
    miceEndPos.append( QPoint(mapWidth-1,0) );

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
                default:
                    throw std::runtime_error("a bug here");
                }
                //qDebug()<<i<<j;
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
        lose *lose_ui = new lose();
        lose_ui->show();
    }
    if(x == 3)
    {
        win *win_ui =new win(nullptr,volume);
        win_ui->show();
    }
}

QPoint MainGameScene::getMicePositon()
{
    return mice->position;
}

kind MainGameScene::blockTypeDetermine(QPoint p)
{
    for(int i = 0 ; i < miceEndPos.size();i++){
        if( p == miceEndPos.at(i) ){
            return kind::exit;
        }
    }
    return kind::floor;
}
