#include<iostream>
#include <queue>
#include<ctime>
#include<conio.h>
#include<Windows.h>
#include<stdlib.h>
#include "time.h"
using namespace std;
int map[22][22] = { 0 };
char mapbuffer[22 * 22 - 1 + 22];
enum Orient { Up, Down, Left, Right, None }orient;

struct xy 
{
	int x;
	int y;
};
queue<xy> snake;	//snake定义
void GameInit();
void GameProcessing();
void GiftGiven();
void MapRefresh();

void GameInit() {
	int i , j ;
	for (i = 1; i < 21; i++)
	{
		for (j = 1; j < 21; j++) map[i][j] = 0;
	}

	for (i = 0; i < 22; i++)
	{
		map[i][0] = 1;
		map[i][21] = 1;
		map[0][i] = 1;
		map[21][i] = 1;
	}					//地图的初始化

	srand(time(0));
	int xr = rand()%20+1;
	int yr = rand()%20+1;
	snake.push(xy{ xr,yr });//蛇的初始位置
	map[yr][xr]=1;
	orient = None;
	GiftGiven();
	MapRefresh();
 }
void GameProcessing() //返回值用于判断游戏进行状态
{
	if(_kbhit())
	{
		if (_getch()) {
			switch (_getch()) {
			case 72:orient = Up; break;
			case 80:orient = Down; break;
			case 75:orient = Left; break;
			case 77:orient = Right; break;
			default:orient = orient; break;
			}
		}
		int xnew = snake.back().x, ynew = snake.back().y;
		switch (orient) {
		case Up: ynew = ynew - 1; break;
		case Down: ynew = ynew + 1; break;
		case Left:xnew = xnew - 1; break;
		case Right:xnew = xnew + 1; break;
		case None:xnew = xnew; ynew = ynew; break;
		}
		snake.push(xy{ xnew,ynew });
		if (map[ynew][xnew] == 0) {
			map[ynew][xnew] = 1;
			map[snake.front().y][snake.front().x] = 0;
			snake.pop();
			MapRefresh();
		}
		else if (map[ynew][xnew] == 2) {
			map[ynew][xnew] = 1;

			GiftGiven();
			MapRefresh();
		}
		//else if (map[ynew][xnew] == 1) {
		//	cout << "failed";
		//	system("pause");
		//}

	}
}

void GiftGiven() 
{
	int xr, yr;
	srand(time((time_t)0));
	do {
		xr = rand() % 20 + 1;
		yr = rand() % 20 + 1;
	} while (map[xr][yr]);
	map[xr][yr] = 2;
}

void MapRefresh() 
{
	system("cls");
	int i, j;
	int k = 0;
	for (i = 0; i < 22; i++)
	{
		for (j = 0; j < 22; j++) 
		{
			switch (map[i][j])
			{
			case 0:mapbuffer[k++] = ' '; break;
			case 1:mapbuffer[k++] = '*'; break;
			case 2:mapbuffer[k++] = '$'; break;
			}
		}
		mapbuffer[k++] = '\n';
	}
	cout << mapbuffer;
}
int main()
{
	GameInit();
	Sleep(1 * 1000);
	while (1) {
		clock_t timebegan = clock();
		do {} while (clock() - timebegan < 1000);
		GameProcessing();
	}
}