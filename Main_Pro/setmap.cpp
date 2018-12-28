#include<iostream>>
#include<cmath>                     //��Ҫһ��"coords_of_wall"��ȡǽ����
#include<fstream>
#include"setmap.h"
namespace sit {
int v1=2;//����è�Ĺ�ֵ������ò���
int mapx(int x)
{                                                                                //������map֮���ת��
    return 6+x;
}
int mapy (int y)
{
    return 6-y;
}

int** setmap (int x1,int y1)
 {
    int** mymap = new int*[13];//�������������Ϊԭ�������,��x,y����Ӧ����[6-y][6+x]Ԫ	��ʼ��Ϊ0��
    for (int i = 0; i < 13; ++i)
        mymap[i] = new int[13];
    std::ifstream myset{"coords_of_wall"};
    while (true){                                                                    //��ǽ
        int x,y;
        myset>>x>>y;
        if (!myset) break;
        mymap[6-y][6+x]=10000;
    }
    int arrayk [][2]{x1,y1};                                                        //����mapֵ
    int head=0,tail=5,step=1;
    int dx[6]{-1,-1,0,1,1,0};
    int dy[6]{0,1,1,0,-1,-1};
	while (head<=tail) {
		int st=tail;
		for (int i=head;i<=st;i++) {
			for (int j=0;j<6;j++) {
                int nx=arrayk[i][0]+dx[j];int ny=arrayk[i][1]+dy[j];
				if ((abs(nx)+abs(ny)<13)||mymap[mapy(ny)][mapx(nx)]==10000) continue;
				if (mymap[mapy(ny)][mapx(nx)]<=step) continue;
				++tail;
				arrayk[tail][0]=nx;arrayk[tail][1]=ny;
				mymap[mapy(ny)][mapx(nx)]=step;
			}
		}
		step++;
		head=st+1;


    }
    int* p[13];
    for (int i = 0; i != 13; ++i) {
          p[i] = new int[13];
    }
    return mymap;
}

int value_for_cat (int catx,int caty,int mousex,int mousey )
{
    int** mousemap = setmap (mousex,mousey);
    int**catmap= setmap(catx,caty);
    int x=-6;
    int y=-6;
    int value=0;
    for (x;x<7;++x)
    {   for (y;y<7;++y){
            while ((abs(x)+abs(y)<13)||mousemap[mapy(y)][mapx(x)]==10000)
            {
               int a=mousemap[mapy(y)][mapx(x)];
               int b=catmap[mapy(y)][mapx(x)] ;
               value=value+v1*exp(-pow(b,1/2))*exp(-pow(a,1/2));
            }

       }

    }
 return value;
}


int*nextstepforcat(int catx,int caty,int mousex,int mousey )      //�ù�ֵ�����ж���һ����ô��
{
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
        *line[i]=*np;
        val[i]=a;
    }
    int m=0;
    for (int i=0;i<=5;++i)
    {
        for (int j=i+1;j<=5;++j)
        {
           if(val[i]>=val[j])
            m=i;
        }
    }

  return   line[m];
}


}
