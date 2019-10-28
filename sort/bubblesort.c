/*
 * 改进的冒泡排序，属于稳定排序，时间复杂度O(n^2)
 * arr：要排序的数组
 * s：数组的起始下标
 * e：数组的末尾下标
 */
void bubblesort(int arr[], int s, int e)
{
	int i;
	int j;
	int flag;

	j = e - 1;
	do
	{
		flag = 0;
		for(i = s; i <= j; i++)
		{
			if(arr[i] > arr[i + 1])
			{
				swap(&arr[i], &arr[i + 1]);
				flag = 1;
			}
		}
		j--;
	}
	while(flag); //某一轮没有发生任何互换则表示全部数据都有序
}
