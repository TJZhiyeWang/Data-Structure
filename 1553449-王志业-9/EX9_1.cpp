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

typedef struct
{
	int head;
	int rear;
	int queuesize;
	QElemType *elem;
}SqQueue;

Status InitQueue(SqQueue &S, int n)
{
	S.elem = (QElemType*)malloc((n + 1)*sizeof(QElemType));
	if (!S.elem)
		exit(OVERFLOW);
	S.rear = n;
	S.head = n;
	S.queuesize = n + 1;
	return OK;
}

Status DestoryQueue(SqQueue &S)
{
	if (!S.elem)
		exit(ERROR);
	free(S.elem);
	S.queuesize = 0;
	return OK;
}

Status StatusEmpty(SqQueue S)
{
	if (S.rear == S.head)
		return TRUE;
	return FALSE;
}

Status EnQueue(SqQueue &S, QElemType e)
{
	if (S.head == (S.rear + 1) % S.queuesize)
		return ERROR;
	S.elem[(S.rear + 1) % S.queuesize] = e;
	S.rear = (S.rear + 1) % S.queuesize;
	return OK;
}

Status DeQueue(SqQueue &S, QElemType &e)
{
	if (StatusEmpty(S) == 1)
		return ERROR;
	e = S.elem[(S.head + 1) % S.queuesize];
	S.head = (S.head + 1) % S.queuesize;
	return OK;
}

Status QueueTranverse(SqQueue S)
{
	int i;
	i = S.head;
	while (i != S.rear)
	{
		cout << S.elem[(i + 1) % S.queuesize] << " ";
		i = (i + 1) % S.queuesize;
	}
	return OK;
}

int main()
{
	int n;
	SqQueue S;
	QElemType e;
	
	cout << "������еĴ�Сn=3" << endl;
	n = 3;
	InitQueue(S, n);
	cout << "������СΪ3�Ķ���" << endl;
	cout << "------------------------" << endl;
	cout << "���Կն��г���" << endl;
	if (DeQueue(S, e))
		cout << e << endl;
	else
		cout << "Queue is Empty" << endl;
	cout << "press Enter to continue" << endl;
	while (_getch() != '\r');

	cout << "------------------------" << endl;
	cout << "�������" << endl;
	e = 1;
	if (!EnQueue(S, e))
		cout << "Queue is Full" << endl;
	else
		cout << "success" << endl;
	cout << "���ڶ���Ԫ��Ϊ��" << endl;
	QueueTranverse(S);
	cout << "press Enter to continue" << endl;
	while (_getch() != '\r');
	e = 2;
	EnQueue(S, e);
	e = 3;
	EnQueue(S, e);

	cout << "------------------------" << endl;
	cout << "�������������" << endl;
	cout << "����ջ��Ԫ��Ϊ��" << endl;
	QueueTranverse(S);
	e = 1;
	cout << "������Ԫ��e" << endl;
	if (!EnQueue(S, e))
		cout << "Queue is Full" << endl;
	else
		cout << "success" << endl;
	cout << "���ڶ���Ԫ��Ϊ��" << endl;
	QueueTranverse(S);
	cout << "press Enter to continue" << endl;
	while (_getch() != '\r');
	cout << "------------------------" << endl;
	cout << "���Գ���" << endl;
	if (DeQueue(S, e))
		cout << e << endl;
	else
		cout << "Queue is Empty" << endl;
	cout << "press Enter to continue" << endl;
	while (_getch() != '\r');
	cout << endl << "������ϣ�ջ��ɾ��" << endl;
	DestoryQueue(S);
	return 0;
}