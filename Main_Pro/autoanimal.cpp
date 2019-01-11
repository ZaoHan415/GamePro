#include"autoanimal.h"       //��Ҫһ��"coords_of_wall"��ȡǽ���� ���������
                            //��Ҫһ��"coords_of_wall_for_cat"��ȡǽ���� �����������

int autoanimal::mapx(int x)
{                                                                                //������map֮���ת��
    return 7+x;
}
int autoanimal::mapy (int y)
{
    return 7-y;
}

autoanimal::abc autoanimal::getdistance_mouse( int x1,int y1)
{
    int** mymap = new int*[15];//�������������Ϊԭ�������,��x,y����Ӧ����[6-y][6+x]Ԫ	��ʼ��Ϊ0��
    for (int i = 0; i < 15; ++i)
        mymap[i] = new int[15];
    for (auto a:mousewall)
    {
        mymap[mapy(a.y)][mapx(a.x)]=10000;
    }
    for (int x=-7;x<8;++x)
    {
        for (int y=-7;y<8;++y)
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

   autoanimal::abc hhh{mymap[mapy(caty)][mapx(catx)], mymap[mapy(door1y)][mapx(door1x)],mymap[mapy(door2y)][mapx(door2x)]};
   for (int i = 0; i < 15; ++i)
        delete[] mymap[i];
    delete[] mymap;
   return hhh;
}

double automouse::value(int x1,int y1)
{   //std::cout<<"5";
    automouse::abc x{getdistance_mouse(x1,y1)};
    //std::cout<<"6";
    int b2=ydist.b;
    if (b2==0)b2=0.1;
    int c1=ydist.c;
    if (c1==0)c1=0.1;
     //std::cout<<"8";

    double v=5*x.a-double(x.b)/b2-double(x.c)/c1;
    //std::cout<<"8";
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
    door2y{door2[1] }

{
    mymap = new int*[15];
    for (int i = 0; i < 15; ++i)
        mymap[i] = new int[15];
    std::cout<<"01";
    initialize_mymap(mymap);
    initialize_mousewall(mousewall);
    initialize_catwall(catwall);
    ydist= getdistance_mouse (mousex, mousey);
}

void autoanimal::initialize_mymap(int** mymap) {
for (auto a:catwall)
    {
        mymap[mapy(a.y)][mapx(a.x)]=10000;
    }

    for (int x=-7;x<8;++x)
    {
        for (int y=-7;y<8;++y)
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

void autoanimal::initialize_mousewall(std::vector<point>mousewall)
{   std::fstream s("coords_of_wall");
    while(true)
    {
        point a;
        s>>a.x;
        if(!s) break;
        s>>a.y;
        if(!s) throw autoanimal::walls_error{};
        mousewall.push_back(a);

    }

}


void autoanimal::initialize_catwall(std::vector<point>catwall)
{   std::fstream s("coords_of_wall_for_cat");
    while(true)
    {
        point a;
        s>>a.x;
        if(!s) break;
        s>>a.y;
        if(!s) throw autoanimal::walls_error_for_cat{};
        mousewall.push_back(a);

    }

}
double autocat::value(int x1,int y1)
{
    double v=-mymap[mapy(y1)][mapx(x1)];
    return v;

}

 autoanimal::point autoanimal::nextstep(int x1,int y1)
 {
        int dx[6]{-1,-1,0,1,1,0};
        int dy[6]{0,1,1,0,-1,-1};
        std::vector<autoanimal::point> line ;
        std::vector<double>values;
        autoanimal::point nowanimal={0,0};
        std::cout<<"4";
        int i=0;
        while(i<=5)
        {   nowanimal.x=x1+dx[i];
            nowanimal.y=y1+dy[i];
            //std::cout<<"5";
            ++i;
            if (is_wall(nowanimal))  continue;
            //std::cout<<"a value is got";
            double a=value(nowanimal.x,nowanimal.y);

            line.push_back(nowanimal) ;
            values.push_back(a);
            //std::cout<<"end a for\n";

        }

        //std::cout<<"values are got";
        int m=0;
        if (values.size() == 0)
            throw std::runtime_error {"Error with map: all walls"};
        double nvalue=values[0];
        for(int i=1;i<values.size();++i){

            if (nvalue<values[i])
            {
                nvalue=values[i];
                m=i;
            }
        }
        autoanimal::point a = line[m];
        return a;
}

 bool automouse::is_wall(point q)

 {    //std::cout<<"judge";
     for (auto p:mousewall)
     {
         if (p.x==p.x&&p.y==q.y) return true;
     }
  return false;
 }
 bool autocat::is_wall(point q)
 {
     for (auto p:catwall)
     {
         if (p.x==p.x&&p.y==q.y) return true;
     }
  return false;
 }

