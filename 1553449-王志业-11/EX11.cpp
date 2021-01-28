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

typedef struct BiTNode
{
	TElemType    data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

typedef BiTree QElemType;
typedef struct
{
	QElemType *elem;
	int front, rear;
	int queuesize;
}SqQueue;
Status InitQueue(SqQueue &Q, int n)
{
	Q.elem = (QElemType*)malloc((n + 1)*sizeof(QElemType));
	if (!Q.elem)
		exit(OVERFLOW);
	Q.rear = n;
	Q.front = n;
	Q.queuesize = n + 1;
	return OK;
}
int Depth(BiTree T)
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
Status CreateBiTree(BiTree &T)
{
	char c;
	if ((c = getchar()) != '#')
	{
		T = (BiTree)malloc(sizeof(BiTNode));
		T->data = c;

		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
	else
		T = NULL;
	return OK;
}

void PreOrderTranverse(BiTree T)
{
	if (T)
	{
		cout << T->data;
		PreOrderTranverse(T->lchild);
		PreOrderTranverse(T->rchild);
	}
}

void InOrderTranverse(BiTree T)
{
	if (T)
	{

		InOrderTranverse(T->lchild);
		cout << T->data;
		InOrderTranverse(T->rchild);
	}
}

void PosOrderTranverse(BiTree T)
{
	if (T)
	{
		PosOrderTranverse(T->lchild);
		PosOrderTranverse(T->rchild);
		cout << T->data;
	}
}

void LevelOrderTranverse(BiTree T)
{
	SqQueue Q;
	BiTree p;
	InitQueue(Q, pow(2, Depth(T)));
	if (T)
	{
		Q.elem[Q.rear] = T;
		Q.rear = (Q.rear + 1) % Q.queuesize;
		while (Q.front != Q.rear)
		{
			p = Q.elem[Q.front];
			cout << p->data;
			Q.front = (Q.front + 1) % Q.queuesize;
			if (p->lchild)
			{
				Q.elem[Q.rear] = p->lchild;
				Q.rear = (Q.rear + 1) % Q.queuesize;
			}
			if (p->rchild)
			{
				Q.elem[Q.rear] = p->rchild;
				Q.rear = (Q.rear + 1) % Q.queuesize;
			}
		}
	}
}

void PrintBiTree(BiTree T, int n = 0)
{
	int i;
	char ch = ' ';
	if (T)
	{
		PrintBiTree(T->rchild, n + 1);
		for (i = 1; i <= n; ++i)
			printf("%5c", ch);
		printf("%c\n", T->data);
		PrintBiTree(T->lchild, n + 1);

	}
}
int leaves_Count(BiTree T)
{
	int num = 0;
	if (T)
	{
		if (!T->lchild&&!T->rchild)
			return 1;
		else
		{
			if (T->lchild)
				num += leaves_Count(T->lchild);
			if (T->rchild)
				num += leaves_Count(T->rchild);
		}
	}
	return num;
}
int node_Count(BiTree T)
{
	if (T)
		return 1 + node_Count(T->lchild) + node_Count(T->rchild);
	else
		return 0;
}
void Copy_BiTree(BiTree T, BiTree &p)
{
	if (T)
	{
		p = (BiTree)malloc(sizeof(BiTNode));
		p->data = T->data;
		p->lchild = NULL;
		p->rchild = NULL;
		Copy_BiTree(T->lchild, p->lchild);
		Copy_BiTree(T->rchild, p->rchild);
	}
}
int main()
{
	BiTree T = NULL;
	cout << "请先序输入一串整形数据，以#表示空节点。如‘abc##d##ef###’" << endl;
	CreateBiTree(T);
	cout << "先序遍历" << endl;
	PreOrderTranverse(T);
	cout << endl;
	cout << "中序遍历";
	cout << endl;
	InOrderTranverse(T);
	cout << endl;
	cout << "后序遍历";
	cout << endl;
	PosOrderTranverse(T);
	cout << endl;
	cout << "层次遍历";
	cout << endl;
	LevelOrderTranverse(T);
	cout << endl;
	cout << "打印树"<<endl;
	PrintBiTree(T);
	cout << "求树的深度" << endl;
	cout << Depth(T) << endl;
	cout << "复制树" << endl;
	BiTree Tcopy = NULL;
	Copy_BiTree(T, Tcopy);
	PrintBiTree(Tcopy);
	cout << "求叶子节点数" << endl;
	cout << leaves_Count(T) << endl;
	cout << "求节点数" << endl;
	cout << node_Count(T) << endl;
	return 0;
}