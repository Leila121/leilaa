#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define High 20  // 游戏画面尺寸
#define Width 30

// 全局变量
int moveDirection;
int canvas[High][Width] = { 0 }; // 二维数组记录游戏画面中的对应元素
							 //0 输出空格，-1输出边框#,1输出蛇头@，>1输出蛇身*


void gotoxy(int x, int y) //光标移动到(x,y)位置
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void moveSnakeByDirection ()
{
	int i,j;
	for (i=0;i<High;i++)
	{
		for (j=0;j<Width;j++)
		{
			if (canvas[i][j]>0)
				canvas[i][j]++;
		}
	}
	int oldTail_i,oldTail_j,oldHead_i,oldHead_j;
	int max =0;

	for (i=1;i<High-1;i++)
	{
		for ( j=1;j<Width-1;j++)
		{
			if(canvas[i][j]>0)
			{
				if(max<canvas[i][j])
				{
					max=canvas[i][j];
					oldTail_i=i;
					oldTail_j=j;
				}
				if(canvas[i][j]==2)
				{
					oldTail_i=i;
					oldTail_j=j;
				}
			}
		}
	}
//
	canvas[oldTail_i][oldTail_j]=0;
	if (moveDirection==1)//向上移动
		canvas[oldHead_i-1][oldHead_j]=1;
	if (moveDirection==2)//向下移动
		canvas[oldHead_i+1][oldHead_j]=1;
	if (moveDirection==3)//向左移动
		canvas[oldHead_i][oldHead_j-1]=1;
	if (moveDirection==4)//向右移动
		canvas[oldHead_i][oldHead_j+1]=1;
}


void startup() // 数据初始化
{
	//边框初始化
	int i, j;

	for (i = 0; i < High; i++)
	{
		canvas[i][0] = -1;
		canvas[i][Width - 1] = -1;
	}
	for (j = 0; j < Width; j++)
	{
		canvas[0][j] = -1;
		canvas[High - 1][j] = -1;
	}

	//初始化蛇头
	canvas[High / 2][Width / 2] = 1;

	//初始化蛇身
	for (i = 1; i <= 4; i++)
		canvas[High / 2][Width / 2-i] = i + 1;

	//初始小蛇向右移动
	moveDirection=4;
}

void show()  // 显示画面
{
	gotoxy(0, 0);  // 光标移动到原点位置，以下重画清屏

	int i, j;

	for (i = 0; i <= High; i++)
	{
		for (j = 0; j <= Width; j++)
		{
			if (canvas[i][j] == 0)
				printf(" ");  //   输出空格
			else if (canvas[i][j] == -1)
				printf("#");  //   输出边框#
			else if (canvas[i][j] == 1)
				printf("@");  //   输出蛇头@
			else if (canvas[i][j] > 1)
				printf("*");  //   输出蛇身*
		}
		printf("\n");
	}
}

void updateWithoutInput()  // 与用户输入无关的更新
{
	moveSnakeByDirection();
}

void updateWithInput()  // 与用户输入有关的更新
{

}

int main()
{
	startup();  // 数据初始化	
	while (1) //  游戏循环执行
	{
		show();  // 显示画面
		updateWithoutInput();  // 与用户输入无关的更新
		updateWithInput();  // 与用户输入有关的更新
	}
	return 0;
}
