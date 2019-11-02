/*
 * 递归二分查找
 * arr：要查找的数组
 * s：数组的起始下标
 * e：数组的末尾下标
 * k：要查找的数
 * 返回值：要查找的数在数组中的下标，没有则返回-1
 */
int binarysearch1(int arr[], int s, int e, int k)
{
	int mid;

	if (s > e) return -1;

	mid = (unsigned int)(s + e) >> 1;

	if (arr[mid] == k) return mid;
	if (arr[mid] > k)
		return binarysearch1(arr, s, mid - 1, k);
	else
		return binarysearch1(arr, mid + 1, e, k);
}

/*
 * 循环二分查找
 * arr：要查找的数组
 * s：数组的起始下标
 * e：数组的末尾下标
 * k：要查找的数
 * 返回值：要查找的数在数组中的下标，没有则返回-1
 */
int binarysearch2(int arr[], int s, int e, int k)
{
	int mid;
	int i;
	int j;

	/*
	 * 使用i <= j作为判断条件，循环内会对最终剩下的一个数进行判断
	 * 适用于某些场景
	 */
	i = s;
	j = e;
	while (i <= j)
	{
		mid = (unsigned int)(s + e) >> 1;
		if (arr[mid] == k) return mid;
		if (arr[mid] > k)
			j = mid - 1;
		else
			i = mid + 1;
	}

	return -1;
}

/*
 * 循环二分查找
 * arr：要查找的数组
 * s：数组的起始下标
 * e：数组的末尾下标
 * k：要查找的数
 * 返回值：要查找的数在数组中的下标，没有则返回-1
 */
int binarysearch3(int arr[], int s, int e, int k)
{
	int mid;
	int i;
	int j;

	/*
	 * 使用i < j作为判断条件，循环内不会对最终剩下的一个数进行判断
	 * 必须是i = mid + 1而不是i = mid，后者会导致i + 1 = j时可能的死循环
	 * 而j = mid或者j = mid - 1均可，识情况而定
	 * 适用于某些场景
	 * 若最终一定会返回数组内下标，则循环结束后可以直接返回i
	 */
	i = s;
	j = e;
	while (i < j)
	{
		mid = (unsigned int)(s + e) >> 1;
		if (arr[mid] == k) return mid;
		if (arr[mid] > k)
			j = mid - 1;
		else
			i = mid + 1;
	}

	return (arr[i] == k)? i: -1;
}
