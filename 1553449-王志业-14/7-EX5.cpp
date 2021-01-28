#define _CRT_SECURE_NO_WARNINGS
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

#define NUM 100

typedef int Status;
typedef int VRType;
typedef int InfoType;
typedef int VertexType;
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

typedef struct ArcNode
{
	int adjvex;
	struct ArcNode *nextarc;
	InfoType *Info;
}ArcNode;
typedef struct VNode
{
	VertexType data;
	int indegree;
	ArcNode *firstarc;
}VNode, AdjList[NUM];
typedef struct
{
	AdjList vertices;
	int vexnum;
	int arcnum;
	int kind;
}ALGraph;
int LocateVex(ALGraph ALG, VertexType v)
{
	int i = 0;
	while (ALG.vertices[i].data != v)
	{
		i++;
	}
	return i;
}
Status CreateALGraph_DN(ALGraph &ALG)
{
	ArcNode *p = NULL;
	int i, j;
	cin >> ALG.vexnum >> ALG.arcnum;
	for (i = 0; i < ALG.vexnum; i++)
	{
		ALG.vertices[i].data = i + 1;
		ALG.vertices[i].firstarc = NULL;
	}
	for (j = 0; j < ALG.arcnum; j++)
	{
		VertexType v1, v2,w;
		cin >> v1 >> v2>>w;
		i = LocateVex(ALG, v1);
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->nextarc = ALG.vertices[i].firstarc;
		ALG.vertices[i].firstarc = p;
		p->adjvex = LocateVex(ALG, v2);
		p->Info = NULL;
	}
	return OK;
}
Status FindIndegree(ALGraph &ALG)
{
	int i = 0,j;
	ArcNode *p;
	for (i = 0; i < ALG.vexnum; i++)
	{
		int num = 0;
		for (j = 0; j < ALG.vexnum; j++)
		{
			p = ALG.vertices[j].firstarc;
			while (p)
			{
				if (p->adjvex == i)
					num++;
				p = p->nextarc;
			}
		}
		ALG.vertices[i].indegree = num;
	}
	return OK;
}
Status TopologicalSort(ALGraph ALG)
{
	FindIndegree(ALG);
	ArcNode *p;
	SqStack S;
	InitStack(S, NUM);
	int i,count,j;
	for (i = 0; i < ALG.vexnum; i++)
		if (!ALG.vertices[i].indegree)
			Push(S, i);
	count = 0;
	while (!StatusEmpty(S))
	{
		Pop(S, i);
		count++;
		p = ALG.vertices[i].firstarc;
		while (p)
		{
			if(!(--ALG.vertices[p->adjvex].indegree))
				Push(S, p->adjvex);
			p = p->nextarc;
		}
	}
	if (count < ALG.vexnum)
		return ERROR;
	return OK;
}
int main()
{
	ALGraph ALG;
    cout<<"---------------图的拓扑排序测试-----------------\n"; 
    cout<<"第一行包含两个整数n、m，表示该图共有n个结点和m条有向边。（n<=100，m<=100）\n"
        <<"接下来m行每行包含三个整数ui、vi，表示有一条长度为wi的有向边连接结点ui、vi。\n"
        <<"点编号从1开始\n";
	CreateALGraph_DN(ALG);
	cout<<"监测是否有环，有则输出0，没有则输出1"<<endl;
	cout << TopologicalSort(ALG);
	return 0;
}
