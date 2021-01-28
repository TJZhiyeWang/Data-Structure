#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
using namespace std;
/*顺序栈*/

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

/* 初始化栈*/
Status InitStack(pStack &S)
{
	S = (pStack)malloc(sizeof(LStack));
	if (!S)
		exit(-1);
	S->next = NULL;
	return OK;
}

/* 入栈操作 */
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

/* 出栈操作 */
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

/* 返回栈顶元素值 */
Status GetTop(pStack &S, SElemType &e)
{
	pStack p;
	if (!S->next)
		return ERROR;
	p = S->next;
	e = p->data;
	return OK;
}
/* 遍历栈的操作 */
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
/* 清空栈 */
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
	cout << "测试空栈弹出" << endl;
	if (Pop(S, e))
		cout << e << endl;
	else
		cout << "Stack is Empty" << endl;
	cout << "press Enter to continue" << endl;
	while (_getch() != '\r');

	cout << "------------------------" << endl;
	cout << "测试入栈" << endl;
	e = 1;
	if (!Push(S, e))
		cout << "Stack is Full" << endl;
	else
		cout << "success" << endl;
	cout << "现在栈内元素为：" << endl;
	StackTranverse(S);
	cout << "press Enter to continue" << endl;
	while (_getch() != '\r');
	e = 2;
	Push(S, e);
	e = 3;
	Push(S, e);

	cout << "------------------------" << endl;
	cout << "测试入栈" << endl;
	cout << "现在栈内元素为：" << endl;
	StackTranverse(S);
	e = 1;
	cout << "再推入元素e" << endl;
	if (!Push(S, e))
		cout << "Stack is Full" << endl;
	else
		cout << "success" << endl;
	cout << "现在栈内元素为：" << endl;
	StackTranverse(S);
	cout << "press Enter to continue" << endl;
	while (_getch() != '\r');
	cout << "------------------------" << endl;
	cout << "测试出栈" << endl;
	if (Pop(S, e))
		cout << e << endl;
	else
		cout << "Stack is Empty" << endl;
	cout << "press Enter to continue" << endl;
	while (_getch() != '\r');
	cout << endl << "测试完毕，栈已删除" << endl;
	DestoryStack(S);
	return 0;
}