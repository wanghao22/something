#include "SortC.h"
using namespace std;

namespace SortC
{
	void swapC(int &a, int &b)
	{
		int temp = a;
		a = b;
		b = temp;
	}

	int* get_line_copy(int *arr, int len)
	{
		int* result = new int[len];
		for (int i = 0; i < len; i++)
			result[i] = arr[i];
		return result;
	}

	//冒泡法
	int* bubble_sort(int *arr, int len) 
	{
		int* result = get_line_copy(arr, len);
		for (int i = 0; i < len - 1; i++)
		{
			for (int j = 0; j < len - 1 - i; j++)
			{
				if (result[j] > result[j + 1])
					swapC(result[j], result[j + 1]);
			}
		}
		return result;
	}

	//选择排序
	int* selection_sort(int *arr, int len)
	{
		int* result = get_line_copy(arr, len);
		for (int i = 0; i < len - 1; i++)
		{
			int min = i;
			for (int j = i + 1; j < len; j++)     //走訪未排序的元素
			{
				if (result[j] < result[min])    //找到目前最小值
					min = j;    //紀錄最小值
			}
			swapC(result[min], result[i]);    //做交換
		}
		return result;
	}

	//插入排序
	int* insertion_sort(int *arr, int len)
	{
		int j,temp;
		int* result = get_line_copy(arr, len);
		for (int i = 1; i<len; i++) 
		{
			temp = result[i];
			for (j = i; j > 0 && result[j - 1] > temp; j--)
				result[j] = result[j - 1];
			result[j] = temp;
		}
		return result;
	}

	//希尔排序
	int* shell_sort(int *arr, int len)
	{
		int gap, i, j;
		int temp;
		int* result = get_line_copy(arr, len);
		for (gap = len >> 1; gap > 0; gap = gap >>= 1)
		{
			for (i = gap; i < len; i++) 
			{
				temp = result[i];
				for (j = i - gap; j >= 0 && result[j] > temp; j -= gap)
					result[j + gap] = result[j];
				result[j + gap] = temp;
			}
		}
		return result;
	}

	//归并排序_迭代法
	int* merge_sort_iteration(int *arr, int len)
	{
		int* result = get_line_copy(arr, len);
		int* a = result;
		int* b = (int*)malloc(len * sizeof(int));
		int seg, start;
		for (seg = 1; seg < len; seg += seg) 
		{
			for (start = 0; start < len; start += seg + seg) 
			{
				int low = start, mid = min(start + seg, len), high = min(start + seg + seg, len);
				int k = low;
				int start1 = low, end1 = mid;
				int start2 = mid, end2 = high;
				while (start1 < end1 && start2 < end2)
					b[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
				while (start1 < end1)
					b[k++] = a[start1++];
				while (start2 < end2)
					b[k++] = a[start2++];
			}
			int* temp = a;
			a = b;
			b = temp;
		}
		if (a != result)
		{
			int i;
			for (i = 0; i < len; i++)
				b[i] = a[i];
			b = a;
		}
		free(b);
		return result;
	}

	void merge_sort_recursive(int arr[], int reg[], int start, int end)
	{
		if (start >= end)
			return;
		int len = end - start, mid = (len >> 1) + start;
		int start1 = start, end1 = mid;
		int start2 = mid + 1, end2 = end;
		merge_sort_recursive(arr, reg, start1, end1);
		merge_sort_recursive(arr, reg, start2, end2);
		int k = start;
		while (start1 <= end1 && start2 <= end2)
			reg[k++] = arr[start1] < arr[start2] ? arr[start1++] : arr[start2++];
		while (start1 <= end1)
			reg[k++] = arr[start1++];
		while (start2 <= end2)
			reg[k++] = arr[start2++];
		for (k = start; k <= end; k++)
			arr[k] = reg[k];
	}

	//归并排序_递归法
	int* merge_sort_recursion(int *arr, int len)
	{
		int* result = get_line_copy(arr, len);
		int *reg = new int[len];
		merge_sort_recursive(result, reg, 0, len - 1);
		return result;
	}

	//快速排序_迭代法
	int* quick_sort_iteration(int *arr, int len)
	{
		int* result = get_line_copy(arr, len);
		if (len <= 0)
			return nullptr; // 避免len等於負值時引發段錯誤（Segment Fault）
		// r[]模擬列表,p為數量,r[p++]為push,r[--p]為pop且取得元素
		Range *r = new Range[len];
		int p = 0;
		r[p++] = new_Range(0, len - 1);
		while (p) {
			Range range = r[--p];
			if (range.start >= range.end)
				continue;
			int mid = result[(range.start + range.end) / 2]; // 選取中間點為基準點
			int left = range.start, right = range.end;
			do
			{
				while (result[left] < mid)
					++left;   // 檢測基準點左側是否符合要求
				while (result[right] > mid)
					--right; //檢測基準點右側是否符合要求
				if (left <= right)
				{
					swapC(result[left], result[right]);
					left++; right--;               // 移動指針以繼續
				}
			} while (left <= right);
			if (range.start < right) 
				r[p++] = new_Range(range.start, right);
			if (range.end > left) 
				r[p++] = new_Range(left, range.end);
		}
		return result;
	}

	void quick_sort_recursive(int arr[], int start, int end)
	{
		if (start >= end)
			return;
		int mid = arr[end];
		int left = start, right = end - 1;
		while (left < right) {
			while (arr[left] < mid && left < right)
				left++;
			while (arr[right] >= mid && left < right)
				right--;
			swapC(arr[left], arr[right]);
		}
		if (arr[left] >= arr[end])
			swapC(arr[left], arr[end]);
		else
			left++;
		if (left)
			quick_sort_recursive(arr, start, left - 1);
		quick_sort_recursive(arr, left + 1, end);
	}

	//快速排序_递归法
	int* quick_sort_recursion(int *arr, int len)
	{
		int* result = get_line_copy(arr, len);
		quick_sort_recursive(result, 0, len - 1);
		return result;
	}
}

namespace SortT
{
	void swapT(int &a, int &b)
	{
		int temp = a;
		a = b;
		b = temp;
	}

	//冒泡法
	void bubble_sort(int *arr, int len)
	{
		for (int i = 0; i < len - 1; i++)
		{
			for (int j = 0; j < len - 1 - i; j++)
			{
				if (arr[j] > arr[j + 1])
					swapT(arr[j], arr[j + 1]);
			}
		}
	}

	//选择排序
	void selection_sort(int *arr, int len)
	{
		for (int i = 0; i < len - 1; i++)
		{
			int min = i;
			for (int j = i + 1; j < len; j++)     //走訪未排序的元素
			{
				if (arr[j] < arr[min])    //找到目前最小值
					min = j;    //紀錄最小值
			}
			swapT(arr[min], arr[i]);    //做交換
		}
	}

	//插入排序
	void insertion_sort(int *arr, int len)
	{
		int j, temp;
		for (int i = 1; i<len; i++)
		{
			temp = arr[i];
			for (j = i; j>0 && arr[j - 1]>temp; j--)
				arr[j] = arr[j - 1];
			arr[j] = temp;
		}
	}

	//希尔排序
	void shell_sort(int *arr, int len)
	{
		int gap, i, j;
		int temp;
		for (gap = len >> 1; gap > 0; gap = gap >>= 1)
		{
			for (i = gap; i < len; i++)
			{
				temp = arr[i];
				for (j = i - gap; j >= 0 && arr[j] > temp; j -= gap)
					arr[j + gap] = arr[j];
				arr[j + gap] = temp;
			}
		}
	}

	//归并排序_迭代法
	void merge_sort_iteration(int *arr, int len)
	{
		int* a = arr;
		int* b = (int*)malloc(len * sizeof(int));
		int seg, start;
		for (seg = 1; seg < len; seg += seg)
		{
			for (start = 0; start < len; start += seg + seg)
			{
				int low = start, mid = min(start + seg, len), high = min(start + seg + seg, len);
				int k = low;
				int start1 = low, end1 = mid;
				int start2 = mid, end2 = high;
				while (start1 < end1 && start2 < end2)
					b[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
				while (start1 < end1)
					b[k++] = a[start1++];
				while (start2 < end2)
					b[k++] = a[start2++];
			}
			int* temp = a;
			a = b;
			b = temp;
		}
		if (a != arr)
		{
			int i;
			for (i = 0; i < len; i++)
				b[i] = a[i];
			b = a;
		}
		free(b);
	}

	void merge_sort_recursive(int arr[], int reg[], int start, int end)
	{
		if (start >= end)
			return;
		int len = end - start, mid = (len >> 1) + start;
		int start1 = start, end1 = mid;
		int start2 = mid + 1, end2 = end;
		merge_sort_recursive(arr, reg, start1, end1);
		merge_sort_recursive(arr, reg, start2, end2);
		int k = start;
		while (start1 <= end1 && start2 <= end2)
			reg[k++] = arr[start1] < arr[start2] ? arr[start1++] : arr[start2++];
		while (start1 <= end1)
			reg[k++] = arr[start1++];
		while (start2 <= end2)
			reg[k++] = arr[start2++];
		for (k = start; k <= end; k++)
			arr[k] = reg[k];
	}

	//归并排序_递归法
	void merge_sort_recursion(int *arr, int len)
	{
		int *reg = new int[len];
		merge_sort_recursive(arr, reg, 0, len - 1);
	}

	//快速排序_迭代法
	void quick_sort_iteration(int *arr, int len)
	{
		if (len <= 0)
			return; // 避免len等於負值時引發段錯誤（Segment Fault）
		// r[]模擬列表,p為數量,r[p++]為push,r[--p]為pop且取得元素
		Range *r = new Range[len];
		int p = 0;
		r[p++] = new_Range(0, len - 1);
		while (p) {
			Range range = r[--p];
			if (range.start >= range.end)
				continue;
			int mid = arr[(range.start + range.end) / 2]; // 選取中間點為基準點
			int left = range.start, right = range.end;
			do
			{
				while (arr[left] < mid)
					++left;   // 檢測基準點左側是否符合要求
				while (arr[right] > mid)
					--right; //檢測基準點右側是否符合要求
				if (left <= right)
				{
					swapT(arr[left], arr[right]);
					left++; right--;               // 移動指針以繼續
				}
			} while (left <= right);
			if (range.start < right)
				r[p++] = new_Range(range.start, right);
			if (range.end > left)
				r[p++] = new_Range(left, range.end);
		}
	}

	void quick_sort_recursive(int arr[], int start, int end)
	{
		if (start >= end)
			return;
		int mid = arr[end];
		int left = start, right = end - 1;
		while (left < right) {
			while (arr[left] < mid && left < right)
				left++;
			while (arr[right] >= mid && left < right)
				right--;
			swapT(arr[left], arr[right]);
		}
		if (arr[left] >= arr[end])
			swapT(arr[left], arr[end]);
		else
			left++;
		if (left)
			quick_sort_recursive(arr, start, left - 1);
		quick_sort_recursive(arr, left + 1, end);
	}

	//快速排序_递归法
	void quick_sort_recursion(int *arr, int len)
	{
		quick_sort_recursive(arr, 0, len - 1);
	}
}