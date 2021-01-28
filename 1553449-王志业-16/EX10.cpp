#include <iostream>
#include <time.h>
#include <ctime>  
#include <iomanip>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
using namespace std;


int mc = 0;
int cc = 0;

int Partition(int L[], int low, int high) {
	int pivotkey = L[low];
	L[0] = L[low];
	while (low < high && ++cc) {
		while (low < high && L[high] >= pivotkey&& ++cc) {
			--high;
		}
		L[low] = L[high];
		while (low < high && L[low] <= pivotkey && ++cc) {
			++low;
		}
		L[high] = L[low];
		mc++;
	}
	L[low] = L[0];
	mc++;
	return low;
}

void SelectSort(int h[], int len) {
	int tmp, minid;
	for (int i = 0; i < len; i++) {
		minid = i;
		for (int j = i + 1; j < len; j++) {
			if (h[minid] > h[j] && ++cc) {
				minid = j;
			}
		}
		if (minid != i) {
			tmp = h[i];
			h[i] = h[minid];
			h[minid] = tmp;
			mc++;
		}
	}
	return;
}

void bubbleSort(int h[], int len) {
	int tmp;
	for (int i = len - 1; i >= 0; i--) {
		cc++;
		for (int j = 0; j < i; j++) {
			cc++;
			if (h[j] > h[j + 1] && ++cc) {
				tmp = h[j];
				h[j] = h[j + 1];
				h[j + 1] = tmp;
				mc++;
			}
		}
		cc++;
	}
	cc++;
	return;
}

void Merge(int h[], int t[], int i, int m, int n) {
	int j, k;
	for (j = m + 1, k = i; i <= m && j <= n; ++k) {
		if (h[i] < h[j] && ++cc) {
			t[k] = h[i++];
			mc++;
		}
		else {
			t[k] = h[j++];
			mc++;
		}
	}
	if (i <= m) {
		for (int u = i; u <= m; u++) {
			t[k++] = h[u];
			mc++;
		}
	}
	if (j <= n) {
		for (int u = j; u <= n; ++u) {
			t[k++] = h[u];
			mc++;
		}
	}
	return;
}

void MSort(int h[], int tr[], int s, int t, int n) {
	if (s == t) {
		tr[s] = h[s];
		cc++;
	}
	else {
		int *tr2 = new int[n];
		int m = (s + t) / 2;
		MSort(h, tr2, s, m, n);
		MSort(h, tr2, m + 1, t, n);
		Merge(tr2, tr, s, m, t);
		delete tr2;
	}
}

void MergeSort(int l[], int len) {
	MSort(l, l, 0, len - 1, len);
}


void Qsort(int L[], int low, int high) {
	if (low < high&& ++cc) {
		int pivotLoc = Partition(L, low, high);
		Qsort(L, low, pivotLoc - 1);
		Qsort(L, pivotLoc + 1, high);
	}
	return;
}

void QuickSort(int L[], int length) {
	Qsort(L, 1, length);
}

void ShellSort(int a[], int n)
{
	int j, gap;

	for (gap = n / 2; gap > 0; gap /= 2)
		for (j = gap; j < n; j++)//从数组第gap个元素开始  
			if (a[j] < a[j - gap] && ++cc)//每个元素与自己组内的数据进行直接插入排序  
			{
				int temp = a[j];
				int k = j - gap;
				while (k >= 0 && a[k] > temp && ++cc)
				{
					a[k + gap] = a[k];
					mc++;
					k -= gap;
				}
				a[k + gap] = temp;
				mc++;
			}
}

void DataSwap(int* data1, int* data2)
{
	int temp = *data1;
	*data1 = *data2;
	*data2 = temp;
	mc++;
	mc++;
}


void SelectionSort(int* pDataArray, int iDataNum)
{
	for (int i = 0; i < iDataNum - 1; i++)    //从第一个位置开始  
	{
		int index = i;
		for (int j = i + 1; j < iDataNum; j++)    //寻找最小的数据索引   
			if (pDataArray[j] < pDataArray[index] && ++cc)
				index = j;

		if (index != i)    //如果最小数位置变化则交换  
			DataSwap(&pDataArray[index], &pDataArray[i]);
	}
}


void InsertSort(int h[], int len) {
	int tmp;
	for (int i = 1; i < len; ++i) {
		cc++;
		if (h[i] < h[i - 1]) {
			tmp = h[i];
			h[i] = h[i - 1];
			mc++;
			int j;
			for (j = i - 2; tmp < h[j]; --j) {
				cc++;
				h[j + 1] = h[j];
				mc++;
			}
			cc++;
			mc++;
			h[j + 1] = tmp;
		}
	}
	return;
}


void HeapAdjust(int h[], int s, int m) {
	int rc = h[s];
	for (int j = 2 * s; j <= m; j *= 2) {
		if (j < m && h[j] > h[j + 1] && ++cc) {
			j++;
		}
		if (rc <= h[j] && ++cc) {
			break;
		}
		h[s] = h[j];
		s = j;
		mc++;
	}
	h[s] = rc;
	mc++;
	return;
}


void HeapSort(int h[], int len) {
	for (int i = len / 2; i > 0; --i) {
		HeapAdjust(h, i, len);
	}
	for (int i = len; i > 1; --i) {
		int tmp = h[1];
		h[1] = h[i];
		h[i] = tmp;
		mc++;
		HeapAdjust(h, 1, i - 1);
	}
	return;
}


void randomGet(int* &arr, int n) {
	
	for (int i = 1; i < n; i++) {
		*(arr+i)= rand() % 4000+1;
	}
	return;
}

void sort(int * &L, int n, void (SORTDO)(int *arr, int n)) {
	
	cc = 0;
	mc = 0;
	SORTDO(L, n-1);
	cout << "比较次数：" << cc << endl;
	cout << "移动次数：" << mc << endl;
	
	cout << endl;
}

int main()
{
    srand((unsigned int)(time(0)));
	int n;
	n = 20;
	int *L = (int *)malloc(sizeof(int)*(n + 1)),*p1 = (int *)malloc(sizeof(int)*(n + 1)),*p2 = (int *)malloc(sizeof(int)*(n + 1)),*p3 = (int *)malloc(sizeof(int)*(n + 1)),*p4 = (int *)malloc(sizeof(int)*(n + 1)),*p5 = (int *)malloc(sizeof(int)*(n + 1)),*p6 = (int *)malloc(sizeof(int)*(n + 1)),*p7 = (int *)malloc(sizeof(int)*(n + 1)),*p8 = (int *)malloc(sizeof(int)*(n + 1));
	randomGet(L, n + 1);
	memcpy(p1,L , sizeof(int)*(n + 1));
	memcpy(p2, L, sizeof(int)*(n + 1));
	memcpy(p3, L, sizeof(int)*(n + 1));
	memcpy(p4, L, sizeof(int)*(n + 1));
	memcpy(p5, L, sizeof(int)*(n + 1));
	memcpy(p6, L, sizeof(int)*(n + 1));
	memcpy(p7, L, sizeof(int)*(n + 1));
	memcpy(p8, L, sizeof(int)*(n + 1));
	cout << "插入排序：\n";
	sort(p7, n, InsertSort);
	
	cout << "选择排序：\n";
	sort(p1, n, SelectionSort);
	cout << "希尔排序：\n";
	sort(p2, n, ShellSort);
	cout << "快速排序：\n";
	sort(p3, n, QuickSort);
	cout << "冒泡排序：\n";
	sort(p4, n, bubbleSort);
	cout << "归并排序：\n";
	sort(p5, n, MergeSort);
	cout << "堆排序：\n";
	sort(p6, n, HeapSort);
	
	free(L);
	return 0;
}
