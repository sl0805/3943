#include<iostream>
#include<conio.h>
#include<windows.h>
using namespace std;
//控制光标位置，列、行
void set_xy(int i, int j)
{
  COORD x_y = { i, j };
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), x_y);
}
//不同类型的俄罗斯方块的各个点的坐标
int b_type[17][8]=
{
  {0,0,1,0,0,1,1,1},
  {1,0,0,1,1,1,0,2},{0,0,1,0,1,1,2,1},
  {0,0,0,1,0,2,0,3},{0,0,1,0,2,0,3,0},
  {1,0,1,1,0,2,1,2},{0,0,0,1,1,1,2,1},{0,0,1,0,0,1,0,2},{0,0,1,0,2,0,2,1},
  {1,0,0,1,1,1,2,1},{0,0,0,1,1,1,0,2},{0,0,0,1,0,2,1,1},{1,0,0,1,1,1,1,2},
  {0,0,1,0,1,1,1,2},{2,0,0,1,1,1,2,1},{0,0,0,1,0,2,1,2},{0,0,1,0,2,0,0,1}
};
#define a1 0
#define b1 1
#define b2 2
#define c1 3
#define c2 4
#define d1 5
#define d2 6
#define d3 7
#define d4 8
#define e1 9
#define e2 10
#define e3 11
#define e4 12
#define f1 13
#define f2 14
#define f3 15
#define f4 16
//方块类
class block
{
  public:
    void draw_b(int dx,int dy,int type);
    void draw_map();
    void welcome();
    int turn(int i);
    void clean(int dx,int dy,int type);
    
};
void block::draw_b(int dx,int dy,int type)
{
  int i,j;
  for(j=0;j<4;j++)
  {
    set_xy(dx+b_type[type][j*2]*2,dy+b_type[type][j*2+1]);
    cout<<"■";
  }
}
void block::draw_map()
{
  int i;
  for(i=0;i<30;i++)
  {
    set_xy(2*i,0);
    cout<<"◇";
    set_xy(2*i,24);
    cout<<"◇";
  }
  for(i=1;i<24;i++)
  {
    set_xy(0,i);
    cout<<"◇";
    set_xy(58,i);
    cout<<"◇";
    set_xy(38,i);
    cout<<"◇";
  }
}
void block::welcome()
{
  set_xy(20,10);
  cout<<"我罗斯"<<endl;
  set_xy(20,15);
  cout<<"请输入1/2/3选择难度";
}
int block::turn(int i)
{
  switch (i)
  {
  case 0:return a1;
    break;
  case 1:return b2;
    break;
  case 2:return b1;
    break;
  case 3:return c2;
    break;
  case 4:return c1;
    break;
  case 5:return d2;
    break;
  case 6:return d3;
    break;
  case 7:return d4;
    break;
  case 8:return d1;
    break;
  case 9:return e2;
    break;
  case 10:return e3;
    break;
  case 11:return e4;
    break;
  case 12:return e1;
    break;
  case 13:return f2;
    break;
  case 14:return f3;
    break;
  case 15:return f4;
    break;
  case 16:return f1;
    break;
  default:
    break;
  }
}
void clean(int dx,int dy,int type)
{
  int i;
  for(i=0;i<4;i++)
  {
    set_xy(dx+b_type[type][i*2]*2,dy+b_type[type][i*2+1]);
    cout<<"  ";
  }
}
int main()
{
  block k;
  k.draw_b(0,0,0);
  getchar();
  k.clean(0,0,0);
  getchar();
}