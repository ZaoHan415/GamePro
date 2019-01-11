#ifndef AUTOANIMAL_H_INCLUDED
#define AUTOANIMAL_H_INCLUDED
#include<iostream>
#include<vector>
#include <fstream>
#include <QPoint>
class autoanimal{

public:

    struct abc
    {
        int a;
        int b;
        int c;
    };
    /*struct point {
        int x, y;
    };*/

    abc getdistance_mouse(int ,int );
    int getdistance_cat(int,int );
    int mapx(int x);
    int mapy (int y);
    QPoint nextstep(int, int);
    virtual double value(int, int)=0;
    autoanimal(QPoint mouse,QPoint cat,QPoint door1,QPoint door2);

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

};

class autocat:public autoanimal
{
public:
    double value(int, int)override;
    autocat(QPoint mouse,QPoint cat,QPoint door1,QPoint door2) :
        autoanimal (mouse, cat, door1, door2) {}
};

class automouse :public autoanimal
{
public:
    double value(int, int)override;
    automouse(QPoint mouse,QPoint cat,QPoint door1,QPoint door2) :
        autoanimal (mouse, cat, door1, door2) {}
};

#endif // AUTOANIMAL_H_INCLUDED
