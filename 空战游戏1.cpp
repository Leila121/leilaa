#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define High 25  // 游戏画面尺寸
#define Width 50

#define EnemyNum 5  //敌机数目

// 全局变量
int canvas[High][Width]={0}; // 二维数组记录游戏画面中的对应元素
                             //0 输出空格，1输出飞机,2输出子弹，3输出敌机
int position_x,position_y;//飞机坐标位置
int enemy_x[EnemyNum],enemy_y[EnemyNum];      // 敌机坐标位置
int score;				  //得分
int BulletWidth;		  //子弹宽度

void gotoxy(int x,int y) //光标移动到(x,y)位置
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}

void startup() // 数据初始化
{
	position_x=High/2;
	position_y=Width/2;
	canvas[position_x][position_y]=1;
	

	int k;
	for (k=0;k<EnemyNum;k++)
	{
		enemy_x[k]=rand() % 3;
		enemy_y[k]=rand() % Width;
		canvas[enemy_x[k]][enemy_y[k]]=3;
	}

	BulletWidth=5;

	score=0;
}

void show()  // 显示画面
{
	gotoxy(0,0);  // 光标移动到原点位置，以下重画清屏
	int i,j;
	for (i=0;i<=High-1;i++)
	{
		for (j=0;j<=Width-1;j++)
		{
			if (canvas[i][j]==1)
				printf("*");  //   输出飞机*
			else if (canvas[i][j]==2)
				printf("|");  //   输出子弹|
			else if (canvas[i][j]==3)
				printf("@");  //   输出敌机@
			else
				printf(" ");  //   输出空格			
		}
		printf("\n");
	}
	printf( "得分：%d",score);
}	

void updateWithoutInput()  // 与用户输入无关的更新
{	
	int i,j,k;  //遍历
	for (i=0;i<=High-1;i++)
	{
		for (j=0;j<=Width-1;j++)
		{
			if (canvas[i][j]==2)  
			{
				for (k=0;k<EnemyNum;k++)
				{
					if (i==enemy_x[k] && j==enemy_y[k]) //击中敌机
					{
						canvas[enemy_x[k]][enemy_y[k]]=0;
						enemy_x[k]=0;
						enemy_y[k] = rand() % Width ;
						canvas[enemy_x[k]][enemy_y[k]]=3;
					
						score++;
					}
				}
				

				//让子弹自动向上移动
				canvas[i][j]=0;
				if (i>0)
					canvas[i-1][j]=2;
			}
		}
	}
	
	for (k=0;k<EnemyNum;k++)
	{
		if (enemy_x[k]>High) //敌机跑出下边界
		{
			canvas[enemy_x[k]][enemy_y[k]]=0;
			enemy_x[k]=0;
			enemy_y[k] = rand() % Width ;
			canvas[enemy_x[k]][enemy_y[k]]=3;

			score--;
		}
	}

	

	static int speed = 10;
	if (speed < 10)
		speed++;
	if( speed == 10)
	{
		//	敌机自动下落
		for (k=0;k<EnemyNum;k++)
		{
			canvas[enemy_x[k]][enemy_y[k]] = 0;
			enemy_x[k]++;
			canvas[enemy_x[k]][enemy_y[k]] = 3;
		}
		
		speed = 0;
	}
}

void updateWithInput()  // 与用户输入有关的更新
{
	char input;

	if (kbhit())//按键时
	{
		input = getch();
		if (input == 'a')
		{
			canvas[position_x][position_y]=0;
			position_y--;
			canvas[position_x][position_y]=1;
		}
		if (input == 'd')
		{
			canvas[position_x][position_y]=0;
			position_y++;
			canvas[position_x][position_y]=1;
		}
		if (input == 'w')
		{
			canvas[position_x][position_y]=0;
			position_x--;
			canvas[position_x][position_y]=1;
		}
		if (input == 's')
		{
			canvas[position_x][position_y]=0;
			position_x++;
			canvas[position_x][position_y]=1;
		}
		if (input == ' ')
		{
			int left,right;
			left=position_y-BulletWidth;
			if (left<0)
				left=0;
			right=position_y+BulletWidth;
			if (right>Width-1)
				right=Width-1;

			int x;
			for (x=left;x<=right;x++)

			canvas[position_x-1][x]=2;
		}
	}
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
