/*
 * 基数排序，属于稳定排序，平均复杂度O(d(r + n))，最坏复杂度O(d(rd + n))，最好复杂度O(rd + n)
 * 其中d为最大数的位数，r为每一位的取值范围宽度，一般是0到9，即r为10
 * arr：要排序的数组
 * s：数组的起始下标
 * e：数组的末尾下标
 */

int get_maxn_d(int arr[], int s, int e)
{
	int max;
	int i;

	max = arr[s];
	for(i = s + 1; i <= e; i++)
		if(max < arr[i]) max = arr[i];

	i = 0;
	do
	{
		max = max / 10;
		i++;
	}
	while(max > 0);

	return i;
}

int get_n_pos(int n, int pos)
{
	int i = 0;

	while(i < pos)
	{
		n /= 10;
		i++;
	}

    return n % 10;
}

void radixsort(int arr[], int s, int e)
{
	int count[10];
	int buckets[e - s + 1];
	int i;
	int j;
	int k;
	int d;

	/*
	 * 算法步骤：
	 * （1）先找出数组中最大的数，确定位数d
	 * （2）按照从低位到高位的顺序逐轮排列数组，d轮过后数组排序完成
	 * 		1.重置count数组，count[i]表示当前位的值为i的桶内的元素个数
	 * 		2.遍历数组，确定每个桶内的元素个数
	 * 		3.更新count数组，count[i]表示当前位的值<=i的元素个数
	 * 		4.遍历数组，将当前位的值为k的元素从后往前依次放入桶中
	 * 		5.此时桶中元素已经按照当前位的值排列好，用其覆盖数组即可
	 */
	d = get_maxn_d(arr, s, e);
	for(i = 0; i < d; i++)
	{
		for(j = 0; j < 10; j++) count[j] = 0;
		for(j = s; j <= e; j++)
		{
			k = get_n_pos(arr[j], i);
			count[k]++;
		}
		for(j = 1; j < 10; j++) count[j] += count[j - 1];
		for(j = e; j >= s; j--)
		{
			k = get_n_pos(arr[j], i);
			buckets[count[k] - 1] = arr[j];
			count[k] -= 1;
		}
		for(j = s; j <= e; j++) arr[j] = buckets[j];
	}
}