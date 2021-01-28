#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>

#define limit 2147483647
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

VertexType CreateDN(MGraph &G)
{
	VertexType s;
	scanf("%d%d%d", &G.vexnum, &G.arcnum,&s);
	int i, j;
	for (i = 0; i < G.vexnum; i++)
		G.vexs[i]=i+1;
	for (i = 0; i < G.vexnum; i++)
	{
		for (j = 0; j < G.vexnum; j++)
		{
			G.arcs[i][j] = { limit,NULL };
		}
	}
	int k;
	VertexType v1, v2;
	VRType w;
	for (k = 0; k < G.arcnum; k++)
	{
		cin >> v1 >> v2 >> w;
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		G.arcs[i][j].adj = w;
	}
	return s;
}
typedef struct s
{
	VRType PathLenth;
	VertexType vexs;
}ShortPathTable[NUM];

bool final[NUM];
Status ShortestPath_DIJ(MGraph G, VertexType v0, ShortPathTable &D)
{
	int i, j,k;
	for (i = 0; i < G.vexnum; i++)
	{
		final[i] = false;
		D[i].PathLenth = G.arcs[LocateVex(G, v0)][i].adj;
		D[i].vexs = G.vexs[i];
	}
	D[LocateVex(G, v0)].PathLenth = 0;
	final[LocateVex(G, v0)] = true;
	for (i = 1; i < G.vexnum; i++)
	{
		VRType min = limit;
		for (j = 0; j < G.vexnum; j++)
		{
			if(!final[j])
				if (D[j].PathLenth <= min)
				{
					k = j;
					min = D[j].PathLenth;
				}
		}
		final[k] = true;
		for (j = 0; j < G.vexnum; j++)
		{
			if (!final[j] && (G.arcs[k][j].adj + min)>0&& ((G.arcs[k][j].adj + min) < D[j].PathLenth))
				D[j].PathLenth = G.arcs[k][j].adj + min;
		}
		
	}
}
Status print_MGraph(MGraph G)
{
	int i, j;
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
int main()
{
	MGraph G;
	VertexType s;
	ShortPathTable D;
	cout<<"---------------图的最短路径测试-----------------\n"; 
	cout<<"第一行包含三个整数n、m、s，分别表示点的个数、有向边的个数、出发点的编号。\n"
        <<"接下来M行每行包含三个整数ui、vi、wi，分别表示第i条有向边的出发点、目标点和长度。\n"
        <<"顶点编号从1开始。\n";
	s = CreateDN(G);
	ShortestPath_DIJ(G, s, D);
	cout<<"最短路径为:"<<endl;
	for (int i = 0; i < G.vexnum; i++)
		cout << D[i].PathLenth << " ";
	return 0;
}
