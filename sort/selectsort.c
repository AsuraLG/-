/*
 * 选择排序，属于非稳定排序，时间复杂度O(n2)
 * arr：要排序的数组
 * s：数组的起始下标
 * e：数组的末尾下标
 */
void selectsort(int arr[], int s, int e)
{
	int i;
	int j;
	int tmp;

	for(i = s; i <= e - 1;i++)
	{
		tmp = i;
		for(j = i + 1; j <= e; j++)
		{
			if(arr[tmp] > arr[j]) tmp = j;
		}
		if (tmp != i) swap(&arr[tmp], &arr[i]);
	}
}
