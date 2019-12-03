#pragma once
#include <iostream>

namespace SortC {
	//交换
	void swapC(int &a, int &b);

	typedef struct _Range {
		int start, end;
	} Range;

	Range inline new_Range(int s, int e) 
	{
		Range r;
		r.start = s;
		r.end = e;
		return r;
	}

	int inline min(int x, int y) {
		return x < y ? x : y;
	}

	//Copy
	int* get_line_copy(int *arr, int len);

	//冒泡法
	int* bubble_sort(int *arr, int len);

	//选择排序
	int* selection_sort(int *arr, int len);

	//插入排序
	int* insertion_sort(int *arr, int len);

	//希尔排序
	int* shell_sort(int *arr, int len);

	//归并排序_迭代法
	int* merge_sort_iteration(int *arr, int len);

	//归并排序_递归法_DO
	void merge_sort_recursive(int arr[], int reg[], int start, int end);

	//归并排序_递归法
	int* merge_sort_recursion(int *arr, int len);

	//快速排序_迭代法
	int* quick_sort_iteration(int *arr, int len);

	//快速排序_递归法_DO
	void quick_sort_recursive(int arr[], int start, int end);

	//快速排序_递归法
	int* quick_sort_recursion(int *arr, int len);
}

namespace SortT {
	//交换
	void swapT(int &a, int &b);

	typedef struct _Range {
		int start, end;
	} Range;

	Range inline new_Range(int s, int e)
	{
		Range r;
		r.start = s;
		r.end = e;
		return r;
	}

	int inline min(int x, int y) {
		return x < y ? x : y;
	}

	//冒泡法
	void bubble_sort(int *arr, int len);

	//选择排序
	void selection_sort(int *arr, int len);

	//插入排序
	void insertion_sort(int *arr, int len);

	//希尔排序
	void shell_sort(int *arr, int len);

	//归并排序_迭代法
	void merge_sort_iteration(int *arr, int len);

	//归并排序_递归法_DO
	void merge_sort_recursive(int arr[], int reg[], int start, int end);

	//归并排序_递归法
	void merge_sort_recursion(int *arr, int len);

	//快速排序_迭代法
	void quick_sort_iteration(int *arr, int len);

	//快速排序_递归法_DO
	void quick_sort_recursive(int arr[], int start, int end);

	//快速排序_递归法
	void quick_sort_recursion(int *arr, int len);
}

/*ms
容器排序	402		368		25510	--
冒泡法		360		352		--		两次遍历（0 to len）(i to len)，全部交换
选择排序	179		186		74782	两次遍历（0 to len）(i to len)，选择最小值交换
插入排序	79		72		40633	两次遍历（0 to len）(0 to i)，把数组分成长度为i的有序数组和无序数组，把无序数组的第一个数有序的插入到有序数组中，i++;
希尔排序	60		54		4023	两次遍历(step = len>>1,step>0)(0 to len,i += step)按步长作比较
归并迭代法	71		65		4529
归并递归法	77		69		4988
快速迭代法	83		72		5683
快速递归法	88		85		12703
*/