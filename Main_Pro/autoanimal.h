#ifndef AUTOANIMAL_H_INCLUDED
#define AUTOANIMAL_H_INCLUDED
#include<iostream>
#include<vector>
#include <fstream>
class autoanimal{

public:

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
    virtual int value(int, int)=0;
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

};

class autocat:public autoanimal
{
public:
    int value(int, int)override;
};

class automouse :public autoanimal
{
public:
    int value(int, int)override;
};

#endif // AUTOANIMAL_H_INCLUDED
