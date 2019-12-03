#pragma once
#include <iostream>

namespace SortC {
	//����
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

	//ð�ݷ�
	int* bubble_sort(int *arr, int len);

	//ѡ������
	int* selection_sort(int *arr, int len);

	//��������
	int* insertion_sort(int *arr, int len);

	//ϣ������
	int* shell_sort(int *arr, int len);

	//�鲢����_������
	int* merge_sort_iteration(int *arr, int len);

	//�鲢����_�ݹ鷨_DO
	void merge_sort_recursive(int arr[], int reg[], int start, int end);

	//�鲢����_�ݹ鷨
	int* merge_sort_recursion(int *arr, int len);

	//��������_������
	int* quick_sort_iteration(int *arr, int len);

	//��������_�ݹ鷨_DO
	void quick_sort_recursive(int arr[], int start, int end);

	//��������_�ݹ鷨
	int* quick_sort_recursion(int *arr, int len);
}

namespace SortT {
	//����
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

	//ð�ݷ�
	void bubble_sort(int *arr, int len);

	//ѡ������
	void selection_sort(int *arr, int len);

	//��������
	void insertion_sort(int *arr, int len);

	//ϣ������
	void shell_sort(int *arr, int len);

	//�鲢����_������
	void merge_sort_iteration(int *arr, int len);

	//�鲢����_�ݹ鷨_DO
	void merge_sort_recursive(int arr[], int reg[], int start, int end);

	//�鲢����_�ݹ鷨
	void merge_sort_recursion(int *arr, int len);

	//��������_������
	void quick_sort_iteration(int *arr, int len);

	//��������_�ݹ鷨_DO
	void quick_sort_recursive(int arr[], int start, int end);

	//��������_�ݹ鷨
	void quick_sort_recursion(int *arr, int len);
}

/*ms
��������	402		368		25510	--
ð�ݷ�		360		352		--		���α�����0 to len��(i to len)��ȫ������
ѡ������	179		186		74782	���α�����0 to len��(i to len)��ѡ����Сֵ����
��������	79		72		40633	���α�����0 to len��(0 to i)��������ֳɳ���Ϊi������������������飬����������ĵ�һ��������Ĳ��뵽���������У�i++;
ϣ������	60		54		4023	���α���(step = len>>1,step>0)(0 to len,i += step)���������Ƚ�
�鲢������	71		65		4529
�鲢�ݹ鷨	77		69		4988
���ٵ�����	83		72		5683
���ٵݹ鷨	88		85		12703
*/