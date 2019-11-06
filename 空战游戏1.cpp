#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define High 25  // ��Ϸ����ߴ�
#define Width 50

#define EnemyNum 5  //�л���Ŀ

// ȫ�ֱ���
int canvas[High][Width]={0}; // ��ά�����¼��Ϸ�����еĶ�ӦԪ��
                             //0 ����ո�1����ɻ�,2����ӵ���3����л�
int position_x,position_y;//�ɻ�����λ��
int enemy_x[EnemyNum],enemy_y[EnemyNum];      // �л�����λ��
int score;				  //�÷�
int BulletWidth;		  //�ӵ����

void gotoxy(int x,int y) //����ƶ���(x,y)λ��
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}

void startup() // ���ݳ�ʼ��
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

void show()  // ��ʾ����
{
	gotoxy(0,0);  // ����ƶ���ԭ��λ�ã������ػ�����
	int i,j;
	for (i=0;i<=High-1;i++)
	{
		for (j=0;j<=Width-1;j++)
		{
			if (canvas[i][j]==1)
				printf("*");  //   ����ɻ�*
			else if (canvas[i][j]==2)
				printf("|");  //   ����ӵ�|
			else if (canvas[i][j]==3)
				printf("@");  //   ����л�@
			else
				printf(" ");  //   ����ո�			
		}
		printf("\n");
	}
	printf( "�÷֣�%d",score);
}	

void updateWithoutInput()  // ���û������޹صĸ���
{	
	int i,j,k;  //����
	for (i=0;i<=High-1;i++)
	{
		for (j=0;j<=Width-1;j++)
		{
			if (canvas[i][j]==2)  
			{
				for (k=0;k<EnemyNum;k++)
				{
					if (i==enemy_x[k] && j==enemy_y[k]) //���ел�
					{
						canvas[enemy_x[k]][enemy_y[k]]=0;
						enemy_x[k]=0;
						enemy_y[k] = rand() % Width ;
						canvas[enemy_x[k]][enemy_y[k]]=3;
					
						score++;
					}
				}
				

				//���ӵ��Զ������ƶ�
				canvas[i][j]=0;
				if (i>0)
					canvas[i-1][j]=2;
			}
		}
	}
	
	for (k=0;k<EnemyNum;k++)
	{
		if (enemy_x[k]>High) //�л��ܳ��±߽�
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
		//	�л��Զ�����
		for (k=0;k<EnemyNum;k++)
		{
			canvas[enemy_x[k]][enemy_y[k]] = 0;
			enemy_x[k]++;
			canvas[enemy_x[k]][enemy_y[k]] = 3;
		}
		
		speed = 0;
	}
}

void updateWithInput()  // ���û������йصĸ���
{
	char input;

	if (kbhit())//����ʱ
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
	startup();  // ���ݳ�ʼ��	
	while (1) //  ��Ϸѭ��ִ��
	{
		show();  // ��ʾ����
		updateWithoutInput();  // ���û������޹صĸ���
		updateWithInput();  // ���û������йصĸ���
	}
	return 0;
}
