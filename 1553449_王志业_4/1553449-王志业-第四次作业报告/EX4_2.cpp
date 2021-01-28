#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
using namespace std;


#define TRUE 1
#define FALSE 0
#define ERROR 0
#define OK 1
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
typedef int QElemType;

typedef struct LQueue
{
    struct LQueue *next;
	QElemType data;
}*pQueue;

Status InitQueue(pQueue &S)
{
	S = (pQueue)malloc(sizeof(LQueue));
	if (!S)
		return OVERFLOW;
	S->next=NULL;
	return OK;
}

Status DestoryQueue(pQueue &S)
{
	pQueue p=S, q;
	if (!S)
		return ERROR;
	while (p)
	{
		q = p->next;
		free(p);
		p = q;
	}
	return OK;
}

Status StatusEmpty(pQueue S)
{
	if (!S->next)
		return TRUE;
	return FALSE;
}

Status EnQueue(pQueue &S, QElemType e)
{
	pQueue p,q;
	p = S;
	while (p->next)
	{
		p = p->next;
	}
	q= (pQueue)malloc(sizeof(LQueue));
	if (!q)
		return OVERFLOW;
	q->next = p->next;
	p->next = q;
	q->data = e;
	return OK;
}

Status DeQueue(pQueue &S, QElemType &e)
{
	pQueue p = S->next;
	if (!p)
		return ERROR;
	e = p->data;
	S->next = p->next;
	free(p);
	return OK;
}

Status QueueTranverse(pQueue S)
{
	pQueue p = S->next;
	while (p)
	{
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
	return OK;
}

int main()
{
	pQueue S;
	QElemType e;

	InitQueue(S);
	cout << "创建大小为3的队列" << endl;
	cout << "------------------------" << endl;
	cout << "测试空队列出队" << endl;
	if (DeQueue(S, e))
		cout << e << endl;
	else
		cout << "Queue is Empty" << endl;
	cout << "press Enter to continue" << endl;
	while (_getch() != '\r');

	cout << "------------------------" << endl;
	cout << "测试入队" << endl;
	e = 1;
	if (!EnQueue(S, e))
		cout << "Queue is Full" << endl;
	else
		cout << "success" << endl;
	cout << "现在队内元素为：" << endl;
	QueueTranverse(S);
	cout << "press Enter to continue" << endl;
	while (_getch() != '\r');
	e = 2;
	EnQueue(S, e);
	e = 3;
	EnQueue(S, e);

	cout << "------------------------" << endl;
	cout << "现在栈内元素为：" << endl;
	QueueTranverse(S);
	e = 1;
	cout << "再推入元素e" << endl;
	if (!EnQueue(S, e))
		cout << "Queue is Full" << endl;
	else
		cout << "success" << endl;
	cout << "现在队内元素为：" << endl;
	QueueTranverse(S);
	cout << "press Enter to continue" << endl;
	while (_getch() != '\r');
	cout << "------------------------" << endl;
	cout << "测试出队" << endl;
	if (DeQueue(S, e))
		cout << e << endl;
	else
		cout << "Queue is Empty" << endl;
	cout << "press Enter to continue" << endl;
	while (_getch() != '\r');
	cout << endl << "测试完毕，栈已删除" << endl;
	DestoryQueue(S);
	return 0;
}