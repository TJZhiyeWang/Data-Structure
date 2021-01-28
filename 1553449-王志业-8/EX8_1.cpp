#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
using namespace std;


#define TRUE 1
#define FALSE 0
#define ERROR 0
#define OK 1
#define INFEASIBLE -1
#define OVERFLOW -2

#define max   100
typedef int Status;
typedef char SElemType;

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

SElemType GetTop(SqStack &S)
{
	if (StatusEmpty(S))
		return ERROR;
	return *(S.top - 1);
}
int main()
{
	int i = 0;
	bool flag=1;
	SqStack St;
	SElemType e;
	InitStack(St, max);
	while ((e = getchar())!=EOF)
	{
		if(e=='(')
			Push(St, e);
		else if(e=='[') 
			Push(St, e);
		else if(e=='{')
			Push(St, e);
		else if(e==')')
		{
			if (Pop(St, e) == OK)
				if (e != '(') {     //≤ª∆•≈‰
					cout << "no\n" << e << "∆⁄¥˝”“¿®∫≈\n";
					return ERROR;
				}
				else continue;
			else {                  //’ªø’ 
				cout << "no\n)∆⁄¥˝◊Û¿®∫≈\n";
				return ERROR;
			}
		}
		else if(e==']')
		{
			if (Pop(St, e) == OK)
				if (e != '[') {     
					cout << "no\n" << e << "∆⁄¥˝”“¿®∫≈\n";
					return ERROR;
				}
				else continue;
			else {                 
				cout << "no\n]∆⁄¥˝◊Û¿®∫≈\n";
				return ERROR;
			}
		}
		else if(e=='}')
		{
			if (Pop(St, e) == OK)
				if (e != '{') {     
					cout << "no\n" << e << "∆⁄¥˝”“¿®∫≈\n";
					return ERROR;
				}
				else continue;
			else {                   
				cout << "no\n}∆⁄¥˝◊Û¿®∫≈\n";
				return ERROR;
			}
		}
	}
	if (StatusEmpty(St)) {  
		cout << "yes" << endl;
		return OK;
	}
	else {
		Pop(St, e);
		cout << "no\n" << e << "∆⁄¥˝”“¿®∫≈\n";
		return ERROR;
	}

	
	return 0;
}

