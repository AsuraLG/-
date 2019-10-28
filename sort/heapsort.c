/*
 * 大顶堆排序，元素由小到大排列，属于非稳定排序，时间复杂度O(nlogn)，通常用于找topK的场景
 * arr：要排序的数组
 * s：数组的起始下标
 * e：数组的末尾下标
 */
void create_heap_max(int arr[], int s, int e)
{
	int i;
	int left;
	int right;
	int nextLeft;
	int nextRight;
	int len;

	len = e - s + 1;
	for(i = s + (len >> 1) - 1; i >= s; i--)
	{
		left = s + ((i - s) << 1) + 1;
		right = s + ((i - s) << 1) + 2;
		if(left <= e && arr[i] < arr[left])
		{
			swap(&arr[i], &arr[left]);
			nextLeft = s + ((left - s) << 1) + 1;
			nextRight = s + ((left - s) << 1) + 2;
			if((nextLeft <= e && arr[left] < arr[nextLeft]) ||
			   (nextRight <= e && arr[left] < arr[nextRight]))
				create_heap_max(arr, s, e);
		}
		if(right <= e && arr[i] < arr[right])
		{
			swap(&arr[i], &arr[right]);
			nextLeft = s + ((right - s) << 1) + 1;
			nextRight = s + ((right - s) << 1) + 2;
			if((nextLeft <= e && arr[right] < arr[nextLeft]) ||
			   (nextRight <= e && arr[right] < arr[nextRight]))
				create_heap_max(arr, s, e);
		}
	}
}

void heapsort_max1(int arr[], int s, int e)
{
	int i;

	/*
	 * 算法步骤：
	 * （1）将去除堆底元素之后的堆为大顶堆
	 * （2）将堆顶元素和堆底元素互换
	 * （3）重复（1）和（2），直到堆里只有一个元素
	 */
	i = e;
	while(i > s)
	{
		create_heap_max(arr, s, i);
		swap(&arr[s], &arr[i]);
		i--;
	}
}

void adjust_heap_max(int arr[], int s, int e, int root)
{
	int i;
	int max;
	int left;
	int right;

	i = root;
	max = i;
	while(1)
	{
		/* 确定节点i的左右儿子节点 */
		left = s + ((i - s) << 1) + 1;
		right = s + ((i - s) << 1) + 2;

		/* 找出节点i，节点left和节点right中最大的，其下标为max */
		if(left <= e && arr[i] < arr[left])
			max = left;
		if(right <= e && arr[max] < arr[right])
			max = right;

		/* 如果max == i说明堆调整完成，否则则将最大节点max和节点i交换，并通过i = max来检查交换后的节点i是否需要继续调整 */
		if(max == i)
			break;
		swap(&arr[i], &arr[max]);
		i = max;
	}
}

void heapsort_max2(int arr[], int s, int e)
{
	int i;
	int len;

	/*
	 * 算法步骤：
	 * （1）先将数组构造成大顶堆，通过自底向顶调整每个非叶子节点的元素位置实现
	 * （2）将堆顶元素和堆底元素互换
	 * （3）调整新堆顶元素的位置，形成新的大顶堆
	 * （3）重复（1）和（2），直到堆里只有一个元素
	 */
	len = e - s + 1;
    for(i = s + (len >> 1) - 1; i >= s; i--)
		adjust_heap_max(arr, s, e, i);

	i = e;
	while(i > s)
	{
		swap(&arr[s], &arr[i]);
		i--;
		adjust_heap_max(arr, s, i, s);
	}
}
