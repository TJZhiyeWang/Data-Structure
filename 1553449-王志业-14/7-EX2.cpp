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

#define NUM 50


typedef int Status;
typedef int VRType;
typedef int InfoType;
typedef int VertexType;

typedef struct ArcCell
{
	VRType adj;
	InfoType *info;
}ArcCell, AdjMatrix[NUM][NUM];

typedef struct
{
	VertexType vexs[NUM];//点的列表
	AdjMatrix arcs;
	int vexnum, arcnum;
}MGraph;

int LocateVex(MGraph G, VertexType v)
{
	int i = 0;
	while (G.vexs[i] != v)
	{
		i++;
	}
	return i;
}
Status CreateUDG(MGraph &G)
{
	scanf("%d%d", &G.vexnum, &G.arcnum);
	int i, j;
	for (i = 0; i < G.vexnum; i++)
		G.vexs[i] = i;
	for (i = 0; i < G.vexnum; i++)
	{
		for (j = 0; j < G.vexnum; j++)
		{
			G.arcs[i][j] = { 0,NULL };
		}
	}
	int k;
	VertexType v1, v2;
	VRType w = 1;
	for (k = 0; k < G.arcnum; k++)
	{
		cin >> v1 >> v2;
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		G.arcs[i][j].adj = w;
		G.arcs[j][i].adj = w;
	}
	return OK;
}

bool visited[NUM];
void DFS(MGraph G, int v)
{
	cout << G.vexs[v];
	visited[v] = 1;
	int i;
	for (i = 0; i < G.vexnum; i++)
	{
		if (G.arcs[v][i].adj&& !visited[i])//如果联通且未访问
		{
			cout << " ";
			DFS(G, i);
		}
	}
}
void DFSTraverse(MGraph G)
{
	int v;
	for (v = 0; v < G.vexnum; v++)
		visited[v] = 0;
	for (v = 0; v < G.vexnum; v++)
		if (!visited[v])
		{
			cout << "{";
           DFS(G, v);
		   cout <<"}";
		}	
}

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
void BFS(MGraph G, int v)
{
	SqQueue Q;
	int i;
	InitQueue(Q,NUM);
	cout << v;
	visited[v] = 1;
	EnQueue(Q, v);
	while (!StatusEmpty(Q))
	{
		DeQueue(Q, v);
		for (i = 0; i < G.vexnum; i++)
		{
			if (G.arcs[v][i].adj&& !visited[i])
			{
				cout << " ";
				cout << i ;
				
				visited[i] = 1;
				EnQueue(Q, i);
			}
		}
	}

}
void BFSTraverse(MGraph G)
{
	int v;
	for (v = 0; v < G.vexnum; v++)
		visited[v] = 0;
	for (v = 0; v < G.vexnum; v++)
		if (!visited[v])
		{
			cout << "{";
			BFS(G, v);
			cout <<"}";
		}
}
int main()
{
	MGraph G;
	cout<<"---------------图的深度优先遍历和广度优先遍历测试-----------------\n"; 
	cout<<"第1行输入2个整数n m，分别表示顶点数和边数，空格分割\n"
       <<"后面m行，每行输入边的两个顶点编号，空格分割\n";
	CreateUDG(G);
	cout<<"深度优先遍历结果如下：\n"; 
	DFSTraverse(G);
	cout << endl;
	cout<<"广度优先遍历结果如下；\n";
	BFSTraverse(G);
	cout << endl;
	return 0;
}


