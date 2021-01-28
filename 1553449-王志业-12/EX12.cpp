#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <math.h>
using namespace std;

#define TRUE 1
#define FALSE 0
#define ERROR 0
#define OK 1
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
typedef char TElemType;
typedef enum { Link, Thread } PointerTag;

typedef struct BiThrNode
{
	TElemType data;
	struct BiThrNode *lchild, *rchild;
	PointerTag LTag, RTag;
}BiThrNode, *BiThrTree;

typedef BiThrTree SElemType;
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

Status CreateBiThrTree(BiThrTree &T)
{
	char c;
	if ((c = getchar()) != '#')
	{
		T = (BiThrTree)malloc(sizeof(BiThrNode));
		T->data = c;

		CreateBiThrTree(T->lchild);
		CreateBiThrTree(T->rchild);
	}
	else
		T = NULL;
	return OK;
}
int Depth(BiThrTree T)
{
	if (T)
	{
		if (Depth(T->lchild) > Depth(T->rchild))
			return 1 + Depth(T->lchild);
		else
			return 1 + Depth(T->rchild);
	}
	return 0;
}
BiThrTree pre = NULL;
Status PreThreading(BiThrTree &T)
{
	BiThrTree p = T;
	SqStack S;
	InitStack(S, pow(2, Depth(T)));
	while (p || S.base != S.top)
	{
		if (p->lchild)
		{
			p->LTag = Link;
			if (p->rchild)
			{
				Push(S, p->rchild);
				p->RTag = Link;
			}
			else
			{
				p->RTag = Thread;
				p->rchild = p->lchild;
			}
			pre = p;
			p = p->lchild;

		}
		else
		{
			p->LTag = Thread;
			p->lchild = pre;
			if (p->rchild)
			{
				p->RTag = Link;
				p = p->rchild;
			}
			else
			{
				p->RTag = Thread;
				if (S.top != S.base)
				{
					pre = p;
					p->rchild = *(S.top - 1);
					Pop(S, p);
				}
				else
				{
					p->rchild = NULL;
					p = p->rchild;
				}
			}
		}
	}
	DestoryStack(S);
	return OK;
}
void preorder_Thr(BiThrTree T)
{
	BiThrTree p = T;
	printf("%c", p->data);
	while (p->rchild)
	{
		if (p->LTag == Link)
			p = p->lchild;
		else
			p = p->rchild;
		printf("%c", p->data);
	}
}


void InThreading(BiThrTree &T)
{
	if (T)
	{
		InThreading(T->lchild);
		if (!T->rchild)
			T->RTag = Thread;
		else
			T->RTag = Link;
		if (pre && pre->RTag == Thread)
			pre->rchild = T;
		if (!T->lchild)
		{
			T->LTag = Thread;
			T->lchild = pre;
		}
		else
			T->LTag = Link;
		pre = T;
		InThreading(T->rchild);
	}
}
void inorder_Thr(BiThrTree T)
{
	BiThrTree p = T;
	while (p->LTag == Link)
		p = p->lchild;
	printf("%c", p->data);
	while (p->rchild)
	{
		if (p->RTag == Link)
		{
			p = p->rchild;
			while (p->LTag == Link) p = p->lchild;
		}
		else p = p->rchild;
		printf("%c", p->data);
	}
}
void PrintBiTree(BiThrTree T, int n = 0)
{
	int i;
	char ch = ' ';
	if (T)
	{
		if (T->RTag == Link)
			PrintBiTree(T->rchild, n + 1);
		for (i = 1; i <= n; ++i)
			printf("%5c", ch);
		printf("%c%d%d\n", T->data, T->LTag, T->RTag);
		if (T->LTag == Link)
			PrintBiTree(T->lchild, n + 1);

	}
}
void Copy_BiTree(BiThrTree T, BiThrTree &p)
{
	if (T)
	{
		p = (BiThrTree)malloc(sizeof(BiThrNode));
		p->data = T->data;
		p->lchild = NULL;
		p->rchild = NULL;
		Copy_BiTree(T->lchild, p->lchild);
		Copy_BiTree(T->rchild, p->rchild);
	}
}


int main()
{
	BiThrTree T = NULL,T1=NULL,T2=NULL;
	cout << "请先序输入一个字符型树的序列，以#代表空节点" << endl;
	CreateBiThrTree(T);
	Copy_BiTree(T, T1);
	Copy_BiTree(T, T2);
	cout << "先序遍历" << endl;
	
	PreThreading(T);
	PrintBiTree(T);
	cout << endl;
	preorder_Thr(T);
	cout << endl;
	pre = NULL;
	cout << "中序遍历" << endl;
	InThreading(T1);
	PrintBiTree(T1);
	cout << endl;
	inorder_Thr(T1);
	cout << endl;
	return 0;
}
