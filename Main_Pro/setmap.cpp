#include<iostream>
#include<cmath>                     //需要一个"coords_of_wall"读取墙坐标
#include<fstream>
#include"setmap.h"
namespace sit {
int v1=2;//用在猫的估值里的无用参数
int mapx(int x)
{                                                                                //坐标与map之间的转换
    return 6+x;
}
int mapy (int y)
{
    return 6-y;
}

int** setmap (int x1,int y1)
 {
    int** mymap = new int*[13];//用数组存以中心为原点的坐标,（x,y）对应数组[6-y][6+x]元	初始化为0，
    for (int i = 0; i < 13; ++i)
        mymap[i] = new int[13];
    std::ifstream myset{"coords_of_wall"};
    while (true){                                                                    //建墙和边界
        int x,y;
        myset>>x>>y;
        if (!myset) break;
        std::cout<<"building wall";
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


    int arrayk [][2]{x1,y1};                                                        //构建map值
    int head=0,tail=0,step=1;
    int dx[6]{-1,-1,0,1,1,0};
    int dy[6]{0,1,1,0,-1,-1};
	while (head<=tail) {
		int st=tail;
		for (int i=head;i<=st;i++) {
			for (int j=0;j<6;j++) {
                int nx=arrayk[i][0]+dx[j];int ny=arrayk[i][1]+dy[j];
				if ((abs(nx)+abs(ny)>12)||mymap[mapy(ny)][mapx(nx)]==10000) continue;
				if (mymap[mapy(ny)][mapx(nx)]<=step) continue;
				++tail;
				std::cout<<nx<<ny;
				arrayk[tail][0]=nx;arrayk[tail][1]=ny;
				mymap[mapy(ny)][mapx(nx)]=step;
			}
		}
		step++;
		head=st+1;
    }

    return mymap;
}

int value_for_cat (int catx,int caty,int mousex,int mousey )
{
    int** mousemap = setmap (mousex,mousey);
    std::cout<<"one map is set\n";
    int**catmap= setmap(catx,caty);
    std::cout<<"one map is set\n";
    int x=-6;
    int y=-6;
    int value=0;
    for (;x<7;++x)
    {   for (;y<7;++y){
            if (catmap[mapy(y)][mapx(x)]<25)
            {  std::cout<<"get in a if\n";
               int a=mousemap[mapy(y)][mapx(x)];
               int b=catmap[mapy(y)][mapx(x)] ;
               value=value+v1*exp(-pow(b,1/2))*exp(-pow(a,1/2));
            }

       }

    }
 return value;
}


int*nextstepforcat(int catx,int caty,int mousex,int mousey )      //用估值函数判断下一步怎么走
{   std::cout<<"nextstep is called\n";
    int *p {new int[2]{catx,caty}};
    int dx[6]{-1,-1,0,1,1,0};
    int dy[6]{0,1,1,0,-1,-1};
    int*np=p;
    int* line[6];
    int val[6];
    for(int i=0;i<=5;++i)
    {   np[0]=p[0]+dx[i];
        np[1]=p[1]+dy[i];
        int a=value_for_cat (np[0] ,np[1], mousex,mousey );
        std::cout<<"a value is gotten";
        *line[i]=*np;
        val[i]=a;
        std::cout<<"end a for\n";
    }
    std::cout<<"values is gotten";
    int m=0;
    int nvalue=val[0];
    for(int i=1;i<6;++i)
    {
        if (nvalue<val[i])
        {
            nvalue=val[i];
            m=i;
        }
    }
   std::cout<<"largest value got";
  return   line[m];
}


}
