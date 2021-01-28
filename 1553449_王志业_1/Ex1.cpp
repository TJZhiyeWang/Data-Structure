#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>//ʹ�õ�ǰʱ��������
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

//˳�����
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
//���L���Ƿ���Ԫ��e,û�з���1
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
//�����ϲ�
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
	cout << "�������Զ����ɵ����ݵĸ���" << endl;
	cin >> n;
	InitList_Sq(L, n);
	srand((unsigned)time(0));
	for (i = 0; i < n; i++)
	{
		//L.elem[i] = rand() % (n / 2);//����0-n/2֮����������֤ÿ�������ٳ�������
		FillList_Sq(L, rand() % (n / 2));
	}
	cout << "***************************************************" << endl;
	cout << "ԭʼ����:������Ҫ��1��2��" << endl;
	PrintList_Sq(L);
	cout << "***************************************************" << endl;
	cout << "���س��������ڵ�һ���м䣬���һ��λ�ò���Ԫ��n+1" << endl;
	while (_getch() != '\r');
	ListInsert_Sq(L, 1, n + 1);
	ListInsert_Sq(L, L.length + 1, n + 1);
	ListInsert_Sq(L, L.length / 2, n + 1);
	cout << "��������飺" << endl;
	PrintList_Sq(L);
	cout << "***************************************************" << endl;
	cout << "���س�������ɾ����һ���м䣬����Ԫ��" << endl;
	while (_getch() != '\r');
	ListDelete_num(L, 1);
	ListDelete_num(L, L.length);
	ListDelete_num(L, L.length / 2);
	cout << "ɾ�������飺" << endl;
	PrintList_Sq(L);
	cout << "***************************************************" << endl;
	cout << "���س������Զ�λĳԪ�أ���0-n/2�����������" << endl;
	while (_getch() != '\r');
	ElemType s;
	s = rand() % (n / 2);
	cout << "��ȡ" << s << "��ѯ����λ��Ϊ:";

	if (LocateElem_Sq(L, s))
		cout << LocateElem_Sq(L, s) << endl;
	else
		cout << "δ�ҵ���Ԫ��" << endl;
	cout << "***************************************************" << endl;
	cout << "���س�������ɾ����һ�γ��ֵ�Ԫ��e�����������ѡ��1��" << endl;
	while (_getch() != '\r');
	s = rand() % (n / 2);
	cout << "��ȡ" << s << "ɾ��:";
	if (ListDelete_fir_elem(L, s))
	{
		cout << "ɾ���������Ϊ:";
		PrintList_Sq(L);
	}
	else
		cout << "δ�ҵ���Ԫ��" << endl;
	cout << "***************************************************" << endl;
	cout << "���س�������ɾ�����г��ֵ�Ԫ��e�����������ѡ��2��" << endl;
	while (_getch() != '\r');
	s = rand() % (n / 2);
	cout << "��ȡ" << s << "ɾ��:";
	if (ListDelete_all_elem(L, s))
	{
		cout << "ɾ���������Ϊ:";
		PrintList_Sq(L);
	}
	else
		cout << "δ�ҵ���Ԫ��" << endl;
	cout << "***************************************************" << endl;
	cout << "���س�������˳������ã�ѡ��3��" << endl;
	while (_getch() != '\r');
	ListInvert(L);
	cout << "���ú�";
	PrintList_Sq(L);
	cout << "***************************************************" << endl;
	cout << "���س���ɾ�����ж���Ԫ�أ�ѡ��5��" << endl;
	while (_getch() != '\r');
	Distinct_Sq(L);
	cout << "�������Ԫ�غ������";
	PrintList_Sq(L);
	cout << "***************************************************" << endl;
	cout << "���س�����������ֽ��в���" << endl;
	while (_getch() != '\r');
	SqList L1, L2;
	InitList_Sq(L1, n);
	InitList_Sq(L2, n);
	for (i = 0; i < n; i++)
	{
		//L.elem[i] = rand() % (n / 2);//����0-n/2֮����������֤ÿ�������ٳ�������
		ListInsert_inorder(L1, rand() % (n / 2));
	}
	cout << "�����ԭʼ����Ϊ��";
	PrintList_Sq(L1);
	cout << "***************************************************" << endl;
	cout << "���س�������������һ��Ԫ�ؽ��в���(����Ҫ��3��" << endl;
	while (_getch() != '\r');
	s = rand() % (n / 2);
	cout << "��ȡ" << s << "����������Ϊ:";
	ListInsert_inorder(L1, s);
	PrintList_Sq(L1);
	cout << "***************************************************" << endl;
	cout << "���س��������������ϲ����в���(����Ҫ��4��" << endl;
	while (_getch() != '\r');
	cout << "������ɵڶ��������Ϊ��";
	for (i = 0; i < n; i++)
	{
		//L.elem[i] = rand() % (n / 2);//����0-n/2֮����������֤ÿ�������ٳ�������
		ListInsert_inorder(L2, rand() % (n / 2));
	}
	PrintList_Sq(L2);
	
	cout << "�ϲ��������Ϊ:";
	PrintList_Sq(SqList_Union(L1, L2));



	for (i = 0; i < n; i++)
	{
		//L.elem[i] = rand() % (n / 2);//����0-n/2֮����������֤ÿ�������ٳ�������
		ListInsert_inorder(L2, rand() % (n / 2));
	}

	cout << "***************************************************" << endl;
	cout << "���س������˳���ѡ��4��" << endl;
	while (_getch() != '\r');
	ListDestroy(L);
	ListDestroy(L1);
	ListDestroy(L2);
	cout << "����˳��������" << endl;
	return 0;
}