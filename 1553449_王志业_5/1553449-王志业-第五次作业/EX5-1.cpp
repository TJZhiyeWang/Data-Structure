#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
using namespace std;
/*˳��ջ*/

#define TRUE 1
#define FALSE 0
#define ERROR 0
#define OK 1
#define INFEASIBLE -1
#define OVERFLOW -2
#define STACK_INIT_SIZE 100
typedef int Status;
typedef int SElemType;

typedef struct
{
	SElemType *top;
	SElemType *base;
	int stacksize;
}SqStack;

Status InitStack(SqStack &S, int n)
{
	S.base = (SElemType*)malloc(n*sizeof(SElemType));
	if (!S.base)
		exit(OVERFLOW);
	S.top = S.base;
	S.stacksize = n;
	return OK;
}

Status DestoryStack(SqStack &S)
{
	if (!S.base)
		exit(ERROR);
	free(S.base);
	S.top = NULL;
	S.stacksize = 0;
	return OK;
}

Status StatusEmpty(SqStack S)
{
	if (S.top == S.base)
		return TRUE;
	return FALSE;
}

Status Push(SqStack &S, SElemType e)
{
	if (S.top >= S.base + S.stacksize)
		return ERROR;
	*S.top = e;
	S.top++;
	return OK;
}

Status Pop(SqStack &S, SElemType &e)
{
	if (StatusEmpty(S))
		return ERROR;
	e = *(S.top - 1);
	S.top--;
	return OK;
}

Status StackTranverse(SqStack S)
{
	for (int i = 1; i <= S.top - S.base; i++)
		cout << *(S.top - i) << " ";
	cout << endl;
	return OK;
}
//n����ת��Ϊʮ����
int NtranverseD(char* num, int n)
{
	int dnum = 0, len, i = 0;
	len = strlen(num);
	while (len > 0)
	{
		if (num[len - 1] >= '0'&&num[len - 1] <= '9')
			dnum += (num[len - 1] - '0')*(int)pow(n, i);
		else
			dnum += (num[len - 1] - 'A' + 10)*(int)pow(n, i);
		i++;
		len--;
	}
	return dnum;
}
Status num_convrsion(SqStack &S, int d_num, int dis_n)
{
	SElemType e;
	while (d_num > 0)
	{
		e = d_num%dis_n;
		Push(S, e);
		d_num /= dis_n;
	}
	return OK;
}
int main()
{
	int n;
	SqStack S;
	SElemType e;
	cout << "����ջ�Ĵ�Сn=3" << endl;
	n = 3;
	InitStack(S, n);
	cout << "������СΪ3��ջ" << endl;
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
	cout << "������ջ����ջ" << endl;
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

	int ini_n, dis_n, d_num;
	char num[10];
	cout << "------------------------" << endl;
	cout << "����10���ڽ��Ƶ�ת��8-2" << endl;
	ini_n = 8;
	dis_n = 2;
	cout << "����Ҫת��������Ϊ456" << endl;
	strcpy(num, "456");
	InitStack(S, STACK_INIT_SIZE);
	d_num = NtranverseD(num, ini_n);
	num_convrsion(S, d_num, dis_n);
	cout << "���Ϊ" << endl;
	StackTranverse(S);
	cout << "press Enter to continue" << endl;
	while (_getch() != '\r');

	cout << "------------------------" << endl;
	cout << "����16���ڽ��Ƶ�ת��16-8" << endl;
	ini_n = 16;
	dis_n = 8;
	cout << "����Ҫת��������ΪA86" << endl;
	strcpy(num, "A86");
	InitStack(S, STACK_INIT_SIZE);
	d_num = NtranverseD(num, ini_n);
	num_convrsion(S, d_num, dis_n);
	cout << "���Ϊ" << endl;
	StackTranverse(S);
	cout << "press Enter to continue" << endl;
	while (_getch() != '\r');
	return 0;
}