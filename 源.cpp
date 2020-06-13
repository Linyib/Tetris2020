#include<Windows.h>
#include<conio.h>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
using namespace std;
#define MapHeight 25//�����Ϸ��ͼ�߶�
#define MapWidth 30//�����Ϸ��ͼ���
#define Mapwidth 20//���С��ͼ���
#define MapO2 64//��Ҷ���ͼ����
#define Map1Mid MapWidth/2-1
int GameState=0; //��Ϸ���еı�־
int line1 = 0;	
int line2 = 0;	//���һ����ͨ��line����������������
//�ṹ���ʾ��������x��y
struct fangge {
	int x, y;
};
//��ʼ��ȫ��ͼֵ
int MapValue[MapHeight + MapO2][MapWidth + MapO2] = { 0 };
//���õ�ͼ����ֵ
void setMapValue(int x, int y, int value) {
	MapValue[x][y] = value;
	MapValue[x + 1][y] = value;
}
//���ع��
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = FALSE;
	cursor.dwSize = sizeof(cursor);
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle, &cursor);
}
//���ȥ��ĳ��
void gotoXY(int x, int y) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X = x; coord.Y = y;
	SetConsoleCursorPosition(handle, coord);
}
//ö�ٽ���ɫ�����ֹ���
enum Color {
	��ɫ = 9, ��ɫ, ��ɫ, ��ɫ, ��ɫ, ��ɫ, ��ɫ = 15,ī��ɫ=2
};
//������ɫ 
void setColor (enum Color color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
//��ȡmin��max֮��������
int getRandRange(int min, int max)
{
	return rand() % (max - min + 1) + min;
}
//��Ⱦ�� ��ʼ���桢��ʼ����Ϸ���桢��������
class Drawing {
public:
	void drawMap();//��Ϸ���еľ�̬�߿�
	void welcome();//��ӭ����
	void overScreen(int s1, int s2);//��������
};
void Drawing::welcome()
{
	setColor(��ɫ);
	while (1)
	{
		setColor(ī��ɫ);
		gotoXY(39, 13);
		cout << "Player1:��С��";
		setColor(��ɫ);
		gotoXY(67, 13);
		cout << "Player2:��С��";
		setColor(��ɫ);
		gotoXY(36, 4);
		for (int i = 0; i < 24; i++)
			cout << "��";
		for (int i = 0; i < 11; i++) {
			gotoXY(36, 4 + i);
			cout << "��";
		}
		for (int i = 0; i < 11; i++) {
			gotoXY(82, 4 + i);
			cout << "��";
		}
		gotoXY(36, 15);
		for (int i = 0; i < 24; i++)
			cout << "��";
		setColor(��ɫ);
		gotoXY(53, 6);
		cout << "��  ӭ  ��  ��";
		gotoXY(55, 9);
		cout << "����˹����";
		setColor(��ɫ);
		gotoXY(66, 11);
		cout << "��˫�˶�սģʽ";
		gotoXY(50, 20);
		setColor(��ɫ);
		cout << "���������ʼ��Ϸ����";
		char c;
		c = getchar();
		break;
	}
}
void Drawing::drawMap() {
	setColor(ī��ɫ);//���һ
	for (int i = 0; i <= MapWidth; i += 2) {
		gotoXY(i, 0);
		setMapValue(i, 0, 2);
		cout << "��";
		gotoXY(i, MapHeight);
		setMapValue(i, MapHeight, 2);
		cout << "��";
	}
	for (int i = 0; i <= MapHeight; i++) {
		gotoXY(0, i);
		setMapValue(0, i, 2);
		cout << "��";
		gotoXY(MapWidth, i);
		setMapValue(MapWidth, i, 2);
		cout << "��";
	}
	for (int i = MapWidth + 2; i <= MapWidth + Mapwidth; i += 2) {
		gotoXY(i, 0);
		setMapValue(i, 0, 2);
		cout << "��";
		gotoXY(i, MapHeight);
		setMapValue(i, MapHeight, 2);
		cout << "��";
	}
	for (int i = 0; i <= MapHeight; i++) {
		gotoXY(MapWidth + Mapwidth, i);
		setMapValue(MapWidth + Mapwidth, i, 2);
		cout << "��";
	}
	setColor(��ɫ);
	gotoXY(MapWidth + 8, 2);
	cout << "��һ��";
	gotoXY(MapWidth + 8, 8);
	cout << "���һ";
	gotoXY(MapWidth + 8, 10);
	cout << "��С��";
	setColor(��ɫ);
	gotoXY(MapWidth + 9, 15);
	cout << "�÷֣�";
	setColor(��ɫ);
	gotoXY(MapWidth + 9, 19);
	cout << "��ת";
	gotoXY(MapWidth + 10, 20);
	cout << "W";
	gotoXY(MapWidth + 2, 21);
	cout << "���� A  S  D ����";
	gotoXY(MapWidth + 8, 22);
	cout << "����";
	setColor(��ɫ);//��Ҷ�
	for (int i = MapO2 + Mapwidth; i <= MapWidth + MapO2 + Mapwidth; i += 2) {
		gotoXY(i, 0);
		setMapValue(i, 0, 2);
		cout << "��";
		gotoXY(i, MapHeight);
		setMapValue(i, MapHeight, 2);
		cout << "��";
	}
	for (int i = 0; i <= MapHeight; i++) {
		gotoXY(MapO2 + Mapwidth, i);
		setMapValue(MapO2 + Mapwidth, i, 2);
		cout << "��";
		gotoXY(MapWidth + MapO2 + Mapwidth, i);
		setMapValue(MapWidth + MapO2 + Mapwidth, i, 2);
		cout << "��";
	}
	for (int i = MapO2; i <= MapO2 + Mapwidth; i += 2) {
		gotoXY(i, 0);
		setMapValue(i, 0, 2);
		cout << "��";
		gotoXY(i, MapHeight);
		setMapValue(i, MapHeight, 2);
		cout << "��";
	}
	for (int i = 0; i <= MapHeight; i++) {
		gotoXY(MapO2, i);
		setMapValue(MapO2, i, 2);
		cout << "��";
	}
	setColor(��ɫ);
	gotoXY(MapO2 + 8, 2);
	cout << "��һ��";
	gotoXY(MapO2 + 8, 8);
	cout << "��Ҷ�";
	gotoXY(MapO2 + 8, 10);
	cout << "��С��";
	setColor(��ɫ);
	gotoXY(MapO2 + 9, 15);
	cout << "�÷֣�";
	setColor(��ɫ);
	gotoXY(MapO2 + 9, 19);
	cout << "��ת";
	gotoXY(MapO2 + 10, 20);
	cout << "��";
	gotoXY(MapO2 + 2, 21);
	cout << "���� �� �� �� ����";
	gotoXY(MapO2 + 9, 22);
	cout << "����";
}
void Drawing::overScreen(int score1, int score2) {
	int win = 1;
	if (score2 > score1) win = 2;
	gotoXY(54, 7);
	if (win == 1)
		cout << "���һ��ʤ";
	else
		cout << "��Ҷ���ʤ";
	gotoXY(57, 9);
	cout << "�÷֣�";
	gotoXY(57, 10);
	if (win == 1) cout << score1;
	else cout << score2;
	gotoXY(53, 12);
	cout << "�����������......";
}
//����Ļ���
class Block
{
public:
	int x0, y0;//��ҵ�ͼ����
	fangge f[4];//�����ĸ���������
	int shape;//�������״
	int state;//֮ǰ�����ʾ����״̬����������ûɶ�ã��ĵĻ�������øĺܶ�
	void clearNextBlock(int wanjia);//��ʾ��һ������ǰ�������һ����ʾ��
	void drawNextBlock(int a,int wanjia);//��С��ͼ����һ������
	virtual void change() {}//ͬ�෽��֮���л���״������Ϊ�麯��
	void down();//�½�
	void moveLeft();//����
	void moveRight();//����
	bool checkLeft();//����ܷ�����
	bool checkRight();//����ܷ�����
	bool checkDown();//����ܷ��½�
	void show();//��ʾ����
	void hide();//��������
	bool checkOver();//�����Ϸ�Ƿ����
	
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
	//������
	case 1:
		setColor(��ɫ);
		gotoXY(OO + 8, 4);
		cout << "����";
		gotoXY(OO + 8, 5);
		cout << "����";
		break;
	//һ����
	case 2:
		setColor(��ɫ);
		gotoXY(OO + 6, 4);
		cout << "��������";
		break;
	//��T����
	case 3:
		setColor(��ɫ);
		gotoXY(OO + 8, 4);
		cout << "��";
		gotoXY(OO + 6, 5);
		cout << "������";
		break;
	//��L����
	case 4:
		setColor(��ɫ);
		gotoXY(OO + 6, 4);
		cout << "��";
		gotoXY(OO + 6, 5);
		cout << "������";
		break;
	//L����
	case 5:
		setColor(��ɫ);
		gotoXY(OO + 10, 4);
		cout << "��";
		gotoXY(OO + 6, 5);
		cout << "������";
		break;
	//��Z����
	case 6:
		setColor(��ɫ);
		gotoXY(OO + 8, 4);
		cout << "����";
		gotoXY(OO + 6, 5);
		cout << "����";
		break;
	//Z����
	case 7:
		setColor(��ɫ);
		gotoXY(OO + 6, 4);
		cout << "����";
		gotoXY(OO + 8, 5);
		cout << "����";
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
			setColor(��ɫ);
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
		cout << "��";
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
//ͨ��Block�����������ֻ�������
//������
class Block1 :public Block
{
public:
	Block1(int x0, int y0);
	void change(){}
};
Block1::Block1(int x0, int y0)
{
	setColor(��ɫ);
	shape = 0;
	state = 1;
	f[0] = { Map1Mid + x0,2 };
	f[1] = { Map1Mid + 2 + x0,2 };
	f[2] = { Map1Mid + x0,3 };
	f[3] = { Map1Mid + 2 + x0,3 };
	show();
	checkOver();
}
//һ����
class Block2 :public Block
{
public:
	Block2(int x0, int y0);
	void change();
};
Block2::Block2(int x0, int y0)
{
	setColor(��ɫ);
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
//��T����
class Block3 :public Block
{
public:
	Block3(int x0, int y0);
	void change();
};
Block3::Block3(int x0, int y0)
{
	setColor(��ɫ);
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
//��L����
Block4::Block4(int x0, int y0)
{
	setColor(��ɫ);
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
//L����
class Block5 :public Block
{
public:
	Block5(int x0, int y0);
	void change();
};
Block5::Block5(int x0, int y0)
{
	setColor(��ɫ);
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
//��Z����
class Block6 :public Block
{
public:
	Block6(int x0, int y0);
	void change();
};
Block6::Block6(int x0, int y0)
{
	setColor(��ɫ);
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
//Z����
class Block7 :public Block
{
public:
	Block7(int x0, int y0);
	void change();
};
Block7::Block7(int x0, int y0)
{
	setColor(��ɫ);
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
//�ڷ�����Ļ�������������������࣬�Ա�˫����Ϸ
class Player1 :public Block
{
private:
	int n, m;//�������������
	Block* b;//��Ϊ����ָ�룬�Ա����ָ���²����ķ���
	int Time;//˫����Ϸʱ����ʱ��Ŀ���
public:
	int score;//��¼�÷�
	Player1();//���캯��
	void readKey(Block *b);//���̶���
	int checkFull();//����Ƿ����У�������
	void Run();//��Ϸ���У���������
	void newShow(int i);//���л����������к�ˢ�»���
	void showScore();//�����仯ʱ��ˢ�·���
	void addLine();//����������
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
	if (_kbhit())//��������ֵ����
	{
		key = _getch();
		if (key == 'w')	b->change();//w�� ����
		if (key == 's')				//s�� ����
		{
			for (int i = 0; i < 3; i++) {
				if (b->checkDown()) b->down();
			}
		}
		if (key == 'a')				//a�� ����
		{
			if (b->checkLeft()) b->moveLeft();
		}
		if (key == 'd')				//d�� ����
		{
			if (b->checkRight()) b->moveRight();
		}
	}
}
int Player1::checkFull()
{
	int count = 0;//����������
	for (int i = MapHeight - 1; i > 3; i--) //�������϶�
	{
		int flag = 1;
		for (int j = x0 + 2; j < x0 + MapWidth-1; j += 2)//�������Ҷ�
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
					MapValue[j][k] = MapValue[j][k - 1];//����Ϸ��ͼֵ����һ��
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
	while (line1--) {//����line1��
		for (int j = x0 + 2; j < x0 + MapWidth - 1; j += 2)//����Ϸ��ͼֵ������һ��
		{
			for (int k = 4; k < MapHeight; k++) {
				MapValue[j][k] = MapValue[j][k + 1];
			}
		}
		for (int j = x0 + 2; j < x0 + MapWidth - 1; j += 2) {//�������һ��
			int n = getRandRange(0, 1);
			setMapValue(j, MapHeight - 1, n);
		}
		newShow(MapHeight - 1);
	}
}
void Player1::newShow(int ii)
{
	setColor(��ɫ);
	for (int i = ii; i > 3; i--) {
		for (int j = x0 + 2; j < x0 + MapWidth - 1; j += 2) {
			gotoXY(j, i);
			if (MapValue[j][i] == 1) cout << "��";
			else  cout << "  ";
		}
	}
}
void Player1::showScore() {
	setColor(��ɫ);
	gotoXY(MapWidth + 9, 16);
	cout << "        ";
	gotoXY(MapWidth + 9, 16);
	printf("%05d", score);
}
void Player1::Run()
{
	while (1)
	{
		//�ж��Ƿ����������
		if(line1!=0){
			addLine();
			line1 = 0;
		}
		if (Time > 150) { //���ʱ�䣬��˫���й�
			Time = 0;
			//����
			if (b->checkDown()) b->down();
			//��������
			else {
				//���У����ı���Ҷ���lineֵ����Ҷ�����������
				checkFull();
				//׼�������·��飬��������һ������
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
				//�������·���ʱ���Ƿ��Ѿ������϶�
				if (!(b->checkOver())) {
					score = -1;
					GameState = 0;
				}
			}

		}
		//���밴��
		readKey(b);
		//ֵԽС���밴�����������ٶ�Ҳ����
		//ͨ��Sleep��Time��ʹ�ã�run1��run2����ִ�У�ʵ��˫��
		Sleep(0.00001);
		Time++;
		break;
	}
}
//��Ҷ������һ������ͬ
class Player2 :public Block
{
private:
	int n, m;//�����
	Block* b;
	int Time;
public:
	int score;
	Player2();
	void readKey(Block* b);//���̶���
	int checkFull();//����Ƿ�����
	void Run();//��Ϸ����
	void newShow(int i);//���к�ˢ�»���
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
		//wsad�����
		if (key == 72)	b->change(); //���ϼ� ����
		if (key == 80)				//���¼� ����
		{
			for (int i = 0; i < 3; i++) {
				if (b->checkDown()) b->down();
			}
		}
		if (key == 75)				//����� ����
		{
			if (b->checkLeft()) b->moveLeft();
		}
		if (key == 77)					//������� ����
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
			//����
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
	setColor(��ɫ);
	for (int i = ii; i > 3; i--) {
		for (int j = x0 + 2; j < x0 + MapWidth - 1; j += 2) {
			gotoXY(j, i);
			if (MapValue[j][i] == 1) cout << "��";
			else  cout << "  ";
		}
	}
}
void Player2::showScore() {
	setColor(��ɫ);
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
//��Ϸ��
class Game
{
public:
	void RunGame();
};
void Game::RunGame()
{
	HideCursor();//���ع��
	Drawing Draw;
	Draw.welcome();
	system("cls");
	Draw.drawMap();
	Player1 player1;
	Player2 player2;
	//������Ϸ
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