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
typedef char VertexType;
typedef enum { DG = 1, DN = 2, UDG = 3, UDN = 4 } GraphKind;
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
	GraphKind kind;
}MGraph;
Status CreateDG(MGraph &G);
Status CreateDN(MGraph &G);
Status CreateUDG(MGraph &G);
Status CreateUDN(MGraph &G);
Status CreateGraph(MGraph &G)
{
	scanf("%d", &G.kind);
	switch (G.kind)
	{
		case DG:return CreateDG(G);
		case DN:return CreateDN(G);
		case UDG:return CreateUDG(G);
		case UDN:return CreateUDN(G);
		default:return ERROR;
	}
}
int LocateVex(MGraph G, VertexType v)
{
	int i = 0;
	while (G.vexs[i] != v)
	{
		i++;
	}
	return i;
}
Status CreateUDN(MGraph &G)
{
	scanf("%d%d", &G.vexnum, &G.arcnum);
	int i, j;
	for (i = 0; i < G.vexnum; i++)
		cin >> G.vexs[i];
	for (i = 0; i < G.vexnum; i++)
	{
		for (j = 0; j < G.vexnum; j++)
		{
			G.arcs[i][j] = { 0,NULL };
		}
	}
	int k;
	VertexType v1, v2;
	VRType w;
	for (k = 0; k < G.arcnum; k++)
	{
		cin >> v1 >> v2>> w;
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		G.arcs[i][j].adj = w;
		G.arcs[j][i].adj = w;
	}
	return OK;
}

Status CreateDN(MGraph &G)
{
	scanf("%d%d", &G.vexnum, &G.arcnum);
	int i, j;
	for (i = 0; i < G.vexnum; i++)
		cin >> G.vexs[i];
	for (i = 0; i < G.vexnum; i++)
	{
		for (j = 0; j < G.vexnum; j++)
		{
			G.arcs[i][j] = { 0,NULL };
		}
	}
	int k;
	VertexType v1, v2;
	VRType w;
	for (k = 0; k < G.arcnum; k++)
	{
		cin>>v1>>v2>>w;
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		G.arcs[i][j].adj = w;
	}
	return OK;
}

Status CreateDG(MGraph &G)
{
	scanf("%d%d", &G.vexnum, &G.arcnum);
	int i, j;
	for (i = 0; i < G.vexnum; i++)
		cin >> G.vexs[i];
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
		cin>>v1>>v2;
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		G.arcs[i][j].adj = w;
	}
	return OK;
}

Status CreateUDG(MGraph &G)
{
	scanf("%d%d", &G.vexnum, &G.arcnum);
	int i, j;
	for (i = 0; i < G.vexnum; i++)
		cin >> G.vexs[i];
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

typedef struct ArcNode
{
	int adjvex;
	struct ArcNode *nextarc;
	InfoType *Info;
}ArcNode;
typedef struct VNode
{
	VertexType data;
	ArcNode *firstarc;
}VNode, AdjList[NUM];
typedef struct
{
	AdjList vertices;
	int vexnum;
	int arcnum;
	int kind;
}ALGraph;

Status matrix2ALGraph_DG(MGraph G, ALGraph &ALG);
Status matrix2ALGraph_DN(MGraph G, ALGraph &ALG);
Status matrix2ALGraph_UDG(MGraph G, ALGraph &ALG);
Status matrix2ALGraph_UDN(MGraph G, ALGraph &ALG);
Status matrix2ALGraph(MGraph G, ALGraph &ALG)
{
	ALG.kind = G.kind;
	ALG.arcnum = G.arcnum;
	ALG.vexnum = G.vexnum;
	switch (G.kind)
	{
		case DG:return matrix2ALGraph_DG(G, ALG);
		case DN:return matrix2ALGraph_DN(G, ALG);
		case UDG:return matrix2ALGraph_UDG(G, ALG);
		case UDN:return matrix2ALGraph_UDN(G, ALG);
		default:return ERROR;
	}
}
Status matrix2ALGraph_DG(MGraph G, ALGraph &ALG)
{
	ArcNode *p = NULL;
	int i, j;
	for (i = 0; i < ALG.vexnum; i++)
	{
		ALG.vertices[i].data = G.vexs[i];
		ALG.vertices[i].firstarc = NULL;
		for (j = 0; j < ALG.vexnum; j++)
		{
			if (G.arcs[i][j].adj == 1)
			{
				p = (ArcNode*)malloc(sizeof(ArcNode));
				p->nextarc = ALG.vertices[i].firstarc;
				ALG.vertices[i].firstarc = p;
				p->adjvex = j;
				p->Info = NULL;
			}
		}
	}
	return OK;
}
Status matrix2ALGraph_DN(MGraph G, ALGraph &ALG)
{
	ArcNode *p = NULL;
	int i, j;
	for (i = 0; i < ALG.vexnum; i++)
	{
		ALG.vertices[i].data = G.vexs[i];
		ALG.vertices[i].firstarc = NULL;
		for (j = 0; j < ALG.vexnum; j++)
		{
			if (G.arcs[i][j].adj)
			{
				p = (ArcNode*)malloc(sizeof(ArcNode));
				p->nextarc = ALG.vertices[i].firstarc;
				ALG.vertices[i].firstarc = p;
				p->adjvex = j;
				p->Info = (int *)malloc(sizeof(int));
				*(p->Info) = G.arcs[i][j].adj;
			}
		}
	}
	return OK;
}
Status matrix2ALGraph_UDG(MGraph G, ALGraph &ALG)
{
	ArcNode *p = NULL;
	int i, j;
	for (i = 0; i < ALG.vexnum; i++)
	{
		ALG.vertices[i].data = G.vexs[i];
		ALG.vertices[i].firstarc = NULL;
		for (j = 0; j < ALG.vexnum; j++)
		{
			if (G.arcs[i][j].adj == 1)
			{
				p = (ArcNode*)malloc(sizeof(ArcNode));
				p->nextarc = ALG.vertices[i].firstarc;
				ALG.vertices[i].firstarc = p;
				p->adjvex = j;
				p->Info = NULL;
			}
		}
	}
	return OK;
}
Status matrix2ALGraph_UDN(MGraph G, ALGraph &ALG)
{
	ArcNode *p = NULL;
	int i, j;
	for (i = 0; i < ALG.vexnum; i++)
	{
		ALG.vertices[i].data = G.vexs[i];
		ALG.vertices[i].firstarc = NULL;
		for (j = 0; j < ALG.vexnum; j++)
		{
			if (G.arcs[i][j].adj)
			{
				p = (ArcNode*)malloc(sizeof(ArcNode));
				p->nextarc = ALG.vertices[i].firstarc;
				ALG.vertices[i].firstarc = p;
				p->adjvex = j;
				p->Info = (int *)malloc(sizeof(int));
				*(p->Info) = G.arcs[i][j].adj;
			}
		}
	}
	return OK;
}
Status print_MGraph(MGraph G)
{
	int i,j;
	for (i = 0; i < G.vexnum; i++)
		cout << G.vexs[i] << " ";
	cout << endl;
	for (i = 0; i < G.vexnum; i++)
	{
		for (j = 0; j < G.vexnum; j++)
			cout << "   " << G.arcs[i][j].adj;
		cout << endl;
	}
	return OK;
}
Status print_ALGraph_UorDG(ALGraph ALG)
{
	int i;
	ArcNode *p = NULL;
	for (i = 0; i < ALG.vexnum; i++)
	{
		cout << ALG.vertices[i].data << "-->";
		p = ALG.vertices[i].firstarc;
		while (p)
		{
			cout << p->adjvex << " ";
			p = p->nextarc;
		}
		cout << endl;
	}
	return OK;
}
Status print_ALGraph_UorDN(ALGraph ALG)
{
	int i;
	ArcNode *p = NULL;
	for (i = 0; i < ALG.vexnum; i++)
	{
		cout << ALG.vertices[i].data << "-->";
		p = ALG.vertices[i].firstarc;
		while (p)
		{
			cout << p->adjvex <<","<<*(p->Info)<<" ";
			p = p->nextarc;
		}
		cout << endl;
	}
	return OK;
}
Status print_ALGraph(ALGraph ALG)
{
	switch (ALG.kind)
	{
		case DG:
		case UDG:return print_ALGraph_UorDG(ALG);
		case DN:
		case UDN:return print_ALGraph_UorDN(ALG);
		default:return ERROR;
	}
}
int main()
{
	MGraph G;
	ALGraph ALG;
	cout<<"-------------------图的存储结构测试----------------------\n"; 
	cout<<"第1行输入一个数字1~4，1为有向图,2为有向网,3为无向图,4为无向网\n"
        <<"第2行输入2个整数n m，分别表示顶点数和边数，空格分割\n"
          <<"第3行为n个字符的序列，一个字符表示一个顶点\n"
           <<"后面m行，若前面选择的是图，则每行输入边的两个顶点字符，空格分割，若是网，则每行输入弧的两个顶点字符和弧的权值，空格分割"; 
	cout<<endl<<"请按规则输入"<<endl;
	CreateGraph(G);
	cout<<"该图的邻接矩阵和邻接表分别表示为"<<endl;
	print_MGraph(G);
	matrix2ALGraph(G, ALG);
	
	print_ALGraph(ALG);
	return 0;
}
