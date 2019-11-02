#include <stdlib.h>

/* 交换p1和p2所指向的值 */
void swap(int *p1, int *p2)
{
	int tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

/* 生成在区间[0, range]内的随机数*/
int getRand(int range)
{
	int i;
	int tmp;
	int res;

	do
	{
		res = 0;
		i = 0;
		tmp = range;

		do
		{
			tmp /= 10;
			i++;
		}
		while(tmp > 0);

		while(i > 0)
		{
			res = (res << 3) + (res << 1) + rand() % 10;
			i--;
		}
	}
	while(res > range);

	return res;
}

int quickScanf()
{
	char c;
	int num = 0;

	do
	{
		c = getchar();
	}
	while(c < '0' || c > '9');

	do
	{
		num = (num << 3) + (num << 1) + c - '0';
		c = getchar();
	}
	while(c >= '0' && c <= '9');

	return num;
}

void quickPrintf(int n)
{
	int tmp = n / 10;
	if(tmp) quickPrintf(tmp);
	putchar(n % 10 + '0');
}