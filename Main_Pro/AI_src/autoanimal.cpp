#include"autoanimal.h"       //��Ҫһ��"coords_of_wall"��ȡǽ���� ����������
                            //��Ҫһ��"coords_of_wall_for_cat"��ȡǽ���� ������������


autocat::autocat(std::vector<int>mouse,std::vector<int>cat,std::vector<int>door1,std::vector<int>door2)
    :autoanimal(mouse,cat,door1,door2)
{
}

automouse::automouse(std::vector<int>mouse,std::vector<int>cat,std::vector<int>door1,std::vector<int>door2)
    :autoanimal(mouse,cat,door1,door2)
{
}

int autoanimal::mapx(int x)
{                                                                                //������map֮����ת��
    return 6+x;
}
int autoanimal::mapy (int y)
{
    return 6-y;
}

autoanimal::abc autoanimal::getdistance_mouse( int x1,int y1)
{

    int** mymap = new int*[13];//��������������Ϊԭ��������,��x,y����Ӧ����[6-y][6+x]Ԫ	��ʼ��Ϊ0��
    for (int i = 0; i < 13; ++i)
        mymap[i] = new int[13];
    std::ifstream myset{"coords_of_wall"};
    while (true){                                                                    //��ǽ�ͱ߽�
        int x,y;
        myset>>x>>y;
        if (!myset) break;
        mymap[mapy(y)][mapx(x)]=10000;
    }
    for (int x=-6;x<7;++x)
    {
        for (int y=-6;y<7;++y)
        {
            if (x*y<=0)
            {
                if (abs(x)+abs(y)>12) mymap[mapy(y)][mapx(x)]=10000;
            }
            if (x*y>0)
            {
                if(abs(x)+abs(y)>6)mymap[mapy(y)][mapx(x)]=10000;
            }
        }

    }


    std::vector<autoanimal::point> arrayk;
    arrayk.push_back({x1, y1});                                                        //����mapֵ
    int head=0,tail=0,step=1;
    int dx[6]{-1,-1,0,1,1,0};
    int dy[6]{0,1,1,0,-1,-1};
    while (head<=tail) {
        int st=tail;
        for (int i=head;i<=st;i++) {
            for (int j=0;j<6;j++) {
                int nx=arrayk[i].x+dx[j];int ny=arrayk[i].y+dy[j];
                if (mymap[mapy(ny)][mapx(nx)]==10000) continue;
                if (mymap[mapy(ny)][mapx(nx)]<=step) continue;
                ++tail;
                arrayk.push_back({nx, ny});
                mymap[mapy(ny)][mapx(nx)]=step;
            }
        }
        step++;
        head=st+1;
    }

   abc hhh{mymap[mapy(caty)][mapx(catx)], mymap[mapy(door1x)][mapx(door1y)],mymap[mapy(door2x)][mapx(door2y)]};
   for (int i = 0; i < 13; ++i)
        delete[] mymap[i];
    delete[] mymap;
   return hhh;
}

int automouse::value(int x1,int y1)
{
    abc x{getdistance_mouse(x1,y1)};
    int v=5*x.a-(x.b)/(ydist.b)-(x.c)/(ydist.c);
    return v;
}


autoanimal::autoanimal(std::vector<int>mouse,std::vector<int>cat,std::vector<int>door1,std::vector<int>door2):
    mousex { mouse[0] },
    mousey{mouse[1]},
    catx{cat[0]},
    caty{cat[1] },
    door1x{door1[0] },
    door1y{door1[1] },
    door2x{door2[0] },
    door2y{door2[1] },
    ydist {getdistance_mouse (mousex, mousey)}
{
    mymap = new int*[13];
    for (int i = 0; i < 13; ++i)
        mymap[i] = new int[13];
    initialize_mymap(mymap);
}

void autoanimal::initialize_mymap(int** mymap) {
std::ifstream myset{"coords_of_wall_for_cat"};
    while (true){                                                                    //��ǽ�ͱ߽�
        int x,y;
        myset>>x>>y;
        if (!myset) break;
        mymap[mapy(y)][mapx(x)]=10000;
    }
    for (int x=-6;x<7;++x)
    {
        for (int y=-6;y<7;++y)
        {
            if (x*y<=0)
            {
                if (abs(x)+abs(y)>12) mymap[mapy(y)][mapx(x)]=10000;
            }
            if (x*y>0)
            {
                if(abs(x)+abs(y)>6)mymap[mapy(y)][mapx(x)]=10000;
            }
        }

    }
    std::vector<autoanimal::point> arrayk;
    arrayk.push_back({mousex, mousey});                                                        //����mapֵ
    int head=0,tail=0,step=1;
    int dx[6]{-1,-1,0,1,1,0};
    int dy[6]{0,1,1,0,-1,-1};
    while (head<=tail) {
        int st=tail;
        for (int i=head;i<=st;i++) {
            for (int j=0;j<6;j++) {
                int nx=arrayk[i].x+dx[j];int ny=arrayk[i].y+dy[j];
                if (mymap[mapy(ny)][mapx(nx)]==10000) continue;
                if (mymap[mapy(ny)][mapx(nx)]<=step) continue;
                ++tail;
                arrayk.push_back({nx, ny});
                mymap[mapy(ny)][mapx(nx)]=step;
            }
        }
        step++;
        head=st+1;
    }

}


int autocat::value(int x1,int y1)
{
    int v=-mymap[mapy(y1)][mapx(x1)];
    return v;

}

 autoanimal::point autoanimal::nextstep(int x1,int y1)
 {
        int dx[6]{-1,-1,0,1,1,0};
        int dy[6]{0,1,1,0,-1,-1};
        autoanimal::point* line = new autoanimal::point [6];
        int val[6];
        autoanimal::point nowanimal={0,0};
        for(int i=0;i<=5;++i)
        {   nowanimal.x=x1+dx[i];
            nowanimal.y=y1+dy[i];
            int a=value(nowanimal.x,nowanimal.y);
            //std::cout<<"a value is got";
            line[i]= nowanimal;
            val[i]=a;
            //std::cout<<"end a for\n";
        }

        //std::cout<<"values are got";
        int m=0;
        int nvalue=val[0];
        for(int i=1;i<6;++i){

            if (nvalue<val[i])
            {
                nvalue=val[i];
                m=i;
            }
        }
        autoanimal::point a = line[m];
        delete []line;
        return a;
}
