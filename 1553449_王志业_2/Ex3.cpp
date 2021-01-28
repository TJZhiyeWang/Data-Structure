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

typedef struct LNode
{
	ElemType data;
	struct LNode *next;
	struct LNode *prior;
}LNode, *LinkList;

Status InitLNode(LinkList &L)
{
	L = (LinkList)malloc(sizeof(LNode));
	if (!L)
		exit(OVERFLOW);
	L->next = L;
	L->prior = L;
	return OK;
}

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
//尾插法
Status Insert_head(LinkList &L, ElemType e)
{
	LinkList node = NULL;
	node = (LinkList)malloc(sizeof(LNode));
	if (!node)
		exit(OVERFLOW);
	node->data = e;
	node->next = L;
	L->prior->next = node;
	node->prior = L->prior;
	L->prior = node;
	return OK;
}
//插入元素到第i个位置
Status Insert_LNode(LinkList &L, ElemType e, int  i=1)
{
	LinkList p = NULL, node = NULL;
	int n = 1;
	p = L->next;
	if (p == L)
	{
		node = (LinkList)malloc(sizeof(LNode));
		if (!node)
			exit(OVERFLOW);
		node->data = e;
		node->next = p;
		p->prior->next = node;
		node->prior = p->prior;
		p->prior = node;
	}
	while (p != L&&n < i)
	{
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
	p->prior->next = node;
	node->prior = p->prior;
	p->prior = node;

	return OK;
}

//删除第i个元素
Status Delete_LNode(LinkList &L, int i)
{
	LinkList p = NULL, q;
	int n = 1;
	p = L->next;
	while (p != L&&n < i)
	{
		p = p->next;
		n++;
	}
	if (p == L || n > i)
		return ERROR;
	q = p->next;
	p->next->prior = p->prior;
	p->prior->next = q;
	free(p);
	return OK;

}

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

int main()
{
	LinkList L;
	InitLNode(L);
	int n, i, e;
	cout << "请输入节点的个数n(后面给出随机的数字填充)" << endl;
	cin >> n;
	cout << "***************************************************" << endl;
	cout << "按回车键测试链表的初始化及头插法建立链表" << endl;
	while (_getch() != '\r');
	srand((unsigned)time(0));
	for (i = 0; i < n; i++)
	{
		Insert_LNode(L, rand() % (n / 2));
	}
	cout << "原始的链表：" << endl;
	Print_LNode(L);
	cout << "***************************************************" << endl;
	cout << "按回车键测试链表的指定位置插入（第一个，中间位置，最后一个位置）" << endl;
	while (_getch() != '\r');
	e = rand() % (n / 2);
	Insert_LNode(L, e, 1);
	Insert_LNode(L, e, 1 + (n + 1) / 2);
	Insert_LNode(L, e, n + 3);
	cout << "插入后的链表：" << endl;
	Print_LNode(L);
	cout << "***************************************************" << endl;
	cout << "按回车键测试链表的指定位置删除（第一个，中间位置，最后一个位置）" << endl;
	while (_getch() != '\r');
	Delete_LNode(L, 1);
	Delete_LNode(L, n / 2);
	Delete_LNode(L, n + 1);
	cout << "删除后的链表：" << endl;
	Print_LNode(L);
	cout << "***************************************************" << endl;
	cout << "按回车键测试链表寻找某一个元素返回其位置" << endl;
	while (_getch() != '\r');
	e = rand() % (n / 2);
	cout << "选取的元素为" << e << endl;
	if (Search_LNode(L, e))
		cout << "它的位置为" << Search_LNode(L, e) << endl;
	else
		cout << "没有找到该元素" << endl;
	cout << "***************************************************" << endl;
	cout << "按回车键测试对链表的计数" << endl;
	while (_getch() != '\r');
	cout << "节点的个数为:" << Count_LNode(L) << endl;
	cout << "***************************************************" << endl;
	return 0;
}


