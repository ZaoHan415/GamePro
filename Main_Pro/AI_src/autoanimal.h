#ifndef AUTOANIMAL_H_INCLUDED
#define AUTOANIMAL_H_INCLUDED

#include<iostream>
#include<vector>
#include <fstream>
#include <QPoint>
/*
对自动行走的猫和老鼠的实现
局面好坏用分数表示
对可能的所有下一步造成的局面打分，选出最高分判断下一步怎么走
需要在类外
声明
std::vector<autoanimal::point>catwall;
std::vector<autoanimal::point>mousewall;


调用
void  initialize_mousewall(std::vector<autoanimal::point>&);
void   initialize_catwall(std::vector<autoanimal::point>&);
初始化墙


*/
class autoanimal{

public:
    class walls_error{};//when the txt for coords_of_wall is fragmentary, throw autoanimal::walls_error;
    class walls_error_for_cat{};//when the txt for coords_of_wall_for_cat is fragmentary, throw autoanimal::walls_error;
    struct abc
    {
        int a;
        int b;
        int c;
    };
    abc getdistance_mouse(int ,int );
    int getdistance_cat(int,int );
    int mapx(int x);
    int mapy (int y);
    QPoint nextstep();
    virtual double value(int, int)=0;
    virtual bool is_wall(QPoint)=0;
    autoanimal(QPoint mouse,QPoint cat,QPoint door1,QPoint door2);

    static std::vector<QPoint> catwall;
    static std::vector<QPoint> mousewall;

    static bool hasInitialized;

protected:
    int mousex;
    int mousey;
    int catx;
    int caty;
    int door1x;
    int door1y;
    int door2x;
    int door2y;

    virtual QPoint this_pos() = 0;

};

class autocat:public autoanimal
{
public:
    double value(int, int)override;
    autocat(QPoint mouse,QPoint cat,QPoint door1,QPoint door2) :
        autoanimal (mouse, cat, door1, door2) {
        mymap = new int*[15];
    for (int i = 0; i < 15; ++i) {
        mymap[i] = new int[15];
        for (int j = 0; j < 15; ++j)
            mymap[i][j] = -1;
    }

        initialize_mymap(mymap);
        }
    bool is_wall(QPoint) override;
     ~autocat () {
        for (int i = 0; i < 15; ++i)
            delete[] mymap[i];
        delete[] mymap;
    }
protected:
    int **mymap;
    void initialize_mymap (int **mymap);
    QPoint this_pos () override;
};

class automouse :public autoanimal
{
public:
    double value(int, int)override;
    automouse(QPoint mouse,QPoint cat,QPoint door1,QPoint door2) :
        autoanimal (mouse, cat, door1, door2) {
         ydist= getdistance_mouse (mousex, mousey);
         }
    bool is_wall(QPoint) override;
protected:
    abc ydist;
    QPoint this_pos() override;
};


void  initialize_mousewall(std::vector<QPoint>&);
void  initialize_catwall(std::vector<QPoint>&);

#endif // AUTOANIMAL_H_INCLUDED

