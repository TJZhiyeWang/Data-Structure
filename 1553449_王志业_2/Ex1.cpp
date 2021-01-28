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
//初始化
Status InitLNode(LinkList &L)
{
	L = (LinkList)malloc(sizeof(LNode));
	if (!L)
		exit(OVERFLOW);
	L->next = NULL;
	return OK;
}
//输出所有的元素
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
//插入元素到第i个位置,若不给出插入的位置，则默认为头插法
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
//删除第i个元素
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
//寻找某一个节点的位置，返回其位置
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
//对链表节点进行计数
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
//单链表的逆置
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
//删除所有值为e的元素
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
//去重操作
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
//删除链表
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
	cout << "原始的链表：" <<endl;
	Print_LNode(L);
	cout << "***************************************************" << endl;
	cout << "按回车键测试链表的指定位置插入（第一个，中间位置，最后一个位置）" << endl;
	while (_getch() != '\r');
	e = rand() % (n / 2);
	Insert_LNode(L, e, 1);
	Insert_LNode(L, e, 1+(n+1)/2);
	Insert_LNode(L, e, n+3);
	cout << "插入后的链表：" << endl;
	Print_LNode(L);
	cout << "***************************************************" << endl;
	cout << "按回车键测试链表的指定位置删除（第一个，中间位置，最后一个位置）" << endl;
	while (_getch() != '\r');
	Delete_LNode(L, 1);
	Delete_LNode(L, n/2);
	Delete_LNode(L, n+1);
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
		cout << "没有找到该元素"<<endl;
	cout << "***************************************************" << endl;
	cout << "按回车键测试对链表的计数" << endl;
	while (_getch() != '\r');
	cout << "节点的个数为:" << Count_LNode(L)<<endl;
	cout << "***************************************************" << endl;
	cout << "按回车键测试对链表的逆置" << endl;
	while (_getch() != '\r');
	Inverse_LNode(L);
	cout << "逆置后的链表：" << endl;
	Print_LNode(L);
	cout << "***************************************************" << endl;
	cout << "按回车键测试对链表的去重" << endl;
	while (_getch() != '\r');
	distinct_LNode(L);
	cout<<"去重后的链表为:" << endl;
	Print_LNode(L);
	cout << "***************************************************" << endl;
	cout << "关于单链表的演示到此结束" << endl;
	destory_Link(L);
	return 0;
}
