#ifndef SETMAP
#define SETMAP

namespace sit{
int mapx(int x);
int mapy (int y);
int** setmap (int x1,int y1);
int*nextstepforcat(int catx,int caty,int mousex,int mousey ) ;
int value_for_cat (int catx,int caty,int mousex,int mousey );
}
#endif // SETMAP
