#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>//使用当前时钟做种子
using namespace std;


#define TRUE 1
#define FALSE 0
#define ERROR 0
#define OK 1
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
typedef int ElemType;
typedef struct
{
	ElemType *elem;
	int length;
	int listsize;
}SqList;
Status PrintList_Sq(SqList L)
{
	int i;
	for (i = 0; i < L.length; i++)
		cout << L.elem[i] << " ";
	cout << endl;
	return OK;
}
Status InitList_Sq(SqList &L, int n)
{
	L.elem = (ElemType*)malloc(n*sizeof(ElemType));
	if (!L.elem)
		exit(OVERFLOW);
	L.length = 0;
	L.listsize = n;
	return OK;
}
Status FillList_Sq(SqList &L, ElemType e)
{
	if (L.length >= L.listsize)
	{
		ElemType *newbase;
		newbase = (ElemType*)realloc(L.elem, (1 + L.listsize)*sizeof(ElemType));
		if (!newbase)
			exit(OVERFLOW);
		L.elem = newbase;
		L.listsize += 1;
	}
	L.elem[L.length] = e;
	L.length++;
	return OK;
}
Status ListInsert_Sq(SqList &L, int i, ElemType e)
{
	if (i<1 || i>L.length + 1)
		return ERROR;
	if (L.length >= L.listsize)
	{
		ElemType *newbase;
		newbase = (ElemType*)realloc(L.elem, (1 + L.listsize)*sizeof(ElemType));
		if (!newbase)
			exit(OVERFLOW);
		L.elem = newbase;
		L.listsize += 1;
	}
	ElemType *q, *p;
	q = &(L.elem[i - 1]);
	for (p = &(L.elem[L.length - 1]); p >= q; --p)
		*(p + 1) = *p;
	*q = e;
	L.length++;
	return OK;
}

//顺序插入
Status ListInsert_inorder(SqList &L, ElemType e)
{
	if (L.length == 0)
	{
		FillList_Sq(L, e);
		return OK;
	}
	if (L.length >= L.listsize)
	{
		ElemType *newbase;
		newbase = (ElemType*)realloc(L.elem, (1 + L.listsize)*sizeof(ElemType));
		if (!newbase)
			exit(OVERFLOW);
		L.elem = newbase;
		L.listsize += 1;
	}
	ElemType *q, *p;
	q = &(L.elem[L.length - 1]);
	p = &(L.elem[0]);
	while (e > *p&&p <= q)
		p++;
	for (; q >= p; q--)
		*(q + 1) = *q;
	*p = e;
	L.length++;
	return OK;
}
Status ListDelete_num(SqList &L, int i)
{
	if (i<1 || i>L.length)

		return ERROR;


	ElemType *p, *q;
	p = &(L.elem[i - 1]);
	q = L.elem + L.length - 1;
	for (++p; p <= q; ++p)
		*(p - 1) = *p;
	--L.length;
	return OK;
}
Status ListDelete_fir_elem(SqList &L, ElemType e)
{
	ElemType *p, *q;
	q = L.elem + L.length - 1;
	p = L.elem;
	while (p <= q&&*p != e)
		p++;
	if (p > q)
		return ERROR;
	for (++p; p <= q; ++p)
		*(p - 1) = *p;
	--L.length;
	return OK;
}
Status ListDelete_all_elem(SqList &L, ElemType e)
{
	int i = 0, num = 0;
	for (i = 0; i + num < L.length; i++)
	{
		L.elem[i] = L.elem[i + num];
		while (L.elem[i] == e)
		{
			num++;
			L.elem[i] = L.elem[i + num];
		}


	}
	L.length -= num;
	if (num == 0)
		return ERROR;
	else
		return OK;
}
int LocateElem_Sq(SqList L, ElemType e)
{
	int i = 1;
	ElemType *p;
	p = L.elem;
	while (i <= L.length && (*p++) != e)
		i++;
	if (i <= L.length)
	{
		return i;
	}
	else
		return ERROR;
}
Status ListInvert(SqList &L)
{
	ElemType temp;
	for (int i = 0; i < L.length / 2; i++)
	{
		temp = L.elem[i];
		L.elem[i] = L.elem[L.length - 1 - i];
		L.elem[L.length - 1 - i] = temp;
	}
	return OK;
}
Status ListDestroy(SqList &L)
{
	if (L.elem)
		free(L.elem);
	L.length = 0;
	return OK;
}
//检查L中是否有元素e,没有返回1
Status Re_Sq(SqList L, ElemType e)
{
	for (int i = 0; i < L.length; i++)
	{
		if (L.elem[i] == e)
			return FALSE;
	}
	return TRUE;
}
Status Distinct_Sq(SqList &L)
{
	SqList new_L;
	InitList_Sq(new_L, 1);
	if (L.length > 0)
	{
		new_L.elem[0] = L.elem[0];
		new_L.length++;
	}
	else
		return ERROR;
	for (int i = 1; i < L.length; i++)
	{
		if (Re_Sq(new_L, L.elem[i]))
			FillList_Sq(new_L, L.elem[i]);
	}
	free(L.elem);
	L = new_L;
	return OK;

}
//有序表合并
SqList SqList_Union(SqList L1, SqList L2)
{
	SqList new_list;
	InitList_Sq(new_list, L1.length + L2.length);
	new_list.length = L1.length + L2.length;
	ElemType *p, *q, *k;
	p = L1.elem;
	q = L2.elem;
	k = new_list.elem;
	while ((p < L1.elem + L1.length) && (q < L2.elem + L2.length))
	{
		if (*p < *q)
		{
			*k = *p;
			p++;
			k++;
		}
		else
		{
			*k = *q;
			q++;
			k++;
		}

	}
	while (q < L2.elem + L2.length)
	{
		*k = *q;
		q++;
		k++;
	}

	while (p < L1.elem + L1.length)
	{
		*k = *p;
		p++;
		k++;
	}
	return new_list;
}
int main()
{
	SqList L;
	int n, i;
	cout << "请输入自动生成的数据的个数" << endl;
	cin >> n;
	InitList_Sq(L, n);
	srand((unsigned)time(0));
	for (i = 0; i < n; i++)
	{
		//L.elem[i] = rand() % (n / 2);//产生0-n/2之间多个数，保证每个数至少出现两次
		FillList_Sq(L, rand() % (n / 2));
	}
	cout << "***************************************************" << endl;
	cout << "原始数组:（基本要求1，2）" << endl;
	PrintList_Sq(L);
	cout << "***************************************************" << endl;
	cout << "按回车键测试在第一，中间，最后一个位置插入元素n+1" << endl;
	while (_getch() != '\r');
	ListInsert_Sq(L, 1, n + 1);
	ListInsert_Sq(L, L.length + 1, n + 1);
	ListInsert_Sq(L, L.length / 2, n + 1);
	cout << "插入后数组：" << endl;
	PrintList_Sq(L);
	cout << "***************************************************" << endl;
	cout << "按回车键测试删除第一，中间，最后的元素" << endl;
	while (_getch() != '\r');
	ListDelete_num(L, 1);
	ListDelete_num(L, L.length);
	ListDelete_num(L, L.length / 2);
	cout << "删除后数组：" << endl;
	PrintList_Sq(L);
	cout << "***************************************************" << endl;
	cout << "按回车键测试定位某元素（在0-n/2内随机产生）" << endl;
	while (_getch() != '\r');
	ElemType s;
	s = rand() % (n / 2);
	cout << "抽取" << s << "查询它的位置为:";

	if (LocateElem_Sq(L, s))
		cout << LocateElem_Sq(L, s) << endl;
	else
		cout << "未找到该元素" << endl;
	cout << "***************************************************" << endl;
	cout << "按回车键测试删除第一次出现的元素e（随机数）（选作1）" << endl;
	while (_getch() != '\r');
	s = rand() % (n / 2);
	cout << "抽取" << s << "删除:";
	if (ListDelete_fir_elem(L, s))
	{
		cout << "删除后的数组为:";
		PrintList_Sq(L);
	}
	else
		cout << "未找到该元素" << endl;
	cout << "***************************************************" << endl;
	cout << "按回车键测试删除所有出现的元素e（随机数）（选作2）" << endl;
	while (_getch() != '\r');
	s = rand() % (n / 2);
	cout << "抽取" << s << "删除:";
	if (ListDelete_all_elem(L, s))
	{
		cout << "删除后的数组为:";
		PrintList_Sq(L);
	}
	else
		cout << "未找到该元素" << endl;
	cout << "***************************************************" << endl;
	cout << "按回车键测试顺序表逆置（选作3）" << endl;
	while (_getch() != '\r');
	ListInvert(L);
	cout << "逆置后：";
	PrintList_Sq(L);
	cout << "***************************************************" << endl;
	cout << "按回车键删除所有多余元素（选作5）" << endl;
	while (_getch() != '\r');
	Distinct_Sq(L);
	cout << "清除多余元素后的数组";
	PrintList_Sq(L);
	cout << "***************************************************" << endl;
	cout << "按回车键对有序表部分进行测试" << endl;
	while (_getch() != '\r');
	SqList L1, L2;
	InitList_Sq(L1, n);
	InitList_Sq(L2, n);
	for (i = 0; i < n; i++)
	{
		//L.elem[i] = rand() % (n / 2);//产生0-n/2之间多个数，保证每个数至少出现两次
		ListInsert_inorder(L1, rand() % (n / 2));
	}
	cout << "有序表原始数组为：";
	PrintList_Sq(L1);
	cout << "***************************************************" << endl;
	cout << "按回车键对有序表插入一个元素进行测试(基本要求3）" << endl;
	while (_getch() != '\r');
	s = rand() % (n / 2);
	cout << "抽取" << s << "插入后的数组为:";
	ListInsert_inorder(L1, s);
	PrintList_Sq(L1);
	cout << "***************************************************" << endl;
	cout << "按回车键对两个有序表合并进行测试(基本要求4）" << endl;
	while (_getch() != '\r');
	cout << "随机生成第二个有序表为：";
	for (i = 0; i < n; i++)
	{
		//L.elem[i] = rand() % (n / 2);//产生0-n/2之间多个数，保证每个数至少出现两次
		ListInsert_inorder(L2, rand() % (n / 2));
	}
	PrintList_Sq(L2);
	
	cout << "合并后的数组为:";
	PrintList_Sq(SqList_Union(L1, L2));



	for (i = 0; i < n; i++)
	{
		//L.elem[i] = rand() % (n / 2);//产生0-n/2之间多个数，保证每个数至少出现两次
		ListInsert_inorder(L2, rand() % (n / 2));
	}

	cout << "***************************************************" << endl;
	cout << "按回车键清空顺序表（选作4）" << endl;
	while (_getch() != '\r');
	ListDestroy(L);
	ListDestroy(L1);
	ListDestroy(L2);
	cout << "所有顺序表已清空" << endl;
	return 0;
}