#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
using namespace std;
/*˳��ջ*/

#define TRUE 1
#define FALSE 0
#define ERROR 0
#define OK 1
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
typedef int SElemType;

typedef struct LStack
{
	SElemType data;
	struct LStack* next;
}LStack,*pStack;

/* ��ʼ��ջ*/
Status InitStack(pStack &S)
{
	S = (pStack)malloc(sizeof(LStack));
	if (!S)
		exit(-1);
	S->next = NULL;
	return OK;
}

/* ��ջ���� */
Status Push(pStack &S, SElemType e)
{
	pStack p;
	p= (pStack)malloc(sizeof(LStack));
	if (!e)
		return ERROR;
	p->data = e;
	p->next = S->next;
	S->next = p;
	return OK;
}

/* ��ջ���� */
Status Pop(pStack &S, SElemType &e)
{
	pStack p;
	if (!S->next)
		return ERROR;
	p = S->next;
	S->next = p->next;
	e = p->data;
	free(p);
	return OK;
}

/* ����ջ��Ԫ��ֵ */
Status GetTop(pStack &S, SElemType &e)
{
	pStack p;
	if (!S->next)
		return ERROR;
	p = S->next;
	e = p->data;
	return OK;
}
/* ����ջ�Ĳ��� */
Status StackTranverse(pStack S)
{
	pStack p=S->next;
	while (p)
	{
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
	return OK;
}
/* ���ջ */
Status DestoryStack(pStack &S)
{
	pStack p = S,q;
	while (p)
	{
		q = p->next;
		free(p);
		p = q;
	}
	return OK;
}


int main()
{
	pStack S;
	SElemType e;
	InitStack(S);
	cout << "------------------------" << endl;
	cout << "���Կ�ջ����" << endl;
	if (Pop(S, e))
		cout << e << endl;
	else
		cout << "Stack is Empty" << endl;
	cout << "press Enter to continue" << endl;
	while (_getch() != '\r');

	cout << "------------------------" << endl;
	cout << "������ջ" << endl;
	e = 1;
	if (!Push(S, e))
		cout << "Stack is Full" << endl;
	else
		cout << "success" << endl;
	cout << "����ջ��Ԫ��Ϊ��" << endl;
	StackTranverse(S);
	cout << "press Enter to continue" << endl;
	while (_getch() != '\r');
	e = 2;
	Push(S, e);
	e = 3;
	Push(S, e);

	cout << "------------------------" << endl;
	cout << "������ջ" << endl;
	cout << "����ջ��Ԫ��Ϊ��" << endl;
	StackTranverse(S);
	e = 1;
	cout << "������Ԫ��e" << endl;
	if (!Push(S, e))
		cout << "Stack is Full" << endl;
	else
		cout << "success" << endl;
	cout << "����ջ��Ԫ��Ϊ��" << endl;
	StackTranverse(S);
	cout << "press Enter to continue" << endl;
	while (_getch() != '\r');
	cout << "------------------------" << endl;
	cout << "���Գ�ջ" << endl;
	if (Pop(S, e))
		cout << e << endl;
	else
		cout << "Stack is Empty" << endl;
	cout << "press Enter to continue" << endl;
	while (_getch() != '\r');
	cout << endl << "������ϣ�ջ��ɾ��" << endl;
	DestoryStack(S);
	return 0;
}