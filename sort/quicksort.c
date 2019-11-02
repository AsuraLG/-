#include <stdlib.h>

/* 取数组里三个数的中位数，返回其索引 */
int findMid(int arr[], int i, int j, int k)
{
	if(arr[i] <= arr[j] && arr[i] <= arr[k])
		return (arr[j] <= arr[k])? j: k;
	if(arr[j] <= arr[i] && arr[j] <= arr[k])
		return (arr[i] <= arr[k])? i: k;
	return (arr[i] <= arr[j])? i: j;
}

int partition_oneway(int arr[], int s, int e)
{
	int i;
	int j;

	/* 随机选择哨兵，避免原始数组基本有序导致复杂度上升 */
	i = rand() % (e - s + 1) + s;
	swap(&arr[i], &arr[s]);

	/*
	 * 该循环用于将本轮排序的数组中哨兵key最终要插入的位置定出来，同时使其左边全小于它，右边全大于等于它
	 * 算法步骤：
	 * （1）从第二个元素开始依次寻找，每当找到一个大于等于key的数，则其肯定在右边，便将右边的arr[j]与其对换
	 * （2）对换后，arr[j] >= key，因此该位置肯定不会动，j更新到j-1
	 * （3）当某一轮i和j相等时，说明上一轮：
	 * 		1.要么执行的是i++，即表示这一轮的arr[i - 1] < key，且arr[i + 1] >= key
	 * 		2.要么执行的是j--，即表示上一轮arr[i]和其前面arr[j]对换了，这一轮的arr[i - 1] < key，且arr[i + 1] >= key
	 * （4）因此若arr[i] >= key，则i自减，使其指向小于哨兵的位置最靠右的值
	 * （5）若arr[i] < key，则此时i就指向小于哨兵的位置最靠右的值
	 * （6）最后将哨兵和下标i指向的值互换位置即可
	 */
	i = s + 1;
	j = e;
	while (i < j)
	{
		if (arr[i] >= arr[s])
		{
			swap(&arr[i], &arr[j]);
			j--;
		}
		else
		{
			i++;
		}
	}
	if (arr[i] >= arr[s]) i--;

	swap(&arr[s], &arr[i]);

	return i;
}

/*
 * 以数组随机位置的数为哨兵的单路快速排序的非递归实现，双路和三路类似
 * arr：要排序的数组
 * s：数组的起始下标
 * e：数组的末尾下标
 */
void quicksort_oneway_stack(int arr[], int s, int e)
{
	int i;
	int left;
	int right;
	int index;
	int stack[1000];

	stack[0] = s;
	stack[1] = e;
    index = 1;
    while(index != -1)
	{
		right = stack[index--];
		left = stack[index--];

		i = partition_oneway(arr, left, right);

		if(i - 1 > left)
		{
			stack[++index] = left;
			stack[++index] = i - 1;
		}
		if(i + 1 < right)
		{
			stack[++index] = i + 1;
			stack[++index] = right;
		}
	}
}

/*
 * 以数组随机位置的数为哨兵的单路快速排序，时间复杂度O(n2)，属于非稳定排序
 * arr：要排序的数组
 * s：数组的起始下标
 * e：数组的末尾下标
 */
void quicksort_oneway(int arr[], int s, int e)
{
	int i;

	if (s >= e) return;

	i = partition_oneway(arr, s, e);
	quicksort_oneway(arr, s, i - 1);
	quicksort_oneway(arr, i + 1, e);
}

int partition_twoway(int arr[], int s, int e)
{
	int i;
	int j;

	/* 随机选择哨兵，避免原始数组基本有序导致复杂度上升 */
	i = rand() % (e - s + 1) + s;
	swap(&arr[i], &arr[s]);

	/*
	 * 该循环用于将本轮排序的数组中哨兵key最终要插入的位置定出来，同时使其左边全小于等于它，右边全大于等于它，保持两边长度基本平衡
	 * 算法步骤：
	 * （1）从第二个元素开始依次寻找，找到第一个大于等于key的下标i
	 * （2）从最后一个元素开始依次寻找，找到第一个小于等于key的下标j
	 * （3）此时要么i小于j，要么i大于j，即i = j + 1
	 * （4）当i小于j时，说明两个元素的位置反了，交换两个元素，然后移动两个下标，开始下一轮
	 * （5）当i = j + 1时，说明数组遍历完成，退出循环
	 * 		1.要么执行的是i++，说明i == j时，arr[i] <= key，arr[j + 1] >= key，则此时arr[j] <= key，arr[i] >= key
	 * 		2.要么执行的是j--，说明i == j时，arr[i] > key，arr[i - 1] <= key，则此时arr[j] <= key，arr[i] >= key
	 * （6）因此最后将哨兵和下标j指向的值互换位置即可
	 */
	i = s + 1;
	j = e;
	while(1)
	{
		for(; i <= j && arr[i] <= arr[s]; i++);
		for(; j >= i && arr[j] >= arr[s]; j--);
		if(i > j) break;
		swap(&arr[i], &arr[j]);
		i++;
		j--;
	}

	swap(&arr[s], &arr[j]);

	return j;
}

/*
 * 以数组随机位置的数为哨兵的双路快速排序
 * arr：要排序的数组
 * s：数组的起始下标
 * e：数组的末尾下标
 */
void quicksort_twoway(int arr[], int s, int e)
{
	int i;

	if (s >= e) return;

	i = partition_twoway(arr, s, e);
	quicksort_twoway(arr, s, i - 1);
	quicksort_twoway(arr, i + 1, e);
}

void partition_threeway(int arr[], int s, int e, int *left, int *right)
{
	int k;
	int i;
	int j;

	/* 随机选择哨兵，避免原始数组基本有序导致复杂度上升 */
	i = rand() % (e - s + 1) + s;
	swap(&arr[i], &arr[s]);

	/*
	 * 该循环用于将本轮排序的数组中与哨兵key相等的元素的左右边界定出来，同时使其左边全小于key，右边全大于key
	 * 算法步骤：
	 * （1）当arr[k] < key时，交换arr[k]和arr[i + 1]，同时i自增，始终指向小于key的最右边的数，由于arr[i + 1]永远小于等于key，因此k直接自增
	 * （2）当arr[k] > key时，交换arr[k]和arr[j - 1]，同时j自减，始终指向大于key的最左边的数，k保持不动，因为arr[j - 1]仍然需要进一步判断
	 * （3）当arr[k] = key时，k自增，判断下一个元素是否需要交换
	 * （4）当k = j时，说明arr[k]到arr[e]均大于key，则循环结束
	 * （5）此时将arr[i]和key互换，此时arr[i]就是第一个等于key的元素
	 * （6）因此最后只需要对小于key的arr[s]到arr[i - 1]，和大于key的arr[j]到arr[e]进行排序
	 */
	i = s;
	j = e + 1;
	k = s + 1;
	while(k < j)
	{
		if(arr[k] < arr[s])
		{
			swap(&arr[k], &arr[i + 1]);
			k++;
			i++;
		}
		else if(arr[k] > arr[s])
		{
			swap(&arr[k], &arr[j - 1]);
			j--;
		}
		else
		{
			k++;
		}
	}

	swap(&arr[s], &arr[i]);
	*left = i - 1;
	*right = j;
}

/*
 * 以数组随机位置的数为哨兵的三路快速排序
 * arr：要排序的数组
 * s：数组的起始下标
 * e：数组的末尾下标
 */
void quicksort_threeway(int arr[], int s, int e)
{
	int left;
	int right;

	if (s >= e) return;

	partition_threeway(arr, s, e, &left, &right);

	// 此时，与哨兵相等的元素范围为left + 1到right - 1
	quicksort_threeway(arr, s, left);
	quicksort_threeway(arr, right, e);
}

/*
 * 以数组随机位置的数为哨兵的三路快速排序，模拟尾递归形式，并不能达到尾递归的优化效果
 * arr：要排序的数组
 * s：数组的起始下标
 * e：数组的末尾下标
 */
 void quicksort_threeway_tail(int arr[], int s, int e)
{
	int i;
	int j;
	int k;
	int left;
	int right;

	i = s;
	j = e;
	while(i < j)
	{
		// 此时，与哨兵相等的元素范围为left + 1到right - 1
		partition_threeway(arr, i, j, &left, &right);
		k = i;
		i = right;
		quicksort_threeway(arr, k, left);
	}
}