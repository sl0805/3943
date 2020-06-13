#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <ctime>
#include <conio.h>
#include <cstdio>
#include <iomanip>
using namespace std;
const int sharp[15][8] = //组成图形的各个点的各个坐标，先纵后横
    {
        {0, 0, 1, 0, 2, 0, 3, 0}, {0, 0, 0, 1, 0, 2, 0, 3}, 
        {0, 0, 1, 0, 0, 1, 1, 1}, 
        {0, 0, 1, 0, 1, 1, 1, 2}, {0, 1, 1, 1, 2, 0, 2, 1}, {0, 0, 0, 1, 0, 2, 1, 2}, {0, 0, 0, 1, 1, 0, 2, 0}, 
        {1, 0, 1, 1, 1, 2, 0, 2}, {0, 0, 0, 1, 1, 1, 2, 1}, {0, 0, 0, 1, 0, 2, 1, 0}, {0, 0, 1, 0, 2, 0, 2, 1}, 
        {0, 0, 0, 1, 1, 1, 1, 2}, {0, 1, 1, 0, 1, 1, 2, 0}, 
        {0, 1, 0, 2, 1, 0, 1, 1}, {0, 0, 1, 0, 1, 1, 2, 1}
    };

const int high[15] = {4, 1, 2, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3};
int map[28][16];
int map1[28][16];

#define a1 0 //条形
#define a2 1
#define b 2 // 方块

#define c1 3 //L形
#define c2 4
#define c3 5
#define c4 6

#define d1 7 //T形
#define d2 8
#define d3 9
#define d4 10

#define e1 11 //闪电1形
#define e2 12

#define f1 13 //闪电2形
#define f2 14
void SetPos(int i, int j) //控制光标位置， 列， 行
{
    COORD pos = {i, j};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
int Welocme() //欢迎界面
{
    //SetColor(1);
    char x;
    int rank;
    while (1)
    {
        system("cls");
        cout << "■■■■■■■■■■作者：孙巧、邹莹■■■■■■■■■■■■" << endl;
        cout << "                       我罗斯方块                    " << endl;
        cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
        cout << "    玩家1操作方式：         "
             << "    玩家2操作方式：" << endl;
        cout << "    ↑ - 旋转              "
             << "    W - 旋转" << endl;
        cout << "    ↓ - 加速下移          "
             << "    S - 加速下移" << endl;
        cout << "    ← - 左移              "
             << "    D - 左移" << endl;
        cout << "    → - 右移              "
             << "    A - 右移" << endl;
        cout << "                 空格 - 暂停     " << endl;
        cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
        cout << "■ 按1—3选择难度■" << endl;
        SetPos(20, 10);
        x = getchar();
        if (x <= '3' && x >= '0')
        {
            rank = x - '0';
            break;
        }
    }
    return rank;
}
class Tetris
{
private:
    int rank;     //游戏难度等级
    int score;    // 得分
    int id;       //图形ID
    int point[2]; //两基点
    int top;      //最高点高度
    int n;

public:
    static int sum;
    Tetris(int r);
    void Welocme();             //首界面
    void DrawMap();             //游戏界面
    void SetColor(int);         //控制颜色
    void Draw(int, int, int);   //画图形
    void ReDraw(int, int, int); //清除图形
    bool Judge(int, int, int);
    bool Judge1(int, int, int);
    void Turn(int); //旋转
    void Updata();  // 更新界面

    void Input_score();
    void tianjia();
    int getscore()
    {
        return score;
    }
    int getid()
    {
        return id;
    }
    void setid(int x)
    {
        id = x;
    }
    int getpoint0()
    {
        return point[0];
    }
    int getpoint1()
    {
        return point[1];
    }
    void setpoint(int x, int y)
    {
        point[0] += x;
        point[1] += y;
    }
    void setpoint1(int x, int y)
    {
        point[0] = x;
        point[1] = y;
    }
    int getrank()
    {
        return rank;
    }
};
int Tetris::sum = 0;

class Tetris1 : public Tetris
{
private:
    int rank;     //游戏难度等级
    int score;    // 得分
    int id;       //图形ID
    int point[2]; //两基点
    int top;      //最高点高度
    int n;

public:
    static int sum2;
    Tetris1(int r);
    void Welocme(); //首界面
    void DrawMap(); //游戏界面
    void Input_score();
    bool Judge(int, int, int);
    bool Judge1(int, int, int);
    void Draw(int, int, int);
    void ReDraw(int, int, int);
    void Updata();
    void Turn(int);
    void tianjia();
    int getscore()
    {
        return score;
    }
    int getid()
    {
        return id;
    }
    void setid(int x)
    {
        id = x;
    }
    int getpoint0()
    {
        return point[0];
    }
    int getpoint1()
    {
        return point[1];
    }
    void setpoint(int x, int y)
    {
        point[0] += x;
        point[1] += y;
    }
    void setpoint1(int x, int y)
    {
        point[0] = x;
        point[1] = y;
    }
    int getrank()
    {
        return rank;
    }
};
int Tetris1::sum2 = 0;
void Tetris1::tianjia() //添加行数。
{

    for (; sum2 <= 25; sum2 += 8)
    {
        SetPos(sum2, 4);
        cout << "■"
             << "■"
             << "■"
             << "■";
    }
    /*	SetPos(0,25);
  	SetColor(0);
  	for(int i=1;i<8;i++)
  	{
  		cout<<"■";
	  }
	cout<<"■"<<"  "<<"■"<<"  "<<"■"<<"■"; */
}
void Tetris::tianjia()
{
    for (; sum + 50 <= 75; sum += 58)
    {
        SetPos(sum + 50, 4);
        cout << "■"
             << "■"
             << "■"
             << "■";
    }
    /*SetPos(52,25);
  	SetColor(0);
  	for(int i=1;i<9;i++)
  	{
  		cout<<"■";
	  }
	  cout<<"■"<<"  "<<"■"<<"■"<<"■";*/
}
Tetris::Tetris(int r) //构造函数， 初始化各个值
{
    point[0] = 0;
    point[1] = 5;
    score = 0;
    top = 25 + n;
    rank = r;
}
Tetris1::Tetris1(int r) : Tetris(r) //构造函数， 初始化各个值
{
    point[0] = 0;
    point[1] = 5;
    score = 0;
    top = 25 + n;
    rank = r;
}
void Tetris::Turn(int num) //旋转函数
{
    switch (num)
    {
    case a1:
        id = a2;
        break; //条形互换
    case a2:
        id = a1;
        break;

    case b:
        id = b;
        break; //方块无法旋转

    case c1:
        id = c2;
        break; //各种L形互换
    case c2:
        id = c3;
        break;
    case c3:
        id = c4;
        break;
    case c4:
        id = c1;
        break;

    case d1:
        id = d2;
        break; //各种T形互换
    case d2:
        id = d3;
        break;
    case d3:
        id = d4;
        break;
    case d4:
        id = d1;
        break;

    case e1:
        id = e2;
        break; //两种闪电形互换
    case e2:
        id = e1;
        break;

    case f1:
        id = f2;
        break;
    case f2:
        id = f1;
        break;
    }
}
void Tetris1::Turn(int num) //旋转函数
{
    switch (num)
    {
    case a1:
        id = a2;
        break; //条形互换
    case a2:
        id = a1;
        break;

    case b:
        id = b;
        break; //方块无法旋转

    case c1:
        id = c2;
        break; //各种L形互换
    case c2:
        id = c3;
        break;
    case c3:
        id = c4;
        break;
    case c4:
        id = c1;
        break;

    case d1:
        id = d2;
        break; //各种T形互换
    case d2:
        id = d3;
        break;
    case d3:
        id = d4;
        break;
    case d4:
        id = d1;
        break;

    case e1:
        id = e2;
        break; //两种闪电形互换
    case e2:
        id = e1;
        break;

    case f1:
        id = f2;
        break;
    case f2:
        id = f1;
        break;
    }
}
void Pause(Tetris &game, Tetris &game1) // 暂停函数
{
    SetPos(32, 10);
    cout << "游戏暂停!" << endl;
    SetPos(30, 11);
    cout << "你的分数为 " << game.getscore();
    SetPos(32 + 50, 10);
    cout << "游戏暂停!" << endl;
    SetPos(30 + 50, 11);
    cout << "你的分数为 " << game1.getscore();
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
    SetPos(32, 10); // 清除暂停时显示的信息
    cout << "         ";
    SetPos(30, 11);
    cout << "              ";
    SetPos(32 + 50, 10); // 清除暂停时显示的信息
    cout << "         ";
    SetPos(30 + 50, 11);
    cout << "              ";
}
void Tetris::Updata() //更新函数
{
    int i, flag;
    int nx, ny;
    for (i = 0; i < 4; i++)
    {
        nx = point[0] + sharp[id][i * 2];
        ny = point[1] + sharp[id][i * 2 + 1];
        SetPos((ny + 1) * 2, nx + 1);
        SetColor(0);
        cout << "■";
        map[nx][ny] = 1; //界面各个点是否为空的更新
    }

    if (point[0] < top)
        top = point[0]; //最高点的更新

    for (i = point[0]; i < point[0] + high[id]; i++) //消除行
    {
        flag = 1;
        for (int j = 0; j < 13; j++) //判定某一行是否满， 用flag来标记
            if (map[i][j] == 0)
                flag = 0;
        if (flag == 1)
        {
            for (int k = i; k >= top; k--)
            {
                for (int p = 0; p < 13; p++)
                {
                    map[k][p] = map[k - 1][p];
                    SetPos((p + 1) * 2, k + 1);
                    if (map[k][p] == 1)
                        cout << "■";
                    else
                        cout << "  ";
                }
            }
            score += 10;
            Input_score();
            tianjia();
        }
    }
}
void Tetris1::Updata() //更新函数
{
    int i, flag;
    int nx, ny;
    for (i = 0; i < 4; i++)
    {
        nx = point[0] + sharp[id][i * 2];
        ny = point[1] + sharp[id][i * 2 + 1];
        SetPos((ny + 1) * 2 + 50, nx + 1);
        SetColor(0);
        cout << "■";
        map1[nx][ny] = 1; //界面各个点是否为空的更新
    }

    if (point[0] < top)
        top = point[0]; //最高点的更新

    for (i = point[0]; i < point[0] + high[id]; i++) //消除行
    {
        flag = 1;
        for (int j = 0; j < 13; j++) //判定某一行是否满， 用flag来标记
            if (map1[i][j] == 0)
                flag = 0;
        if (flag == 1)
        {
            for (int k = i; k >= top; k--)
            {
                for (int p = 0; p < 13; p++)
                {
                    map1[k][p] = map[k - 1][p];
                    SetPos((p + 1) * 2 + 50, k + 1);
                    if (map1[k][p] == 1)
                        cout << "■";
                    else
                        cout << "  ";
                }
            }
            score += 10;
            Input_score();
            tianjia();
        }
    }
}
void Tetris::Input_score()
{
    SetColor(3);
    SetPos(30, 19);
    cout << "得分: " << score;
}
void Tetris1::Input_score()
{
    SetColor(3);
    SetPos(80, 19);
    cout << "得分: " << score;
}
void Tetris::SetColor(int color_num) //设置颜色
{
    int n;
    switch (color_num)
    {
    case 0:
        n = 0x08;
        break;
    case 1:
        n = 0x0C;
        break;
    case 2:
        n = 0x0D;
        break;
    case 3:
        n = 0x0E;
        break;
    case 4:
        n = 0x0A;
        break;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), n);
}
void Tetris1::DrawMap() //画游戏时界面
{
    int i;
    SetColor(0);
    SetColor(3);
    Input_score();
    SetPos(30 + 50, 17);
    cout << "玩家2";
    SetPos(30 + 50, 21);
    cout << "难度等级: " << rank;
    SetPos(32 + 50, 2);
    cout << "下一图形";
}
void Tetris::DrawMap() //画游戏时界面
{
    int i;
    SetColor(0);

    for (i = 0; i < 48; i++) //宽24格
    {
        SetPos(i * 2, 0);
        cout << "■";
        SetPos(i * 2, 26);
        cout << "■";
    }

    for (i = 0; i <= 26; i++) //高26格
    {
        SetPos(0, i);
        cout << "■";
        SetPos(28, i);
        cout << "■";
        SetPos(50, i);
        cout << "■";
        SetPos(46, i);
        cout << "■";
        SetPos(78, i);
        cout << "■";
        SetPos(96, i);
        cout << "■";
    }

    for (i = 14; i < 24; i++)
    {
        SetPos(i * 2, 16);
        cout << "■";
    }
    for (i = 14; i < 24; i++)
    {
        SetPos(i * 2 + 50, 16);
        cout << "■";
    }
    for (i = 24; i < 44; i++)
    {
        SetPos(i * 2, 46);
        cout << "■";
    }
    for (i = 24; i < 48; i++)
    {
        SetPos(i * 2, 32);
        cout << "■";
    }
    SetColor(3);
    Input_score();
    SetPos(30, 17);
    cout << "玩家1";
    SetPos(30, 21);
    cout << "难度等级: " << rank;
    SetPos(32, 2);
    cout << "下一图形";
}
void Tetris::Draw(int x, int y, int num) //画图形
{
    int nx, ny;

    for (int i = 0; i < 4; i++)
    {
        nx = x + sharp[num][2 * i];
        ny = y + sharp[num][2 * i + 1];
        SetPos((ny + 1) * 2, nx + 1);
        SetColor(i + 1);
        cout << "■";
    }
}
void Tetris1::Draw(int x, int y, int num) //画图形
{
    int nx, ny;

    for (int i = 0; i < 4; i++)
    {
        nx = x + sharp[num][2 * i];
        ny = y + sharp[num][2 * i + 1];
        SetPos((ny + 1) * 2 + 50, nx + 1);
        SetColor(i + 1);
        cout << "■";
    }
}
void Tetris::ReDraw(int x, int y, int num) //为更新图形的位置清除图形
{
    int nx, ny;

    for (int i = 0; i < 4; i++)
    {
        nx = x + sharp[num][2 * i];
        ny = y + sharp[num][2 * i + 1];

        SetPos((ny + 1) * 2, nx + 1);
        cout << "  "; //改为两个空格可以优化界面。
    }
}
void Tetris1::ReDraw(int x, int y, int num) //为更新图形的位置清除图形
{
    int nx, ny;

    for (int i = 0; i < 4; i++)
    {
        nx = x + sharp[num][2 * i];
        ny = y + sharp[num][2 * i + 1];

        SetPos((ny + 1) * 2 + 50, nx + 1);
        cout << "  "; //改为两个空格可以优化界面。
    }
}
bool Tetris::Judge(int x, int y, int num) //判断是否可以继续下落：判定在该位置上是否能够画图形，如果可以的话返回false，否则返回true
{                                         
    int nx, ny;
    for (int i = 0; i < 4; i++)
    {
        nx = x + sharp[num][2 * i];
        ny = y + sharp[num][2 * i + 1];
        if (!(nx < 25 && nx >= 0 && !map[nx][ny]))
            return true;
    }
    return false;
}
bool Tetris::Judge1(int x, int y, int num) //判断是否可以继续左移或右移：判断方法如judge
{                                          
    int nx, ny;
    for (int i = 0; i < 4; i++)
    {
        nx = x + sharp[num][2 * i];
        ny = y + sharp[num][2 * i + 1];
        if (!(nx < 25 && nx >= 0 && ny < 13 && ny >= 0 && !map[nx][ny]))
            return true;
    }
    return false;
}
bool Tetris1::Judge(int x, int y, int num) //判断是否可以继续下落：判定在该位置上是否能够画图形，如果可以的话返回false，否则返回true
{                                          
    int nx, ny;
    for (int i = 0; i < 4; i++)
    {
        nx = x + sharp[num][2 * i];
        ny = y + sharp[num][2 * i + 1];
        if (!(nx < 25 && nx >= 0 && !map1[nx][ny]))
            return true;
    }
    return false;
}
bool Tetris1::Judge1(int x, int y, int num) //判断是否可以继续左移或右移：判断方法如judge
{                                           
    int nx, ny;
    for (int i = 0; i < 4; i++)
    {
        nx = x + sharp[num][2 * i];
        ny = y + sharp[num][2 * i + 1];
        if (!(nx < 25 && nx >= 0 && ny < 13 && ny >= 0 && !map1[nx][ny]))
            return true;
    }
    return false;
}
int Run(Tetris &game, Tetris1 &game1) //运行游戏
{
    int next_id, next_id1;
    srand((int)time(0));

    game.setid(rand() % 15);
    game1.setid(rand() % 15);
    next_id = rand() % 15;
    next_id1 = rand() % 15;
    game.Draw(game.getpoint0(), game.getpoint1(), game.getid());
    game1.Draw(game1.getpoint0(), game1.getpoint1(), game1.getid());
    game.Draw(5, 16, next_id);
    game1.Draw(5, 16, next_id1);

    while (1)
    {

        if (1) 
        {
            if (game.Judge(game.getpoint0() + 1, game.getpoint1(), game.getid())) //玩家1：判断如果在当前位置下落一格是否可行，返回值为true时，不可下落
            {
                game.Updata();
                game.setid(next_id);

                game.ReDraw(5, 16, next_id);
                next_id = rand() % 15;

                game.setpoint1(0, 5);
                game.Draw(game.getpoint0(), game.getpoint1(), game.getid());
                game.Draw(5, 16, next_id);
                //玩家1：如果当前位置判断为不可下落的话，那判断当前位置是否位于框图最顶点，其中一个玩家到最顶点，游戏结束。
                if (game.Judge(game.getpoint0(), game.getpoint1(), game.getid()) || game1.Judge(game1.getpoint0(), game1.getpoint1(), game1.getid()))
                {
                    return 0;
                }
            }
            else//继续下落
            {
                game.ReDraw(game.getpoint0(), game.getpoint1(), game.getid());
                game.setpoint(1, 0);
                game.Draw(game.getpoint0(), game.getpoint1(), game.getid());
            }
            if (game1.Judge(game1.getpoint0() + 1, game1.getpoint1(), game1.getid())) //玩家2：判断如果在当前位置下落一格是否可行，返回值为true时，不可下落
            {
                game1.Updata();
                game1.setid(next_id1);
                game1.ReDraw(5, 16, next_id1);
                next_id1 = rand() % 15;
                game1.setpoint1(0, 5);
                game1.Draw(game1.getpoint0(), game1.getpoint1(), game1.getid());
                game1.Draw(5, 16, next_id1);
                //玩家2：如果当前位置判断为不可下落的话，那判断当前位置是否位于框图最顶点，其中一个玩家到最顶点，游戏结束。
                if (game.Judge(game.getpoint0(), game.getpoint1(), game.getid()) && game1.Judge(game1.getpoint0(), game1.getpoint1(), game1.getid()))
                {
                    return 0;
                }
            }
            else//继续下落
            {
                game1.ReDraw(game1.getpoint0(), game1.getpoint1(), game1.getid());
                game1.setpoint(1, 0);
                game1.Draw(game1.getpoint0(), game1.getpoint1(), game1.getid());
            }
        }

        if (_kbhit()) //_kbhit()判断键盘是否输入值
        {
            int key, key2;
            key = _getch();//根据键值判断所需要实现的功能。

            if (key == 119) //72按向上方向键时
            {
                int temp = game1.getid();
                game1.Turn(game1.getid());
                if (game1.Judge(game1.getpoint0(), game1.getpoint1(), game1.getid()))
                    game1.setid(temp);
                game1.ReDraw(game1.getpoint0(), game1.getpoint1(), temp);
                game1.Draw(game1.getpoint0(), game1.getpoint1(), game1.getid());
            }
            if (key == 115) //80按向下方向键时
            {
                if (!game1.Judge(game1.getpoint0() + 2, game1.getpoint1(), game1.getid()))
                {
                    game1.ReDraw(game1.getpoint0(), game1.getpoint1(), game1.getid());
                    game1.setpoint(2, 0);
                    game1.Draw(game1.getpoint0(), game1.getpoint1(), game1.getid());
                }
            }
            else if (key == 97) //75按向左方向键时
            {
                if (!game1.Judge1(game1.getpoint0(), game1.getpoint1() - 1, game1.getid()))
                {
                    game1.ReDraw(game1.getpoint0(), game1.getpoint1(), game1.getid());
                    game1.setpoint(0, -1);
                    game1.Draw(game1.getpoint0(), game1.getpoint1(), game1.getid());
                }
            }
            else if (key == 100) //按向右方向键时
            {
                if (!game1.Judge1(game1.getpoint0(), game1.getpoint1() + 1, game1.getid()))
                {
                    game1.ReDraw(game1.getpoint0(), game1.getpoint1(), game1.getid());
                    game1.setpoint(0, 1);
                    game1.Draw(game1.getpoint0(), game1.getpoint1(), game1.getid());
                }
            }
            else if (key == 224) //224
            {
                key2 = _getch();

                if (key2 == 72) //72按向上方向键时
                {
                    int temp = game.getid();
                    game.Turn(game.getid());
                    if (game.Judge(game.getpoint0(), game.getpoint1(), game.getid()))
                        game.setid(temp);
                    game.ReDraw(game.getpoint0(), game.getpoint1(), temp);
                    game.Draw(game.getpoint0(), game.getpoint1(), game.getid());
                }
                if (key2 == 80) //80按向下方向键时
                {
                    if (!game.Judge(game.getpoint0() + 2, game.getpoint1(), game.getid()))
                    {
                        game.ReDraw(game.getpoint0(), game.getpoint1(), game.getid());
                        game.setpoint(2, 0);
                        game.Draw(game.getpoint0(), game.getpoint1(), game.getid());
                    }
                }
                else if (key2 == 75) //75按向左方向键时
                {
                    if (!game.Judge1(game.getpoint0(), game.getpoint1() - 1, game.getid()))
                    {
                        game.ReDraw(game.getpoint0(), game.getpoint1(), game.getid());
                        game.setpoint(0, -1);
                        game.Draw(game.getpoint0(), game.getpoint1(), game.getid());
                    }
                }
                else if (key2 == 77) //按向右方向键时
                {
                    if (!game.Judge1(game.getpoint0(), game.getpoint1() + 1, game.getid()))
                    {
                        game.ReDraw(game.getpoint0(), game.getpoint1(), game.getid());
                        game.setpoint(0, 1);
                        game.Draw(game.getpoint0(), game.getpoint1(), game.getid());
                    }
                }
            }

            else if (key == 32) // 按下空格暂停
            {
                Pause(game, game1);
            }
        }
        Sleep(400 - game.getrank() * 100); //用这个函数来调整不同难度等级的不同速度，从1-3速度依次递增
    }
}
int main()
{
    int rank = Welocme();
    Tetris game(rank);
    Tetris1 game1(rank);
    system("cls"); //清除欢迎界面
    game.DrawMap();
    game1.DrawMap();

    while (Run(game, game1))
    {
    }

    system("cls");

    if (game.getscore() > game1.getscore())
    {
        cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
        cout << "                      玩家1胜利                           " << endl;
        cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
    }

    else if (game.getscore() == game1.getscore())
    {
        cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
        cout << "                          二人平手                        " << endl;
        cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
    }

    else
    {
        cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
        cout << "                          玩家2胜利                        " << endl;
        cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
    }
    Sleep(300);
    return 0;
}