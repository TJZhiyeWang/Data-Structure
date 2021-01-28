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

typedef struct LNode
{
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;
//��ʼ��ѭ������
Status InitLNode(LinkList &L)
{
	L = (LinkList)malloc(sizeof(LNode));
	if (!L)
		exit(OVERFLOW);
	L->next = L;
	return OK;
}
//��ӡ����
void Print_LNode(LinkList L)
{
	LinkList p = NULL;
	p = L->next;
	while (p != L)
	{
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}
//����Ԫ�ص���i��λ��Ĭ��Ϊͷ�巨
Status Insert_LNode(LinkList &L, ElemType e, int  i=1)
{
	LinkList p = NULL, node = NULL,q;
	int n = 1;
	p = L->next;
	q = L;
	if (p == L)
	{
		node = (LinkList)malloc(sizeof(LNode));
		if (!node)
			exit(OVERFLOW);
		node->data = e;
		q->next = node;
		node->next = p;
	}
	while (p != L&&n < i)
	{
		q = p;
		p = p->next;
		n++;
	}
	if (p == L || n > i)
		return ERROR;
	node = (LinkList)malloc(sizeof(LNode));
	if (!node)
		exit(OVERFLOW);
	node->data = e;
	node->next = p;
	q->next = node;
	return OK;
}
//ɾ����i��Ԫ��
Status Delete_LNode(LinkList &L, int i)
{
	LinkList p = NULL, q;
	int n = 1;
	p = L->next;
	q = L;
	while (p != L&&n < i)
	{
		q = p;
		p = p->next;
		n++;
	}
	if (p == L || n > i)
		return ERROR;
	q->next = p->next;
	free(p);
	return OK;

}
//��ĳ���ڵ�
Status Search_LNode(LinkList L, ElemType e)
{
	LinkList p = NULL;
	int loc = 1;
	p = L->next;
	while (p != L && (p->data != e))
	{
		p = p->next;
		loc++;
	}
	if (p == L)
		return -1;
	return loc;

}
//����ڵ�ĸ���
int Count_LNode(LinkList L)
{
	int count = 0;
	LinkList p = NULL;
	p = L->next;
	while (p != L)
	{
		count++;
		p = p->next;
	}
	return count;
}
//�ж�һ�������Ƿ�Ϊѭ������
Status is_Circular_LinkList(LinkList L)
{
	LinkList p;
	p = L->next;
	while (p != L && p)
	{
		p = p->next;
	}
	if (p == L)
		return TRUE;
	return FALSE;
}

int main()
{
	LinkList L;
	InitLNode(L);
	int n, i, e;
	cout << "������ڵ�ĸ���n(�������������������)" << endl;
	cin >> n;
	cout << "***************************************************" << endl;
	cout << "���س�����������ĳ�ʼ����ͷ�巨��������" << endl;
	while (_getch() != '\r');
	srand((unsigned)time(0));
	for (i = 0; i < n; i++)
	{
		Insert_LNode(L, rand() % (n / 2));
	}
	cout << "ԭʼ������" << endl;
	Print_LNode(L);
	cout << "***************************************************" << endl;
	cout << "���س������������ָ��λ�ò��루��һ�����м�λ�ã����һ��λ�ã�" << endl;
	while (_getch() != '\r');
	e = rand() % (n / 2);
	Insert_LNode(L, e, 1);
	Insert_LNode(L, e, 1 + (n + 1) / 2);
	Insert_LNode(L, e, n + 3);
	cout << "����������" << endl;
	Print_LNode(L);
	cout << "***************************************************" << endl;
	cout << "���س������������ָ��λ��ɾ������һ�����м�λ�ã����һ��λ�ã�" << endl;
	while (_getch() != '\r');
	Delete_LNode(L, 1);
	Delete_LNode(L, n / 2);
	Delete_LNode(L, n + 1);
	cout << "ɾ���������" << endl;
	Print_LNode(L);
	cout << "***************************************************" << endl;
	cout << "���س�����������Ѱ��ĳһ��Ԫ�ط�����λ��" << endl;
	while (_getch() != '\r');
	e = rand() % (n / 2);
	cout << "ѡȡ��Ԫ��Ϊ" << e << endl;
	if (Search_LNode(L, e))
		cout << "����λ��Ϊ" << Search_LNode(L, e) << endl;
	else
		cout << "û���ҵ���Ԫ��" << endl;
	cout << "***************************************************" << endl;
	cout << "���س������Զ�����ļ���" << endl;
	while (_getch() != '\r');
	cout << "�ڵ�ĸ���Ϊ:" << Count_LNode(L) << endl;
	cout << "***************************************************" << endl;
	cout << "���س��������Ƿ�Ϊѭ������" << endl;
	while (_getch() != '\r');
	if (is_Circular_LinkList(L))
		cout << "��������ѭ������" << endl;
	else
		cout << "��������ѭ������" << endl;
	cout << "***************************************************" << endl;
	return 0;
}
