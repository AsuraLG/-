/*
 * 直接插入排序，适用于数组长度在50以下的时候，比快速排序会快一些，属于稳定排序，时间复杂度O(n2)
 * arr：要排序的数组
 * s：数组的起始下标
 * e：数组的末尾下标
 */
void insertsort_straight(int arr[], int s, int e)
{
	int i;
	int j;
	int tmp;

	for (i = s + 1; i <= e; i++)
	{
		if (arr[i] < arr[i - 1])
		{
			tmp = arr[i];
			for (j = i; j > s && arr[j - 1] > tmp; j--)
				arr[j] = arr[j - 1];
			arr[j] = tmp;
		}
	}
}

/*
 * 希尔排序，属于非稳定排序，平均时间复杂度O(n^1.5)
 * arr：要排序的数组
 * s：数组的起始下标
 * e：数组的末尾下标
 */
void insertsort_shell(int arr[], int s, int e)
{
	int gap;
	int i;
	int j;
	int tmp;

	gap = (unsigned int)(e - s + 1) >> 1;
	while(gap >= 1)
	{
		for(i = s + gap; i <= e; i++)
		{
			if (arr[i] < arr[i - gap])
			{
				tmp = arr[i];
				for (j = i; j >= s + gap && arr[j - gap] > tmp; j -= gap)
					arr[j] = arr[j - gap];
				arr[j] = tmp;
			}
		}
		gap >>= 1;
	}
}