#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
using namespace std;


#define TRUE 1
#define FALSE 0
#define ERROR -1
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
//��ʼ��
Status InitLNode(LinkList &L)
{
	L = (LinkList)malloc(sizeof(LNode));
	if (!L)
		exit(OVERFLOW);
	L->next = NULL;
	return OK;
}
//������е�Ԫ��
void Print_LNode(LinkList L)
{
	LinkList p = NULL;
	p = L->next;
	while (p)
	{
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}
//����Ԫ�ص���i��λ��,�������������λ�ã���Ĭ��Ϊͷ�巨
Status Insert_LNode(LinkList &L, ElemType e, int  i = 1)
{
	LinkList p = NULL, node = NULL;
	int n = 1;
	p = L;
	while (p&&n < i)
	{
		p = p->next;
		n++;
	}
	if (!p || n > i)
		return 0;
	node = (LinkList)malloc(sizeof(LNode));
	if (!node)
		exit(OVERFLOW);
	node->data = e;
	node->next = p->next;
	p->next = node;

	return OK;
}
//ɾ����i��Ԫ��
Status Delete_LNode(LinkList &L, int i)
{
	LinkList p = NULL, q;
	int n = 1;
	p = L;
	while (p->next&&n < i)
	{
		p = p->next;
		n++;
	}
	if (!(p->next) || n > i)
		return 0;
	q = p->next;
	p->next = q->next;
	free(q);
	return OK;

}
//Ѱ��ĳһ���ڵ��λ�ã�������λ��
int Search_LNode(LinkList L, ElemType e)
{
	LinkList p = NULL;
	int loc = 1;
	p = L->next;
	while (p && (p->data != e))
	{
		p = p->next;
		loc++;
	}
	if (!p)
		return ERROR;
	return loc;

}
//������ڵ���м���
int Count_LNode(LinkList L)
{
	int count = 0;
	LinkList p = NULL;
	p = L->next;
	while (p)
	{
		count++;
		p = p->next;
	}
	return count;
}
//�����������
Status Inverse_LNode(LinkList &L)
{
	LinkList p, q=NULL,k=NULL;
	p = L->next;
	if (p)
	{
		q = p->next;
		p->next = NULL;
	}
	while (q)
	{
		k = q->next;
		q->next = p;
		p = q;
		q = k;
		if (k)
			k = k->next;
	}
	L->next = p;
	return OK;
}
//ɾ������ֵΪe��Ԫ��
Status Delete_all_LNode(LinkList &L, ElemType e)
{
	LinkList p = L, q;
	while (p->next)
	{
		if (p->next->data == e)
		{
			q = p->next;
			p->next = q->next;
			free(q);
			continue;
		}
		p = p->next;
	}
	return OK;
}
//ȥ�ز���
Status distinct_LNode(LinkList &L)
{
	LinkList p = L->next;
	while (p)
	{
		Delete_all_LNode(p, p->data);
		p = p->next;
	}
	return OK;
}
//ɾ������
Status destory_Link(LinkList &L)
{
	LinkList p=L->next,q=L;
	while (q)
	{
		free(q);
		q = p;
		if (p)
			p = p->next;
		
	}
	return OK;
}
int main()
{
	LinkList L;
	InitLNode(L);
	int n,i,e;
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
	cout << "ԭʼ������" <<endl;
	Print_LNode(L);
	cout << "***************************************************" << endl;
	cout << "���س������������ָ��λ�ò��루��һ�����м�λ�ã����һ��λ�ã�" << endl;
	while (_getch() != '\r');
	e = rand() % (n / 2);
	Insert_LNode(L, e, 1);
	Insert_LNode(L, e, 1+(n+1)/2);
	Insert_LNode(L, e, n+3);
	cout << "����������" << endl;
	Print_LNode(L);
	cout << "***************************************************" << endl;
	cout << "���س������������ָ��λ��ɾ������һ�����м�λ�ã����һ��λ�ã�" << endl;
	while (_getch() != '\r');
	Delete_LNode(L, 1);
	Delete_LNode(L, n/2);
	Delete_LNode(L, n+1);
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
		cout << "û���ҵ���Ԫ��"<<endl;
	cout << "***************************************************" << endl;
	cout << "���س������Զ�����ļ���" << endl;
	while (_getch() != '\r');
	cout << "�ڵ�ĸ���Ϊ:" << Count_LNode(L)<<endl;
	cout << "***************************************************" << endl;
	cout << "���س������Զ����������" << endl;
	while (_getch() != '\r');
	Inverse_LNode(L);
	cout << "���ú������" << endl;
	Print_LNode(L);
	cout << "***************************************************" << endl;
	cout << "���س������Զ������ȥ��" << endl;
	while (_getch() != '\r');
	distinct_LNode(L);
	cout<<"ȥ�غ������Ϊ:" << endl;
	Print_LNode(L);
	cout << "***************************************************" << endl;
	cout << "���ڵ��������ʾ���˽���" << endl;
	destory_Link(L);
	return 0;
}
