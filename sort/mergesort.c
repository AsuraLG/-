/*
 * 归并排序，稳定排序，时间复杂度O(nlogn)，传统方法
 * arr：要排序的数组
 * s：数组的起始下标
 * e：数组的末尾下标
 */
void mergesort1(int arr[], int s, int e)
{
	int mid;
	int i;
	int j;
	int	k;
	int tmp[e - s + 1];

	if (s == e) return;

	mid = (unsigned int)(s + e) >> 1;

	mergesort1(arr, s, mid);
	mergesort1(arr, mid + 1, e);

	/* 将归并好的两个部分合并 */
	for(i = s, j = mid + 1, k = 0; i <= mid && j <= e; k++)
	{
		if(arr[i] <= arr[j])
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

/*
 * 归并排序，稳定排序，时间复杂度O(nlogn)，减少空间和时间消耗的方法，由非计算机专业人士友好提供
 * arr：要排序的数组
 * s：数组的起始下标
 * e：数组的末尾下标
 */
void mergesort2(int arr[], int s, int e)
{
	int i;
	int j;
	int	k;
	int mid = (unsigned int)(s + e) >> 1;
	int tmp[mid - s + 1];

	if (s == e) return;

	mergesort2(arr, s, mid);
	mergesort2(arr, mid + 1, e);

	/* 将归并好的两个部分合并 */
	for(i = 0; i < mid - s + 1; i++) tmp[i] = arr[s + i];
	for(i = 0, j = mid + 1, k = s; i <= mid - s && j <= e; k++)
	{
		if(tmp[i] <= arr[j])
			arr[k] = tmp[i++];
		else
			arr[k] = arr[j++];
	}
	for(; i <= mid - s; i++, k++)
		arr[k] = tmp[i];
}