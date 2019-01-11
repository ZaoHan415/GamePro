#ifndef AUTOANIMAL_H_INCLUDED
#define AUTOANIMAL_H_INCLUDED
#include<iostream>
#include<vector>
#include <fstream>
/*
对自动行走的猫和老鼠的实现
局面好坏用分数表示
对可能的所有下一步造成的局面打分，选出最高分判断下一步怎么走




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
    struct point {
        int x, y;
    };
    abc getdistance_mouse(int ,int );
    int getdistance_cat(int,int );
    int mapx(int x);
    int mapy (int y);
    point nextstep(int, int);
    virtual double value(int, int)=0;
    virtual bool is_wall(point)=0;
    autoanimal(std::vector<int>mouse,std::vector<int>cat,std::vector<int>door1,std::vector<int>door2);

    ~autoanimal () {
        for (int i = 0; i < 13; ++i)
            delete[] mymap[i];
        delete[] mymap;

    }

protected:
    int mousex;
    int mousey;
    int catx;
    int caty;
    int door1x;
    int door1y;
    int door2x;
    int door2y;
    int **mymap;
    void initialize_mymap (int **mymap);
    abc ydist;
    std::vector<point> mousewall;
    void initialize_mousewall(std::vector<point>);
    std::vector<point> catwall;
    void initialize_catwall(std::vector<point>);
};

class autocat:public autoanimal
{
public:
    double value(int, int)override;
    autocat(std::vector<int>mouse,std::vector<int>cat,std::vector<int>door1,std::vector<int>door2) :
        autoanimal (mouse, cat, door1, door2) {}
    bool is_wall(point) override;
};

class automouse :public autoanimal
{
public:
    double value(int, int)override;
    automouse(std::vector<int>mouse,std::vector<int>cat,std::vector<int>door1,std::vector<int>door2) :
        autoanimal (mouse, cat, door1, door2) {}
    bool is_wall(point) override;
};

#endif // AUTOANIMAL_H_INCLUDED
