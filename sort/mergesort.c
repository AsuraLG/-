/*
 * 归并排序，稳定排序，时间复杂度O(nlogn)
 * arr：要排序的数组
 * s：数组的起始下标
 * e：数组的末尾下标
 */
void mergesort(int arr[], int s, int e)
{
	int mid;
	int i;
	int j;
	int	k;
	int tmp[e - s + 1];

	if (s == e) return;

	mid = (unsigned int)(s + e) >> 1;

	mergesort(arr, s, mid);
	mergesort(arr, mid + 1, e);

	/* 将归并好的两个部分合并 */
	for(i = s, j = mid + 1, k = 0; i <= mid && j <= e; k++)
	{
		if(arr[i] < arr[j])
			tmp[k] = arr[i++];
		else
			tmp[k] = arr[j++];
	}
	for(; i <= mid; i++, k++)
		tmp[k] = arr[i];
	for(; j <= e; j++, k++)
		tmp[k] = arr[j];
	for(k = 0; k <= e - s; k++)
		arr[s + k] = tmp[k];
}
