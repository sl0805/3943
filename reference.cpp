#include<iostream>
#include<string>
#include<cstdlib>
#include<windows.h>
#include<ctime>
#include<conio.h>
#include<cstdio>
using namespace std;
 
class Tetris
{
private:
  int rank;        //游戏难度等级
  int score;        // 得分
  int id;          //图形ID
  int point[2];      //两基点
  int top;          //最高点高度
public:
  Tetris();
  void Welocme();      //首界面
  void DrawMap();      //游戏界面
  void SetColor(int);    //控制颜色
  void Draw(int, int, int);    //画图形
  void Run();        //运行游戏
  void ReDraw(int, int, int);      //清除图形
  bool Judge(int, int, int);
  void Turn(int);        //旋转
  void Updata();        // 更新界面
  void Pause();        //游戏暂停
  void Input_score();
};
 
const int sharp[15][8] =          //组成图形的各个点的各个坐标，先纵后横
{
{0,0,1,0,2,0,3,0},{0,0,0,1,0,2,0,3},
{0,0,1,0,0,1,1,1},
{0,0,1,0,1,1,1,2},{0,1,1,1,2,0,2,1},{0,0,0,1,0,2,1,2},{0,0,0,1,1,0,2,0},
{1,0,1,1,1,2,0,2},{0,0,0,1,1,1,2,1},{0,0,0,1,0,2,1,0},{0,0,1,0,2,0,2,1},
{0,0,0,1,1,1,1,2},{0,1,1,0,1,1,2,0},
{0,1,0,2,1,0,1,1},{0,0,1,0,1,1,2,1}
};
 
const int high[15] = { 4,1,2,2,3,2,3,2,3,2,3,2,3,2,3 };
int map[28][16];
 
#define a1  0      //条形
#define a2  1
#define b 2          // 方块
 
#define c1 3          //L形
#define c2 4
#define c3 5
#define c4 6
 
#define d1 7          //T形
#define d2 8 
#define d3 9
#define d4 10
 
#define e1 11        //闪电1形
#define e2 12
 
#define f1 13        //闪电2形
#define f2 14
 
Tetris::Tetris()        //构造函数， 初始化各个值
{
  point[0] = 0;
  point[1] = 5;
  score = 0;
  top = 25;
}
 
void Tetris::Turn(int num)        //旋转函数
{
  switch (num)
  {
  case a1: id = a2; break;          //条形互换
  case a2: id = a1; break;
 
  case b: id = b; break;          //方块无法旋转
 
  case c1: id = c2; break;          //各种L形互换
  case c2: id = c3; break;
  case c3: id = c4; break;
  case c4: id = c1; break;
 
  case d1: id = d2; break;          //各种T形互换
  case d2: id = d3; break;
  case d3: id = d4; break;
  case d4: id = d1; break;
 
  case e1: id = e2; break;          //两种闪电形互换
  case e2: id = e1; break;
 
  case f1: id = f2; break;
  case f2: id = f1; break;
  }
}
 
void SetPos(int i, int j)      //控制光标位置， 列， 行
{
  COORD pos = { i,j };
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
 
void Tetris::Pause()        // 暂停函数
{
  SetPos(32, 10);
  cout << "游戏暂停!" << endl;
  SetPos(30, 11);
  cout << "你的分数为 " << score;
  char temp;
  while (1)
  {
    while (1)
    {
      if (_kbhit())
      {
        temp = _getch();
        break;
      }
    }
    if (temp == 32)
      break;
  }
  SetPos(32, 10);          // 清除暂停时显示的信息
  cout << "         ";
  SetPos(30, 11);
  cout << "              ";
}
 
void Tetris::Updata()          //更新函数，在每块俄罗斯方块下落后更新一次界面
{
  int i, flag;
  int nx, ny;
  for (i = 0; i < 4; i++)
  {
    nx = point[0] + sharp[id][i * 2];
    ny = point[1] + sharp[id][i * 2 + 1];
    SetPos((ny + 1) * 2, nx + 1);
    SetColor(0);//落下静止后方块的颜色设置。
    cout << "■";
    map[nx][ny] = 1;          //界面各个点是否为空的更新
  }
 
  if (point[0] < top)//point[0]为行数。
    top = point[0];          //最高点的更新
 
  for (i = point[0]; i < point[0] + high[id]; i++)      //消除行
  {
    flag = 1;
    for (int j = 0; j < 13; j++)          //判定某一行是否满， 用flag来标记
      if (map[i][j] == 0)
        flag = 0;//一行全满时用1表示
    if (flag == 1)//判断有一行全满后进行消行处理
    {
      for (int k = i; k >= top; k--)
      {
        for (int p = 0; p < 13; p++)
        {
          map[k][p] = map[k - 1][p];
          SetPos((p + 1) * 2, k + 1);
          if (map[k][p] == 1)
            cout << "■";
          else cout << "  ";
 
        }
      }
      score += 10;
      Input_score();
    }
  }
}
 
void Tetris::Input_score()
{
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);//该行以下输出的颜色设置，该函数不是自己定义的,不需要自己定义的setcolor函数了
  SetPos(30, 19);
  cout << "得分: " << score;
}
 
void Tetris::Welocme()      //欢迎界面
{
  SetColor(1);
  char x;
  while (1)
  {
    //cout << "■■■■■■■■■■■■■■■■■■■■■" << endl;
    cout << "    俄罗斯方块    " << endl;
    cout << "■■■■■■■■■■■■■■■■■■■■■" << endl;
    cout << "    操作方式：" << endl;
    cout << "    ↑ - 旋转" << endl;
    cout << "    ↓ - 加速下移" << endl;
    cout << "    ← - 左移" << endl;
    cout << "    → - 右移" << endl;
    cout << "    空格 - 暂停" << endl;
    cout << "■■■■■■■■■■■■■■■■■■■■■" << endl;
    cout << "■ 按1—3选择难度■" << endl;
    //SetPos(20, 10);//设置光标位置，30为第几列，10为第几行
    x = getchar();//输入难度选择
    if (x <= '9' && x >= '0')
    {
      rank = x - '0';//rank为难度系数，为Terris类中的一个成员变量
      break;
    }
  }
}

void Tetris::SetColor(int color_num)      //设置颜色
{
  int n;
  switch (color_num)
  {
  case 0: n = 0x08; break;
  case 1: n = 0x0C; break;
  case 2: n = 0x0D; break;
  case 3: n = 0x0E; break;
  case 4: n = 0x0A; break;
  }
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), n);
} 

void Tetris::DrawMap()        //画游戏时界面
{
  int i;
  //SetColor(2);
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);//该行以下输出的颜色设置，该函数不是自己定义的,不需要自己定义的setcolor函数了
  for (i = 0; i < 24; i++)    //宽24格
  {
    SetPos(i * 2, 0);
    cout << "——";
    SetPos(i * 2, 26);
    cout << "——";
  }
  for (i = 0; i < 26; i++)    //高26格
  {
    SetPos(0, i);
    cout << "|";
    SetPos(27, i);
    cout << "|";
    SetPos(46, i);
    cout << "|";
  }
 
  for (i = 14; i < 22; i++)
  {
    SetPos(i * 2, 16);
    cout << "——";
  }
  //SetColor(3);
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
  Input_score();//具体得分显示
  SetPos(30, 21);
  cout << "难度等级: " << rank;
  SetPos(32, 2);
  cout << "下一图形";
}
 
void Tetris::Draw(int x, int y, int num)        //画图形
{
  int nx, ny;
 
  for (int i = 0; i < 4; i++)
  {
    nx = x + sharp[num][2 * i];//刚出现的图形从哪一行开始下落
    ny = y + sharp[num][2 * i + 1];//刚出现的图形从哪一列开始下落
    SetPos((ny + 1) * 2, nx + 1);
    SetColor(i + 1);
    cout << "■";
  }
}
 
void Tetris::ReDraw(int x, int y, int num)        //当“下一个图形”开始下落时清楚原先的图形
{
  int nx, ny;
  
  for (int i = 0; i < 4; i++)
  {
    nx = x + sharp[num][2 * i];
    ny = y + sharp[num][2 * i + 1];
    SetPos((ny + 1) * 2, nx + 1);
    cout << " ";
  }
}
 
bool Tetris::Judge(int x, int y, int num)//不可画返回true，否则返回false
{                         
  int nx, ny;
  for (int i = 0; i < 4; i++)
  {
    nx = x + sharp[num][2 * i];
    ny = y + sharp[num][2 * i + 1];
    if (!(nx < 25 && nx >= 0 && ny < 13 && ny >= 0 && !map[nx][ny]))
      return true;//当图形移动到边界位置或者位置被其他占有时就不能再移动
  }
  return false;
}
 
void Tetris::Run()          //运行游戏
{
  int next_id;
  srand((int)time(0));//以当前时间对应的int值作为随机数的起点，这样不同时间对应的随机数就不一样，time函数一定要有参数，0表示不对随机数进行存储
  //srand相当于给rand函数提供一个起点
  id = rand() % 15;//得到图形对应的ID
  next_id = rand() % 15;
 
  Draw(point[0], point[1], id);//绘制图形
  Draw(5, 16, next_id);//依次为第几行、第几列、什么图形
 
  int count;
  if (rank == 1)
    count = 150;
  else if (rank == 2)
    count = 100;
  else if (rank==3)
    count = 50;
  else
    count = 5;
  int i = 0;  //不同等级对应不同count
 
  while (1)
  {
    if (!(i < count))        //i 与 count 用于控制时间
    {
      i = 0;
      if (Judge(point[0] + 1, point[1], id))      //在某一位置不能下落的话
      {//judge函数在不可画时返回true，否则返回false
        Updata();
        id = next_id;
 
        ReDraw(5, 16, next_id);
        next_id = rand() % 15;
 
        point[0] = 0; point[1] = 5;
        Draw(point[0], point[1], id);
        Draw(5, 16, next_id);
 
        if (Judge(point[0], point[1], id))//如果一开始就不能够下落，即超过行高界限时，结束游戏
        {
          system("cls");//清除界面
          SetPos(20, 10);
          cout << "游戏结束！" << endl;
          SetPos(20, 11);
          cout << "你的分数为 " << score << endl;
          system("pause");
          exit(1);
        }
      }
      else          //继续下落
      {
        ReDraw(point[0], point[1], id);
        point[0]++;
        Draw(point[0], point[1], id);
      }
    }
 
    if (_kbhit())        //kbhit函数检查当前是否有键盘输入 
    {
      int key, key2;
      key = _getch();//getch为不回显函数，用户按下某个字符时，函数自动读取，无需按回车
      if (key == 224)//对于方向键getch函数第一次返回224，第二次返回真实键值
      {
        key2 = _getch();
 
        if (key2 == 72)      //按向上方向键时
        {
          int temp = id;
          Turn(id);
          if (Judge(point[0], point[1], id))
            id = temp;
          ReDraw(point[0], point[1], temp);
          Draw(point[0], point[1], id);
        }
        if (key2 == 80)        //按向下方向键时
        {
          if (!Judge(point[0] + 2, point[1], id))
          {
            ReDraw(point[0], point[1], id);
            point[0] += 2;
            Draw(point[0], point[1], id);
          }
        }
        else if (key2 == 75)        //按向左方向键时
        {
          if (!Judge(point[0], point[1] - 1, id))
          {
            ReDraw(point[0], point[1], id);
            point[1]--;
            Draw(point[0], point[1], id);
          }
        }
        else if (key2 == 77)          //按向右方向键时
        {
          if (!Judge(point[0], point[1] + 1, id))
          {
            ReDraw(point[0], point[1], id);
            point[1]++;
            Draw(point[0], point[1], id);
          }
        }
      }
      else if (key == 32)          // 按下空格暂停
        Pause();
    }
 
    Sleep(1);    //等待1毫秒，sleep函数可以用来延迟代码执行若干秒
    i++;        //控制下落间隔
  }
}
 
int main()
{
  Tetris game;
  game.Welocme();
  system("cls");        //清屏
  game.DrawMap();
  game.Run();
}