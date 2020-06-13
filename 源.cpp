#include<Windows.h>
#include<conio.h>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
using namespace std;
#define MapHeight 25//玩家游戏地图高度
#define MapWidth 30//玩家游戏地图宽度
#define Mapwidth 20//玩家小地图宽度
#define MapO2 64//玩家二地图基点
#define Map1Mid MapWidth/2-1
int GameState=0; //游戏运行的标志
int line1 = 0;	
int line2 = 0;	//玩家一、二通过line来关联产生垃圾行
//结构体表示方块坐标x，y
struct fangge {
	int x, y;
};
//初始化全地图值
int MapValue[MapHeight + MapO2][MapWidth + MapO2] = { 0 };
//设置地图坐标值
void setMapValue(int x, int y, int value) {
	MapValue[x][y] = value;
	MapValue[x + 1][y] = value;
}
//隐藏光标
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = FALSE;
	cursor.dwSize = sizeof(cursor);
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle, &cursor);
}
//光标去到某处
void gotoXY(int x, int y) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X = x; coord.Y = y;
	SetConsoleCursorPosition(handle, coord);
}
//枚举将颜色与数字关联
enum Color {
	蓝色 = 9, 绿色, 青色, 红色, 紫色, 黄色, 白色 = 15,墨绿色=2
};
//设置颜色 
void setColor (enum Color color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
//获取min到max之间的随机数
int getRandRange(int min, int max)
{
	return rand() % (max - min + 1) + min;
}
//渲染类 开始界面、初始化游戏界面、结束界面
class Drawing {
public:
	void drawMap();//游戏运行的静态边框
	void welcome();//欢迎界面
	void overScreen(int s1, int s2);//结束界面
};
void Drawing::welcome()
{
	setColor(黄色);
	while (1)
	{
		setColor(墨绿色);
		gotoXY(39, 13);
		cout << "Player1:林小斌";
		setColor(青色);
		gotoXY(67, 13);
		cout << "Player2:林小辉";
		setColor(红色);
		gotoXY(36, 4);
		for (int i = 0; i < 24; i++)
			cout << "■";
		for (int i = 0; i < 11; i++) {
			gotoXY(36, 4 + i);
			cout << "■";
		}
		for (int i = 0; i < 11; i++) {
			gotoXY(82, 4 + i);
			cout << "■";
		}
		gotoXY(36, 15);
		for (int i = 0; i < 24; i++)
			cout << "■";
		setColor(黄色);
		gotoXY(53, 6);
		cout << "欢  迎  来  到";
		gotoXY(55, 9);
		cout << "我罗斯方块";
		setColor(蓝色);
		gotoXY(66, 11);
		cout << "→双人对战模式";
		gotoXY(50, 20);
		setColor(白色);
		cout << "按任意键开始游戏……";
		char c;
		c = getchar();
		break;
	}
}
void Drawing::drawMap() {
	setColor(墨绿色);//玩家一
	for (int i = 0; i <= MapWidth; i += 2) {
		gotoXY(i, 0);
		setMapValue(i, 0, 2);
		cout << "█";
		gotoXY(i, MapHeight);
		setMapValue(i, MapHeight, 2);
		cout << "█";
	}
	for (int i = 0; i <= MapHeight; i++) {
		gotoXY(0, i);
		setMapValue(0, i, 2);
		cout << "█";
		gotoXY(MapWidth, i);
		setMapValue(MapWidth, i, 2);
		cout << "█";
	}
	for (int i = MapWidth + 2; i <= MapWidth + Mapwidth; i += 2) {
		gotoXY(i, 0);
		setMapValue(i, 0, 2);
		cout << "█";
		gotoXY(i, MapHeight);
		setMapValue(i, MapHeight, 2);
		cout << "█";
	}
	for (int i = 0; i <= MapHeight; i++) {
		gotoXY(MapWidth + Mapwidth, i);
		setMapValue(MapWidth + Mapwidth, i, 2);
		cout << "█";
	}
	setColor(白色);
	gotoXY(MapWidth + 8, 2);
	cout << "下一个";
	gotoXY(MapWidth + 8, 8);
	cout << "玩家一";
	gotoXY(MapWidth + 8, 10);
	cout << "林小斌";
	setColor(红色);
	gotoXY(MapWidth + 9, 15);
	cout << "得分：";
	setColor(黄色);
	gotoXY(MapWidth + 9, 19);
	cout << "旋转";
	gotoXY(MapWidth + 10, 20);
	cout << "W";
	gotoXY(MapWidth + 2, 21);
	cout << "左移 A  S  D 右移";
	gotoXY(MapWidth + 8, 22);
	cout << "下落";
	setColor(青色);//玩家二
	for (int i = MapO2 + Mapwidth; i <= MapWidth + MapO2 + Mapwidth; i += 2) {
		gotoXY(i, 0);
		setMapValue(i, 0, 2);
		cout << "█";
		gotoXY(i, MapHeight);
		setMapValue(i, MapHeight, 2);
		cout << "█";
	}
	for (int i = 0; i <= MapHeight; i++) {
		gotoXY(MapO2 + Mapwidth, i);
		setMapValue(MapO2 + Mapwidth, i, 2);
		cout << "█";
		gotoXY(MapWidth + MapO2 + Mapwidth, i);
		setMapValue(MapWidth + MapO2 + Mapwidth, i, 2);
		cout << "█";
	}
	for (int i = MapO2; i <= MapO2 + Mapwidth; i += 2) {
		gotoXY(i, 0);
		setMapValue(i, 0, 2);
		cout << "█";
		gotoXY(i, MapHeight);
		setMapValue(i, MapHeight, 2);
		cout << "█";
	}
	for (int i = 0; i <= MapHeight; i++) {
		gotoXY(MapO2, i);
		setMapValue(MapO2, i, 2);
		cout << "█";
	}
	setColor(白色);
	gotoXY(MapO2 + 8, 2);
	cout << "下一个";
	gotoXY(MapO2 + 8, 8);
	cout << "玩家二";
	gotoXY(MapO2 + 8, 10);
	cout << "林小辉";
	setColor(红色);
	gotoXY(MapO2 + 9, 15);
	cout << "得分：";
	setColor(黄色);
	gotoXY(MapO2 + 9, 19);
	cout << "旋转";
	gotoXY(MapO2 + 10, 20);
	cout << "↑";
	gotoXY(MapO2 + 2, 21);
	cout << "左移 ← ↓ → 右移";
	gotoXY(MapO2 + 9, 22);
	cout << "下落";
}
void Drawing::overScreen(int score1, int score2) {
	int win = 1;
	if (score2 > score1) win = 2;
	gotoXY(54, 7);
	if (win == 1)
		cout << "玩家一获胜";
	else
		cout << "玩家二获胜";
	gotoXY(57, 9);
	cout << "得分：";
	gotoXY(57, 10);
	if (win == 1) cout << score1;
	else cout << score2;
	gotoXY(53, 12);
	cout << "按任意键结束......";
}
//方块的基类
class Block
{
public:
	int x0, y0;//玩家地图基点
	fangge f[4];//方块四个方格坐标
	int shape;//方块的形状
	int state;//之前是想表示方块状态，后来发觉没啥用，改的话派生类得改很多
	void clearNextBlock(int wanjia);//显示下一个方块前，清除上一次显示的
	void drawNextBlock(int a,int wanjia);//在小地图画下一个方块
	virtual void change() {}//同类方块之间切换形状，声明为虚函数
	void down();//下降
	void moveLeft();//左移
	void moveRight();//右移
	bool checkLeft();//检查能否左移
	bool checkRight();//检查能否右移
	bool checkDown();//检查能否下降
	void show();//显示方块
	void hide();//消除方块
	bool checkOver();//检查游戏是否结束
	
};
void Block::clearNextBlock(int wanjia) {
	int OO = MapWidth;
	if (wanjia == 2) OO = 64;
	for (int i = OO +4; i < OO + 14; i += 2) {
		for (int j = 3; j < 7; j++) {
			gotoXY(i, j);
			cout << "  ";
		}
	}
}
void Block::drawNextBlock(int a,int wanjia) {
	clearNextBlock(wanjia);
	int OO = MapWidth;
	if (wanjia == 2) OO = 64;
	OO++;
	switch (a) {
	//田字型
	case 1:
		setColor(蓝色);
		gotoXY(OO + 8, 4);
		cout << "██";
		gotoXY(OO + 8, 5);
		cout << "██";
		break;
	//一字型
	case 2:
		setColor(绿色);
		gotoXY(OO + 6, 4);
		cout << "████";
		break;
	//倒T字型
	case 3:
		setColor(青色);
		gotoXY(OO + 8, 4);
		cout << "█";
		gotoXY(OO + 6, 5);
		cout << "███";
		break;
	//反L字型
	case 4:
		setColor(红色);
		gotoXY(OO + 6, 4);
		cout << "█";
		gotoXY(OO + 6, 5);
		cout << "███";
		break;
	//L字型
	case 5:
		setColor(紫色);
		gotoXY(OO + 10, 4);
		cout << "█";
		gotoXY(OO + 6, 5);
		cout << "███";
		break;
	//反Z字型
	case 6:
		setColor(黄色);
		gotoXY(OO + 8, 4);
		cout << "██";
		gotoXY(OO + 6, 5);
		cout << "██";
		break;
	//Z字型
	case 7:
		setColor(白色);
		gotoXY(OO + 6, 4);
		cout << "██";
		gotoXY(OO + 8, 5);
		cout << "██";
		break;
	}
}
bool Block::checkLeft() 
{
	for (int i = 0; i < 4; i++) {
		if (MapValue[f[i].x - 2][f[i].y] != 0) return false;
	}
	return true;
}
bool Block::checkRight()
{
	for (int i = 0; i < 4; i++) {
		if (MapValue[f[i].x + 2][f[i].y] != 0) return false;
	}
	return true;
}
bool Block::checkDown()
{
	for (int i = 0; i < 4; i++) {
		if (MapValue[f[i].x][f[i].y + 1] != 0)
		{
			state = 0;
			for (int i = 0; i < 4; i++) {
				setMapValue(f[i].x, f[i].y, 1);
			}
			setColor(白色);
			show();
			return false;
		}
	}
	return true;
}
void Block::down()
{
	if (state == 1) {
		if (checkDown()) {
			hide();
			for (int i = 0; i < 4; i++) {
				f[i].y += 1;
			}
			show();
		}
	}
}
void Block::moveLeft()
{
	if (state == 1) {
		if (checkLeft()) {
			hide();
			for (int i = 0; i < 4; i++) {
				f[i].x -= 2;
			}
			show();
		}
	}
}
void Block::moveRight()
{
	if (state == 1) {
		if (checkRight()) {
			hide();
			for (int i = 0; i < 4; i++) {
				f[i].x += 2;
			}
			show();
		}
	}
}
void Block::show()
{
	for (int i = 0; i < 4; i++) {
		gotoXY(f[i].x, f[i].y);
		cout << "█";
	}
}
void Block::hide() {
	for (int i = -0; i < 4; i++) {
		gotoXY(f[i].x, f[i].y);
		cout << "  ";
	}
}
bool Block::checkOver() {
	for (int i = 0; i < 4; i++) {
		if (MapValue[f[i].x][f[i].y] != 0)
			return  false;
	}
	return true;
}
//通过Block类派生出七种基本子类
//田字型
class Block1 :public Block
{
public:
	Block1(int x0, int y0);
	void change(){}
};
Block1::Block1(int x0, int y0)
{
	setColor(蓝色);
	shape = 0;
	state = 1;
	f[0] = { Map1Mid + x0,2 };
	f[1] = { Map1Mid + 2 + x0,2 };
	f[2] = { Map1Mid + x0,3 };
	f[3] = { Map1Mid + 2 + x0,3 };
	show();
	checkOver();
}
//一字型
class Block2 :public Block
{
public:
	Block2(int x0, int y0);
	void change();
};
Block2::Block2(int x0, int y0)
{
	setColor(青色);
	shape = 0;
	state = 1;
	f[0] = { Map1Mid-2 + x0 ,2 };
	f[1] = { Map1Mid + x0 ,2 };
	f[2] = { Map1Mid + 2 + x0,2 };
	f[3] = { Map1Mid +4 + x0,2 };
	show();
	checkOver();
}
void Block2::change() {
	if (state == 1) {
		hide();
		switch (shape) {
		case 0:
		case 2:
			if (MapValue[f[0].x + 2][f[0].y - 1] != 0 || MapValue[f[2].x - 2][f[2].y + 1] || MapValue[f[3].x - 4][f[3].y + 2] != 0) break;
			f[0].x += 2; f[0].y -= 1;
			f[2].x -= 2; f[2].y += 1;
			f[3].x -= 4; f[3].y += 2;
			shape = (++shape) % 4;
			break;
		case 1:
		case 3:
			if (MapValue[f[0].x - 2][f[0].y + 1] != 0 || MapValue[f[2].x + 2][f[2].y - 1] || MapValue[f[3].x + 4][f[3].y - 2] != 0) break;
			f[0].x -= 2; f[0].y += 1;
			f[2].x += 2; f[2].y -= 1;
			f[3].x += 4; f[3].y -= 2;
			shape = (++shape) % 4;
			break;
		}
		show();
	}
}
//倒T字型
class Block3 :public Block
{
public:
	Block3(int x0, int y0);
	void change();
};
Block3::Block3(int x0, int y0)
{
	setColor(青色);
	shape = 0;
	state = 1;
	f[0] = { Map1Mid - 2 + x0,2 };
	f[2] = { Map1Mid + x0,2 };
	f[3] = { Map1Mid + 2 + x0,2 };
	f[1] = { Map1Mid + x0,1 };
	show();
	checkOver();
}
void Block3::change() {
	if (state == 1) {
		hide();
		switch (shape) {
		case 0:
			if (MapValue[f[0].x + 2][f[0].y - 1] || MapValue[f[1].x + 2][f[1].y + 1] != 0 || MapValue[f[3].x - 2][f[3].y + 1] != 0)  break;
			f[0].x += 2; f[0].y -= 1;
			f[1].x += 2; f[1].y += 1;
			f[3].x -= 2; f[3].y += 1;
			break;
		case 1:
			if (MapValue[f[0].x + 2][f[0].y + 1] != 0 || MapValue[f[1].x - 2][f[1].y + 1] != 0 || MapValue[f[3].x - 2][f[3].y - 1] != 0) break;
			f[0].x += 2; f[0].y += 1;
			f[1].x -= 2; f[1].y += 1;
			f[3].x -= 2; f[3].y -= 1;
			break;
		case 2:
			if (MapValue[f[0].x - 2][f[0].y + 1] != 0 || MapValue[f[1].x - 2][f[1].y - 1] != 0 || MapValue[f[3].x + 2][f[3].y - 1] != 0) break;
			f[0].x -= 2; f[0].y += 1;
			f[1].x -= 2; f[1].y -= 1;
			f[3].x += 2; f[3].y -= 1;
			break;
		case 3:
			if (MapValue[f[0].x - 2][f[0].y - 1] != 0 || MapValue[f[1].x + 2][f[1].y - 1] != 0 || MapValue[f[3].x + 2][f[3].y + 1] != 0) break;
			f[0].x -= 2; f[0].y -= 1;
			f[1].x += 2; f[1].y -= 1;
			f[3].x += 2; f[3].y += 1;
			break;
		}
		shape = (++shape) % 4;
		show();
	}
}
class Block4 :public Block
{
public:
	Block4(int x0, int y0);
	void change();
};
//反L字型
Block4::Block4(int x0, int y0)
{
	setColor(红色);
	shape = 0;
	state = 1;
	f[0] = { Map1Mid - 2 + x0,1 };
	f[1] = { Map1Mid - 2 + x0,2 };
	f[2] = { Map1Mid + x0,2 };
	f[3] = { Map1Mid + 2 + x0,2 };
	show();
	checkOver();
}
void Block4::change() {
	if (state == 1) {
		hide();
		switch (shape) {
		case 0:
			if (MapValue[f[0].x + 4][f[0].y] || MapValue[f[3].x - 2][f[3].y + 1] != 0) break;
			f[0].x += 4;
			f[1].x += 2; f[1].y -= 1;
			f[3].x -= 2; f[3].y += 1;
			break;
		case 1:
			if (MapValue[f[0].x][f[0].y + 2] != 0 || MapValue[f[3].x - 2][f[3].y - 1] != 0) break;
			f[0].y += 2;
			f[1].x += 2; f[1].y += 1;
			f[3].x -= 2; f[3].y -= 1;
			break;
		case 2:
			if (MapValue[f[0].x-4][f[0].y] != 0 || MapValue[f[3].x + 2][f[3].y - 1] != 0) break;
			f[0].x -= 4;
			f[1].x -= 2; f[1].y += 1;
			f[3].x += 2; f[3].y -= 1;
			break;
		case 3:
			if (MapValue[f[0].x ][f[0].y - 2] != 0 || MapValue[f[3].x + 2][f[3].y + 1] != 0) break;
			f[0].y -= 2;
			f[1].x -= 2; f[1].y -= 1;
			f[3].x += 2; f[3].y += 1;
			break;
		}
		shape = (++shape) % 4;
		show();
	}
}
//L字型
class Block5 :public Block
{
public:
	Block5(int x0, int y0);
	void change();
};
Block5::Block5(int x0, int y0)
{
	setColor(紫色);
	shape = 0;
	state = 1;
	f[0] = { Map1Mid - 2 + x0,2 };
	f[1] = { Map1Mid + x0 ,2 };
	f[2] = { Map1Mid + 2 + x0 ,2 };
	f[3] = { Map1Mid + x0 + 2,1 };
	show();
	checkOver();
}
void Block5::change() {
	if (state == 1) {
		hide();
		switch (shape) {
		case 0:
			if (MapValue[f[0].x + 2][f[0].y - 1] != 0 || MapValue[f[3].x][f[3].y + 2] != 0) break;
			f[0].x += 2; f[0].y -= 1;
			f[2].x -= 2; f[2].y += 1;
			f[3].y += 2;
			break;
		case 1:
			if (MapValue[f[0].x + 2][f[0].y + 1] || MapValue[f[3].x - 4][f[3].y ] != 0) break;
			f[0].x += 2; f[0].y += 1;
			f[2].x -= 2; f[2].y -= 1;
			f[3].x -= 4;
			break;
		case 2:
			if (MapValue[f[0].x - 2][f[0].y + 1] != 0 || MapValue[f[3].x][f[3].y - 2] != 0) break;
			f[0].x -= 2; f[0].y += 1;
			f[2].x += 2; f[2].y -= 1;
			f[3].y -= 2;
			break;
		case 3:
			if (MapValue[f[0].x - 2][f[0].y - 1] != 0 || MapValue[f[3].x + 4][f[3].y] != 0) break;
			f[0].x -= 2; f[0].y -= 1;
			f[2].x += 2; f[2].y += 1;
			f[3].x += 4;
			break;
		}
		shape = (++shape) % 4;
		show();
	}
}
//反Z字型
class Block6 :public Block
{
public:
	Block6(int x0, int y0);
	void change();
};
Block6::Block6(int x0, int y0)
{
	setColor(黄色);
	shape = 0;
	state = 1;
	f[0] = { Map1Mid - 2 + x0,3 };
	f[1] = { Map1Mid + x0,3 };
	f[2] = { Map1Mid + x0,2 };
	f[3] = { Map1Mid + 2 + x0,2 };
	show();
	checkOver();
}
void Block6::change() {
	if (state == 1) {
		HideCursor();
		hide();
		switch (shape) {
		case 0:
		case 2:
			if (MapValue[f[0].x + 2][f[0].y - 1] != 0 || MapValue[f[3].x - 4][f[3].y] != 0) break;
			f[0].x += 2; f[0].y -= 1;
			f[2].x -= 2; f[2].y -= 1;
			f[3].x -= 4;
			break;
		case 1:
		case 3:
			if (MapValue[f[0].x - 2][f[0].y + 1] || MapValue[f[3].x + 4][f[3].y] != 0) break;
			f[0].x -= 2; f[0].y += 1;
			f[2].x += 2; f[2].y += 1;
			f[3].x += 4;
			break;
		}
		shape = (++shape) % 4;
		show();
	}
}
//Z字型
class Block7 :public Block
{
public:
	Block7(int x0, int y0);
	void change();
};
Block7::Block7(int x0, int y0)
{
	setColor(白色);
	shape = 0;
	state = 1;
	f[0] = { Map1Mid - 2 + x0,2 };
	f[1] = { Map1Mid + x0 ,2 };
	f[2] = { Map1Mid + x0,3 };
	f[3] = { Map1Mid + 2 + x0,3 };
	show();
	checkOver();
}
void Block7::change() {
	if (state == 1) {
		HideCursor();
		hide();
		switch (shape) {
		case 0:
		case 2:
			if (MapValue[f[0].x + 2][f[0].y - 1] != 0 || MapValue[f[3].x - 4][f[3].y] != 0) break;
			f[0].x += 2; f[0].y -= 1;
			f[2].x -= 2; f[2].y -= 1;
			f[3].x -= 4;
			break;
		case 1:
		case 3:
			if (MapValue[f[0].x - 2][f[0].y + 1] != 0 || MapValue[f[3].x + 4][f[3].y] != 0) break;
			f[0].x -= 2; f[0].y += 1;
			f[2].x += 2; f[2].y += 1;
			f[3].x +=4;
			break;
		}
		shape = (++shape) % 4;
		show();
	}
}
//在方块类的基础上派生出两个玩家类，以便双人游戏
class Player1 :public Block
{
private:
	int n, m;//产生连个随机数
	Block* b;//作为基类指针，以便后面指向新产生的方块
	int Time;//双人游戏时，对时间的控制
public:
	int score;//记录得分
	Player1();//构造函数
	void readKey(Block *b);//键盘读入
	int checkFull();//检查是否满行，并消行
	void Run();//游戏运行，方块下落
	void newShow(int i);//消行或增加垃圾行后刷新画布
	void showScore();//分数变化时，刷新分数
	void addLine();//增加垃圾行
};
Player1::Player1() {
	x0 = 0; y0 = 0;
	Time = 0;
	score = 0;
	showScore();
	n = getRandRange(1, 7);
	m = getRandRange(1, 7);
	b = new Block;
	drawNextBlock(n ,1 );
	switch (m)
	{
	case 1:b = new Block1(x0, y0); break;
	case 2:b = new Block2(x0, y0); break;
	case 3:b = new Block3(x0, y0); break;
	case 4:b = new Block4(x0, y0); break;
	case 5:b = new Block5(x0, y0); break;
	case 6:b = new Block6(x0, y0); break;
	case 7:b = new Block7(x0, y0); break;
	}
}
void Player1::readKey(Block *b)
{
	int key=0;
	if (_kbhit())//若键盘有值输入
	{
		key = _getch();
		if (key == 'w')	b->change();//w键 换形
		if (key == 's')				//s键 加速
		{
			for (int i = 0; i < 3; i++) {
				if (b->checkDown()) b->down();
			}
		}
		if (key == 'a')				//a键 左移
		{
			if (b->checkLeft()) b->moveLeft();
		}
		if (key == 'd')				//d键 右移
		{
			if (b->checkRight()) b->moveRight();
		}
	}
}
int Player1::checkFull()
{
	int count = 0;//计算消行数
	for (int i = MapHeight - 1; i > 3; i--) //从下往上读
	{
		int flag = 1;
		for (int j = x0 + 2; j < x0 + MapWidth-1; j += 2)//从左往右读
		{
			if (MapValue[j][i] == 0) {
				flag = 0; break;
			}
		}
		if (flag == 1)
		{
			for (int j = x0 + 2; j < x0 + MapWidth-1; j += 2) 
			{
				for (int k = i; k > 3; k--) {
					MapValue[j][k] = MapValue[j][k - 1];//将游戏地图值上移一行
				}
			}
			count++;
			newShow(i);
			i++;
		}
	}
	line2 = count;
	score += count * 100;
	showScore();
	return 0;
}
void Player1::addLine()
{
	while (line1--) {//增加line1行
		for (int j = x0 + 2; j < x0 + MapWidth - 1; j += 2)//将游戏地图值往上移一行
		{
			for (int k = 4; k < MapHeight; k++) {
				MapValue[j][k] = MapValue[j][k + 1];
			}
		}
		for (int j = x0 + 2; j < x0 + MapWidth - 1; j += 2) {//随机增加一行
			int n = getRandRange(0, 1);
			setMapValue(j, MapHeight - 1, n);
		}
		newShow(MapHeight - 1);
	}
}
void Player1::newShow(int ii)
{
	setColor(白色);
	for (int i = ii; i > 3; i--) {
		for (int j = x0 + 2; j < x0 + MapWidth - 1; j += 2) {
			gotoXY(j, i);
			if (MapValue[j][i] == 1) cout << "█";
			else  cout << "  ";
		}
	}
}
void Player1::showScore() {
	setColor(红色);
	gotoXY(MapWidth + 9, 16);
	cout << "        ";
	gotoXY(MapWidth + 9, 16);
	printf("%05d", score);
}
void Player1::Run()
{
	while (1)
	{
		//判断是否产生垃圾行
		if(line1!=0){
			addLine();
			line1 = 0;
		}
		if (Time > 150) { //标记时间，与双人有关
			Time = 0;
			//下落
			if (b->checkDown()) b->down();
			//不能下落
			else {
				//消行，并改变玩家二的line值，玩家二产生垃圾行
				checkFull();
				//准备下落新方块，并产生下一个方块
				m = n;
				n = getRandRange(1, 7);
				drawNextBlock(n, 1);
				switch (m)
				{
				case 1:b = new Block1(x0, y0); break;
				case 2:b = new Block2(x0, y0); break;
				case 3:b = new Block3(x0, y0); break;
				case 4:b = new Block4(x0, y0); break;
				case 5:b = new Block5(x0, y0); break;
				case 6:b = new Block6(x0, y0); break;
				case 7:b = new Block7(x0, y0); break;
				}
				//检查产生新方块时，是否已经到达上端
				if (!(b->checkOver())) {
					score = -1;
					GameState = 0;
				}
			}

		}
		//读入按键
		readKey(b);
		//值越小读入按键更流畅，速度也更快
		//通过Sleep和Time的使用，run1和run2交替执行，实现双人
		Sleep(0.00001);
		Time++;
		break;
	}
}
//玩家二与玩家一基本相同
class Player2 :public Block
{
private:
	int n, m;//随机数
	Block* b;
	int Time;
public:
	int score;
	Player2();
	void readKey(Block* b);//键盘读入
	int checkFull();//检查是否满行
	void Run();//游戏运行
	void newShow(int i);//消行后刷新画布
	void showScore();
	void addLine();
};
Player2::Player2() {
	x0 = 84;
	y0 = 0;
	score = 0;
	showScore();
	n = getRandRange(1, 7);
	m = getRandRange(1, 7);
	b = new Block;
	drawNextBlock(n , 2);
	switch (m)
	{
	case 1:b = new Block1(x0, y0); break;
	case 2:b = new Block2(x0, y0); break;
	case 3:b = new Block3(x0, y0); break;
	case 4:b = new Block4(x0, y0); break;
	case 5:b = new Block5(x0, y0); break;
	case 6:b = new Block6(x0, y0); break;
	case 7:b = new Block7(x0, y0); break;
	}
}
void Player2::readKey(Block* b)
{
	int key = 0;
	if (_kbhit())			
	{
		if (_kbhit() != 0) {
			key = _getch();
		}
		//wsad方向键
		if (key == 72)	b->change(); //向上键 换形
		if (key == 80)				//向下键 加速
		{
			for (int i = 0; i < 3; i++) {
				if (b->checkDown()) b->down();
			}
		}
		if (key == 75)				//向左键 左移
		{
			if (b->checkLeft()) b->moveLeft();
		}
		if (key == 77)					//向右向键 右移
		{
			if (b->checkRight()) b->moveRight();
		}
	}
}
int Player2::checkFull()
{
	int count = 0;
	for (int i = MapHeight - 1; i > 3; i--)
	{
		int flag = 1;
		for (int j = x0 + 2; j < x0 + MapWidth - 1; j += 2)
		{
			if (MapValue[j][i] == 0) {
				flag = 0; break;
			}
		}
		if (flag == 1)
		{
			for (int j = x0 + 2; j < x0 + MapWidth - 1; j += 2)
			{
				for (int k = i; k > 3; k--) {
					MapValue[j][k] = MapValue[j][k - 1];
				}
			}
			count++;
			newShow(i);
			i++;
			//分数
		}
	}
	line1 = count;
	score += count * 100;
	showScore();
	return 0;
}
void Player2::addLine()
{
	while (line2--) {
		for (int j = x0 + 2; j < x0 + MapWidth - 1; j += 2)
		{
			for (int k = 4; k < MapHeight; k++) {
				MapValue[j][k] = MapValue[j][k + 1];
			}
		}
		for (int j = x0 + 2; j < x0 + MapWidth - 1; j += 2) {
			int n = getRandRange(0, 1);
			setMapValue(j, MapHeight - 1, n);
		}
		newShow(MapHeight - 1);
	}
}
void Player2::newShow(int ii)
{
	setColor(白色);
	for (int i = ii; i > 3; i--) {
		for (int j = x0 + 2; j < x0 + MapWidth - 1; j += 2) {
			gotoXY(j, i);
			if (MapValue[j][i] == 1) cout << "█";
			else  cout << "  ";
		}
	}
}
void Player2::showScore() {
	setColor(红色);
	gotoXY(MapO2 + 9, 16);
	cout << "        ";
	gotoXY(MapO2 + 9, 16);
	printf("%05d", score);
}
void Player2::Run()
{
	while (1)
	{
		if (line2 != 0) {
			addLine();
			line2 = 0;
		}
		if (Time > 150) {
			Time = 0;
			if (b->checkDown()) b->down();
			else {
				checkFull(); 
				m = n;
				n = getRandRange(1, 7);
				drawNextBlock(n, 2);
				switch (m)
				{
				case 1:b = new Block1(x0, y0); break;
				case 2:b = new Block2(x0, y0); break;
				case 3:b = new Block3(x0, y0); break;
				case 4:b = new Block4(x0, y0); break;
				case 5:b = new Block5(x0, y0); break;
				case 6:b = new Block6(x0, y0); break;
				case 7:b = new Block7(x0, y0); break;
				}
				if (!(b->checkOver())) {
					score = -1;
					GameState = 0;
				}
			}
			
		}
		readKey(b);
		Sleep(1);
		Time++;
		break;
	}
}
//游戏类
class Game
{
public:
	void RunGame();
};
void Game::RunGame()
{
	HideCursor();//隐藏光标
	Drawing Draw;
	Draw.welcome();
	system("cls");
	Draw.drawMap();
	Player1 player1;
	Player2 player2;
	//运行游戏
	while (GameState) {
		player1.Run();
		player2.Run();
	}
	system("cls");
	Draw.overScreen(player1.score, player2.score);
	system("pause>nul");
}

int main() {
	srand(time(NULL));
	GameState = 1;
	Game game;
	game.RunGame();
	system("pause>nul");
}