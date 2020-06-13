#include<iostream>
#include<string>
#include<cstdlib>
#include<windows.h>
#include<ctime>
#include<conio.h>
#include<cstdio>
#include<iomanip>
using namespace std;
const int sharp[15][8] =          //���ͼ�εĸ�����ĸ������꣬���ݺ��
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
int map1[28][16];
 
#define a1  0      //����
#define a2  1
#define b 2          // ����
 
#define c1 3          //L��
#define c2 4
#define c3 5
#define c4 6
 
#define d1 7          //T��
#define d2 8 
#define d3 9
#define d4 10
 
#define e1 11        //����1��
#define e2 12
 
#define f1 13        //����2��
#define f2 14
void SetPos(int i, int j)      //���ƹ��λ�ã� �У� ��
{
  COORD pos = { i,j };
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

class Tetris
{
private:
  int rank;        //��Ϸ�Ѷȵȼ�
  int score;        // �÷�
  int id;          //ͼ��ID
  int point[2];      //������
  int top;          //��ߵ�߶�
  int n;
  
public:
static int sum;
  Tetris(int r);
   void Welocme();      //�׽���
   void DrawMap();      //��Ϸ����
  void SetColor(int);    //������ɫ
   void Draw(int, int, int);    //��ͼ��
  // void Run();        //������Ϸ
   void ReDraw(int, int, int);      //���ͼ��
  bool Judge(int, int, int);
  bool Judge1(int, int, int);
   void Turn(int);        //��ת
   void Updata();        // ���½���
          
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
  	id=x;
  }
  int getpoint0()
  {
  	return point[0];
  }
  int getpoint1()
  {
  	return point[1];
  }
  void setpoint(int x,int y)
  {
  	point[0]+=x;
  	point[1]+=y;
  }
  void setpoint1(int x,int y)
  {
  	point[0]=x;
  	point[1]=y;
  }
  int getrank()
  {
  	return rank;
  }
};
int Tetris::sum=0;
  
 class Tetris1:public Tetris
 {
 	private:
  int rank;        //��Ϸ�Ѷȵȼ�
  int score;        // �÷�
  int id;          //ͼ��ID
  int point[2];      //������
  int top;          //��ߵ�߶�
  int n;
 	public:
 		static int sum2;
  Tetris1(int r);
  void Welocme();      //�׽���
  void DrawMap();      //��Ϸ����
  void Input_score();
//	void Run();        //������Ϸ
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
  	id=x;
  }
  int getpoint0()
  {
  	return point[0];
  }
  int getpoint1()
  {
  	return point[1];
  }
  void setpoint(int x,int y)
  {
  	point[0]+=x;
  	point[1]+=y;
  }
  void setpoint1(int x,int y)
  {
  	point[0]=x;
  	point[1]=y;
  }
  int getrank()
  {
  	return rank;
  }
 	
 };
 int Tetris1::sum2=0;
void Tetris1::tianjia()//��������� 
  {
  	
  	for(;sum2<=25;sum2+=8)
  	{
  		SetPos(sum2,4);
  		cout<<"��"<<"��"<<"��"<<"��";
	  }
  /*	SetPos(0,25);
  	SetColor(0);
  	for(int i=1;i<8;i++)
  	{
  		cout<<"��";
	  }
	cout<<"��"<<"  "<<"��"<<"  "<<"��"<<"��"; */
	 
  }
  void Tetris::tianjia()
  {
  	for(;sum+50<=75;sum+=58)
  	{
  		SetPos(sum+50,4);
  		cout<<"��"<<"��"<<"��"<<"��";
	  }
  	/*SetPos(52,25);
  	SetColor(0);
  	for(int i=1;i<9;i++)
  	{
  		cout<<"��";
	  }
	  cout<<"��"<<"  "<<"��"<<"��"<<"��";*/
  }
Tetris::Tetris(int r)        //���캯���� ��ʼ������ֵ
{
  point[0] = 0;
  point[1] = 5;
  score = 0;
  top = 25+n;
  rank=r;
}
Tetris1::Tetris1(int r):Tetris(r)       //���캯���� ��ʼ������ֵ
{
  point[0] = 0;
  point[1] = 5;
  score = 0;
  top = 25+n;
  rank=r;
}
void Tetris::Turn(int num)        //��ת����
{
  switch (num)
  {
  case a1: id = a2; break;          //���λ���
  case a2: id = a1; break;
 
  case b: id = b; break;          //�����޷���ת
 
  case c1: id = c2; break;          //����L�λ���
  case c2: id = c3; break;
  case c3: id = c4; break;
  case c4: id = c1; break;
 
  case d1: id = d2; break;          //����T�λ���
  case d2: id = d3; break;
  case d3: id = d4; break;
  case d4: id = d1; break;
 
  case e1: id = e2; break;          //���������λ���
  case e2: id = e1; break;
 
  case f1: id = f2; break;
  case f2: id = f1; break;
  }
}
void Tetris1::Turn(int num)        //��ת����
{
  switch (num)
  {
  case a1: id = a2; break;          //���λ���
  case a2: id = a1; break;
 
  case b: id = b; break;          //�����޷���ת
 
  case c1: id = c2; break;          //����L�λ���
  case c2: id = c3; break;
  case c3: id = c4; break;
  case c4: id = c1; break;
 
  case d1: id = d2; break;          //����T�λ���
  case d2: id = d3; break;
  case d3: id = d4; break;
  case d4: id = d1; break;
 
  case e1: id = e2; break;          //���������λ���
  case e2: id = e1; break;
 
  case f1: id = f2; break;
  case f2: id = f1; break;
  }
}
 

 
void Pause(Tetris &game,Tetris &game1)        // ��ͣ����
{
  SetPos(32, 10);
  cout << "��Ϸ��ͣ!" << endl;
  SetPos(30, 11);
  cout << "��ķ���Ϊ " << game.getscore();
  SetPos(32+50, 10);
  cout << "��Ϸ��ͣ!" << endl;
  SetPos(30+50, 11);
  cout << "��ķ���Ϊ " << game1.getscore();
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
  SetPos(32, 10);          // �����ͣʱ��ʾ����Ϣ
  cout << "         ";
  SetPos(30, 11);
  cout << "              ";
  SetPos(32+50, 10);          // �����ͣʱ��ʾ����Ϣ
  cout << "         ";
  SetPos(30+50, 11);
  cout << "              ";
}

void Tetris::Updata()          //���º���
{
  int i, flag;
  int nx, ny;
  for (i = 0; i < 4; i++)
  {
    nx = point[0] + sharp[id][i * 2];
    ny = point[1] + sharp[id][i * 2 + 1];
    SetPos((ny + 1) * 2, nx + 1);
    SetColor(0);
    cout << "��";
    map[nx][ny] = 1;          //����������Ƿ�Ϊ�յĸ���
  }
 
  if (point[0] < top)
    top = point[0];          //��ߵ�ĸ���
 
  for (i = point[0]; i < point[0] + high[id]; i++)      //������
  {
    flag = 1;
    for (int j = 0; j < 13; j++)          //�ж�ĳһ���Ƿ����� ��flag�����
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
            cout << "��";
          else cout << "  ";
 
        }
      }
      score += 10;
      Input_score();
      tianjia();
    }
  }
}
void Tetris1::Updata()          //���º���
{
  int i, flag;
  int nx, ny;
  for (i = 0; i < 4; i++)
  {
    nx = point[0] + sharp[id][i * 2];
    ny = point[1] + sharp[id][i * 2 + 1];
    SetPos((ny + 1) * 2+50, nx + 1);
    SetColor(0);
    cout << "��";
    map1[nx][ny] = 1;          //����������Ƿ�Ϊ�յĸ���
  }
 
  if (point[0] < top)
    top = point[0];          //��ߵ�ĸ���
 
  for (i = point[0]; i < point[0] + high[id]; i++)      //������
  {
    flag = 1;
    for (int j = 0; j < 13; j++)          //�ж�ĳһ���Ƿ����� ��flag�����
      if (map1[i][j] == 0)
        flag = 0;
    if (flag == 1)
    {
      for (int k = i; k >= top; k--)
      {
        for (int p = 0; p < 13; p++)
        {
          map1[k][p] = map[k - 1][p];
          SetPos((p + 1) * 2+50, k + 1);
          if (map1[k][p] == 1)
            cout << "��";
          else cout << "  ";
 
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
  cout << "�÷�: " << score;
}
void Tetris1::Input_score()
{
  SetColor(3);
  SetPos(80, 19);
  cout << "�÷�: " << score;
}
 
void Tetris::Welocme()      //��ӭ����
{
  SetColor(1);
  char x;
  while (1)
  {
    system("cls");
    cout << "�����������������������ߣ����ɡ���Ө������������������������" <<endl;
    cout << "                       ����˹����                    " << endl;
    cout << "��������������������������������������������������������" << endl;
    cout << "    ���1������ʽ��         "<< "    ���2������ʽ��" << endl;
    cout << "    �� - ��ת              " << "    W - ��ת" << endl;
    cout << "    �� - ��������          " << "    S - ��������" << endl;
    cout << "    �� - ����              " << "    D - ����" << endl;
    cout << "    �� - ����              " << "    A - ����" << endl;
    cout << "                 �ո� - ��ͣ     " << endl;
    cout << "����������������������������������������������������������" << endl;
    cout << "�� ��1��3ѡ���Ѷȡ�" << endl;
    SetPos(20, 10);
    x = getchar();
    if (x <= '9' && x >= '0')
    {
      rank = x - '0';
      break;
    }
  }
}
int Welocme()      //��ӭ����
{
  //SetColor(1);
  char x;int rank;
  while (1)
  {
    system("cls");
    cout << "�����������������������ߣ����ɡ���Ө������������������������" <<endl;
    cout << "                       ����˹����                    " << endl;
    cout << "��������������������������������������������������������" << endl;
    cout << "    ���1������ʽ��         "<< "    ���2������ʽ��" << endl;
    cout << "    �� - ��ת              " << "    W - ��ת" << endl;
    cout << "    �� - ��������          " << "    S - ��������" << endl;
    cout << "    �� - ����              " << "    D - ����" << endl;
    cout << "    �� - ����              " << "    A - ����" << endl;
    cout << "                 �ո� - ��ͣ     " << endl;
    cout << "����������������������������������������������������������" << endl;
    cout << "�� ��1��3ѡ���Ѷȡ�" << endl;
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
/*void Tetris1::Welocme()      //��ӭ����
{
  SetColor(1);
  char x;
  while (1)
  {
    system("cls");
    cout << "�����������������2���á�������������������" << endl;
    cout << "    ����˹����    " << endl;
    cout << "������������������������������������������" << endl;
    cout << "    ������ʽ��" << endl;
    cout << "    �� - ��ת" << endl;
    cout << "    �� - ��������" << endl;
    cout << "    �� - ����" << endl;
    cout << "    �� - ����" << endl;
    cout << "    �ո� - ��ͣ" << endl;
    cout << "������������������������������������������" << endl;
    cout << "�� ��1��3ѡ���Ѷȡ�" << endl;
    SetPos(20, 10);
    x = getchar();
    if (x <= '9' && x >= '0')
    {
      rank = x - '0';
      break;
    }
  }
}*/ 
 
void Tetris::SetColor(int color_num)      //������ɫ
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
 
void Tetris1::DrawMap()        //����Ϸʱ����
{
  int i;
  SetColor(0);
  SetColor(3);
  Input_score();
  SetPos(30+50,17);
  cout<<"���2";
  SetPos(30+50, 21);
  cout << "�Ѷȵȼ�: " << rank;
  SetPos(32+50,2);
  cout<< "��һͼ��";
}
void Tetris::DrawMap()        //����Ϸʱ����
{
  int i;
  SetColor(0);
 
  for (i =0; i < 48; i++)    //��24��
  {
    SetPos(i * 2, 0);
    cout << "��";
    SetPos(i * 2, 26);
    cout << "��";
  }
 
  for (i = 0; i <=26; i++)    //��26��
  {
    SetPos(0, i);
    cout << "��";
    SetPos(28, i);
    cout << "��";
    SetPos(50, i);
    cout << "��";
    SetPos(46, i);
    cout << "��";
    SetPos(78, i);
    cout << "��";
    SetPos(96, i);
    cout << "��";
  }
 
  for (i = 14; i < 24; i++)
  {
    SetPos(i * 2, 16);
    cout << "��";
  }
  for (i = 14; i < 24; i++)
  {
    SetPos(i * 2+50, 16);
    cout << "��";
  }
  for (i = 24; i < 44; i++)
  {
    SetPos(i * 2, 46);
    cout << "��";
  }
 for (i = 24; i < 48; i++)
  {
    SetPos(i * 2, 32);
    cout << "��";
  }
  SetColor(3);
  Input_score();
  SetPos(30,17);
  cout<<"���1";
  SetPos(30, 21);
  cout << "�Ѷȵȼ�: " << rank;
  SetPos(32, 2);
  cout << "��һͼ��";
}
 
void Tetris::Draw(int x, int y, int num)        //��ͼ��
{
  int nx, ny;
 
  for (int i = 0; i < 4; i++)
  {
    nx = x + sharp[num][2 * i];
    ny = y + sharp[num][2 * i + 1];
    SetPos((ny + 1) * 2, nx + 1);
    SetColor(i + 1);
    cout << "��";
    
  }
}
void Tetris1::Draw(int x, int y, int num)        //��ͼ��
{
  int nx, ny;
 
  for (int i = 0; i < 4; i++)
  {
    nx = x + sharp[num][2 * i];
    ny = y + sharp[num][2 * i + 1];
    SetPos((ny + 1) * 2+50, nx + 1);
    SetColor(i+ 1);
    cout << "��";
    
  }
}
void Tetris::ReDraw(int x, int y, int num)        //Ϊ����ͼ�ε�λ�����ͼ��
{
  int nx, ny;
  
  for (int i = 0; i < 4; i++)
  {
    nx = x + sharp[num][2 * i];
    ny = y + sharp[num][2 * i + 1];
   
    SetPos((ny + 1) * 2, nx + 1);
    cout << "  ";//��Ϊ�����ո�����Ż����档 
  }
}
void Tetris1::ReDraw(int x, int y, int num)        //Ϊ����ͼ�ε�λ�����ͼ��
{
  int nx, ny;
  
  for (int i = 0; i < 4; i++)
  {
    nx = x + sharp[num][2 * i];
    ny = y + sharp[num][2 * i + 1];
   
    SetPos((ny + 1) * 2+50, nx + 1);
    cout << "  ";//��Ϊ�����ո�����Ż����档 
  }
}
 
bool Tetris::Judge(int x, int y, int num)        //�ж���x, y ��ָλ���Ƿ�ɻ����Ϊ
{                          //num ��ͼ�Σ� �����ɻ��򷴻�true
  int nx, ny;
  for (int i = 0; i < 4; i++)
  {
    nx = x + sharp[num][2 * i];
    ny = y + sharp[num][2 * i + 1];
    if (!(nx < 25 && nx >=0 && !map[nx][ny]))
      return true;
  }
  return false;
}
bool Tetris::Judge1(int x, int y, int num)        //�ж���x, y ��ָλ���Ƿ�ɻ����Ϊ
{                          //num ��ͼ�Σ� �����ɻ��򷴻�true
  int nx, ny;
  for (int i = 0; i < 4; i++)
  {
    nx = x + sharp[num][2 * i];
    ny = y + sharp[num][2 * i + 1];
    if (!(nx < 25 && nx >=0 && ny < 13 && ny >= 0 && !map[nx][ny]))
      return true;
  }
  return false;
}
bool Tetris1::Judge(int x, int y, int num)        //�ж���x, y ��ָλ���Ƿ�ɻ����Ϊ
{                          //num ��ͼ�Σ� �����ɻ��򷴻�true
  int nx, ny;
  for (int i = 0; i < 4; i++)
  {
    nx = x + sharp[num][2 * i];
    ny = y + sharp[num][2 * i + 1];
    if (!(nx < 25&& nx >= 0 && !map1[nx][ny]))
      return true;
  }
  return false;
}
bool Tetris1::Judge1(int x, int y, int num)        //�ж���x, y ��ָλ���Ƿ�ɻ����Ϊ
{                          //num ��ͼ�Σ� �����ɻ��򷴻�true
  int nx, ny;
  for (int i = 0; i < 4; i++)
  {
    nx = x + sharp[num][2 * i];
    ny = y + sharp[num][2 * i + 1];
    if (!(nx < 25&& nx >= 0 && ny < 13 && ny >= 0 && !map1[nx][ny]))
      return true;
  }
  return false;
}
/*void Tetris1::Run()          //������Ϸ
{
  int next_id;
  srand((int)time(0));
 
  id = rand() % 15;
  next_id = rand() % 15;
 
  Draw(point[0], point[1], id);
  Draw(5, 16, next_id);
 
  int count;
  if (rank == 1)
    count = 150;
  else if (rank == 2)
    count = 100;
  else if (rank==3)
    count = 50;
  else
    count = 5;
  int i = 0;  //��ͬ�ȼ���Ӧ��ͬcount
 while(1)
 {
  
    if (!(i < count))        //i �� count ���ڿ���ʱ��
    {
      i = 0;
      if (Judge(point[0] + 1, point[1], id))      //��ĳһλ�ò�������Ļ�
      {
        Updata();
        id = next_id;
 
        ReDraw(5, 16, next_id);
        next_id = rand() % 15;
 
        point[0] = 0; point[1] = 5;
        Draw(point[0], point[1], id);
        Draw(5, 16, next_id);
 		return;
        if (Judge(point[0], point[1], id))
        {
          system("cls");
          SetPos(20, 10);
          cout << "��Ϸ������" << endl;
          SetPos(20, 11);
          cout << "��ķ���Ϊ " << score << endl;
          system("pause");
          exit(1);
          
        }
        
      }
      else          //��������
      {
        ReDraw(point[0], point[1], id);
        point[0]++;
        Draw(point[0], point[1], id);
      }
    }
 
    if (_kbhit())        //��������ֵʱ  
    {
      int key, key2;
      //key = _getch();
      //if (key == 119)//224
      //{
        key2 = _getch();
 		
        if (key2==119)      //72�����Ϸ����ʱ
        {
          int temp = id;
          Turn(id);
          if (Judge(point[0], point[1], id))
            id = temp;
          ReDraw(point[0], point[1], temp);
          Draw(point[0], point[1], id);
        }
        else if (key2 == )        //80�����·����ʱ
        {
          if (!Judge(point[0] + 2, point[1], id))
          {  
            ReDraw(point[0], point[1], id);
            point[0] += 2;
            Draw(point[0], point[1], id);
          }
        }
        else if (key2 == 97)        //75���������ʱ
        {
          if (!Judge(point[0], point[1] - 1, id))
          {  
            ReDraw(point[0], point[1], id);
            point[1]--;
            Draw(point[0], point[1], id);
          }
        }
        else if (key2 == 100)          //�����ҷ����ʱ
        {
          if (!Judge(point[0], point[1] + 1, id))
          { 
            ReDraw(point[0], point[1], id);
            point[1]++;
            Draw(point[0], point[1], id);
          }
        }
      //}
      else if (key == 32)          // ���¿ո���ͣ
        Pause();
        
    }
 	
    Sleep(1);    //�ȴ�1����
  	i++;        //����������
   	
}
}*/
int Run(Tetris &game,Tetris1 &game1)          //������Ϸ
{
  int next_id,next_id1;
  srand((int)time(0));
 
  game.setid ( rand() % 15);
  game1.setid(rand() % 15);
  next_id =rand() % 15;
  next_id1 =rand() % 15;
  game.Draw(game.getpoint0(), game.getpoint1(), game.getid());
  game1.Draw(game1.getpoint0(), game1.getpoint1(), game1.getid());
  game.Draw(5, 16, next_id);
  game1.Draw(5, 16, next_id1);
 
  
 
  
  while(1)
  {
  
    
     if (1)        //i �� count ���ڿ���ʱ��
    {
      if( game.Judge(game.getpoint0() + 1,  game.getpoint1(), game.getid())  )    //��ĳһλ�ò�������Ļ�
      {
        game.Updata();
        game.setid(next_id) ;
 
        game.ReDraw(5, 16, next_id);
        next_id = rand() % 15;
 
        game.setpoint1(0,5);
        game.Draw(game.getpoint0(), game.getpoint1(), game.getid());
        game.Draw(5, 16, next_id);
 		  if (game.Judge(game.getpoint0(), game.getpoint1(), game.getid())&&game1.Judge(game1.getpoint0(), game1.getpoint1(), game1.getid()))
        {
          return 0;
        }   
        
      }
      else
	  {
	  	//�������� 
   		game.ReDraw(game.getpoint0(), game.getpoint1(), game.getid());
    	game.setpoint(1,0);
   		game.Draw(game.getpoint0(), game.getpoint1(), game.getid());
	}
	if ( game1.Judge(game1.getpoint0() + 1,  game1.getpoint1(), game1.getid()) )     //��ĳһλ�ò�������Ļ�
      {
        game1.Updata();
        game1.setid( next_id1) ;
 		game1.ReDraw(5, 16, next_id1);
        next_id1 = rand() % 15;
 		game1.setpoint1(0,5);
        game1.Draw(game1.getpoint0(), game1.getpoint1(), game1.getid());
        game1.Draw(5, 16, next_id1);
 	if (game.Judge(game.getpoint0(), game.getpoint1(), game.getid())&&game1.Judge(game1.getpoint0(), game1.getpoint1(), game1.getid()))
        {
          return 0;
        }   
        
      }
      else
      {
      	game1.ReDraw(game1.getpoint0(), game1.getpoint1(), game1.getid());
    	game1.setpoint(1,0);
    	game1.Draw(game1.getpoint0(), game1.getpoint1(), game1.getid());
	  }
}
        
   
 	
    if (_kbhit())        //_kbhit()��������ֵʱ  
    {
    	int key, key2;
      key = _getch(); 
      
        if(key == 119)      //72�����Ϸ����ʱ
        {
          int temp =  game1.getid();
          game1.Turn(game1.getid());
          if (game1.Judge(game1.getpoint0(), game1.getpoint1(), game1.getid()))
            game1.setid (temp);
          game1.ReDraw(game1.getpoint0(), game1.getpoint1(), temp);
          game1.Draw(game1.getpoint0(), game1.getpoint1(), game1.getid());
        }
        if (key == 115)        //80�����·����ʱ
        {
          if (!game1.Judge(game1.getpoint0() + 2, game1.getpoint1(), game1.getid()))
          {  
            game1.ReDraw(game1.getpoint0(), game1.getpoint1(),game1.getid());
            game1.setpoint(2,0);
            game1.Draw(game1.getpoint0(), game1.getpoint1(), game1.getid());
          }
        }
        else if (key == 97)        //75���������ʱ
        {
          if (!game1.Judge1(game1.getpoint0(), game1.getpoint1() - 1, game1.getid()))
          {  
            game1.ReDraw(game1.getpoint0(), game1.getpoint1() ,game1.getid());
            game1.setpoint(0,-1);
            game1.Draw(game1.getpoint0(), game1.getpoint1() ,game1.getid());
          }
        }
        else if (key == 100)          //�����ҷ����ʱ
        {
          if (!game1.Judge1(game1.getpoint0(), game1.getpoint1()+1, game1.getid()))
          { 
           game1.ReDraw(game1.getpoint0(), game1.getpoint1() ,game1.getid());
            game1.setpoint(0,1);
            game1.Draw(game1.getpoint0(), game1.getpoint1() ,game1.getid());
          }
        }
       else if (key == 224)//224
      {
        key2 = _getch();
 
        if (key2 == 72)      //72�����Ϸ����ʱ
        {
          int temp =  game.getid();
          game.Turn(game.getid());
          if (game.Judge(game.getpoint0(), game.getpoint1(), game.getid()))
            game.setid (temp);
          game.ReDraw(game.getpoint0(), game.getpoint1(), temp);
          game.Draw(game.getpoint0(), game.getpoint1(), game.getid());
        }
        if (key2 == 80)        //80�����·����ʱ
        {
          if (!game.Judge(game.getpoint0() + 2, game.getpoint1(), game.getid()))
          {  
            game.ReDraw(game.getpoint0(), game.getpoint1(),game.getid());
            game.setpoint(2,0);
            game.Draw(game.getpoint0(), game.getpoint1(), game.getid());
          }
        }
        else if (key2 == 75)        //75���������ʱ
        {
          if (!game.Judge1(game.getpoint0(), game.getpoint1() - 1, game.getid()))
          {  
            game.ReDraw(game.getpoint0(), game.getpoint1() ,game.getid());
            game.setpoint(0,-1);
            game.Draw(game.getpoint0(), game.getpoint1() ,game.getid());
          }
        }
        else if (key2 == 77)          //�����ҷ����ʱ
        {
          if (!game.Judge1(game.getpoint0(), game.getpoint1()+1, game.getid()))
          { 
           game.ReDraw(game.getpoint0(), game.getpoint1() ,game.getid());
            game.setpoint(0,1);
            game.Draw(game.getpoint0(), game.getpoint1() ,game.getid());
          }
        }
       
      }
      
      else if (key == 32)          // ���¿ո���ͣ
      {
	  	Pause(game,game1);  
	  }
        
    
        
    
    
  }
  Sleep(400-game.getrank()*100);    //�ȴ�1����
   
}
}
int main()
{
 int rank=Welocme();
Tetris game(rank);
 Tetris1 game1(rank);
  system("cls");        //�����ӭ����
 game.DrawMap(); 
  game1.DrawMap();
  
  	while(Run(game,game1))
  	{
  		
	}
 	
   system("cls"); 
   
	if(game.getscore()>game1.getscore())
	{
	cout << "��������������������������������������������������������" << endl;
	cout<<  "                      ���1ʤ��                           "<<endl;
	cout << "��������������������������������������������������������" << endl;
	}
	
	else if(game.getscore()==game1.getscore())
	{
		cout << "��������������������������������������������������������" << endl;
	cout<<"                          ����ƽ��                        "<< endl;
	cout << "��������������������������������������������������������" << endl;
	}
	
	else
	{
		cout << "��������������������������������������������������������" << endl;
	cout<<"                          ���2ʤ��                        "<< endl; 
	cout << "��������������������������������������������������������" << endl;
	}
	Sleep(300);
 	return 0;
  
  
}