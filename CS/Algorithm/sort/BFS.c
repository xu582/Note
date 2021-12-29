#include<stdio.h>
#include<iostream>

struct note
{
	int x;
	int y;
};

char a[20][21];	//用来存储地图

/*在（i，j）位置时消灭的气球*/
int getnum(int i, int j)
{
	int sum, x, y;
	sum = 0;
	
	//向上统计消灭的气球
	x = i; y = j;
	while (a[x][y] != '#')	//判断该点是不是强
	{
		//如果当前点是气球，则开始计数
		if (a[x][y] == 'G')
			sum++;
		x--;
	}

	//向下统计消灭的气球
	x = i; y = j;
	while (a[x][y] != '#')	//判断该点是不是强
	{
		//如果当前点是气球，则开始计数
		if (a[x][y] == 'G')
			sum++;
		x++;
	}

	//向左统计消灭的气球
	x = i; y = j;
	while (a[x][y] != '#')	//判断该点是不是强
	{
		//如果当前点是气球，则开始计数
		if (a[x][y] == 'G')
			sum++;
		y--;
	}

	//向右统计消灭的气球
	x = i; y = j;
	while (a[x][y] != '#')	//判断该点是不是强
	{
		//如果当前点是气球，则开始计数
		if (a[x][y] == 'G')
			sum++;
		y++;
	}

	return sum;
}

int main()
{
	struct note que[401];
	int head, tail;
	int book[20][20] = { 0 };

	int i, k, sum, max = 0, mx, my, n, m, startx, starty, tx, ty;

	//定义一个用于先一步方向的数组
	int next[4][2] = {
		{0,1},
		{1,0},
		{0,-1},
		{1,0},
	};

	scanf("%d %d %d %d", &n, &m, &startx, &starty);

	for (i = 0; i <= n - 1; i++)
		scanf("%s", a[i]);

	//队列初始化
	head = 1;
	tail = 1;

	//往队列插入小人的起始坐标
	que[tail].x = startx;
	que[tail].y = starty;
	tail++;
	book[startx][starty] = 1;
	max = getnum(startx, starty);
	mx = startx;
	my = starty;

	//当队列不为空的时候循环
	while (head < tail)
	{
		//枚举4个方向
		for (k = 0; k <= 3; k++)
		{
			//尝试走的下一个点的坐标
			tx = que[head].x + next[k][0];
			tx = que[head].y + next[k][1];
		

			//判断是否越界
			if (tx < 0 || tx > n - 1 || ty < 0 || ty > m - 1)
			{
				continue;
			}

			//判断是否为平地或者曾经走过
			if (a[tx][ty] == '.' && book[tx][ty] == 0)
			{
				//每个点只入队一次，所以需要标记这个点已经走过
				book[tx][ty] = 1;
				//插入新扩展的点到队列
				que[tail].x = tx;
				que[tail].y = ty;
				tail++;

				//统计新的点可以消灭气球的数量
				sum = getnum(tx, ty);
				//更新max的值
				if (sum > max)
				{
					max = sum;
					mx = tx;
					my = ty;
				}
			}
		}
		head++;
	}
	printf("将炸弹放置在(%d,%d)处，可以消灭%d个气球\n", mx, my, max);
	getchar(); 
	getchar();
	return 0;
}
