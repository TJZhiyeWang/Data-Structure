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
Status CreateUDN(MGraph &G)
{
	scanf("%d%d", &G.vexnum, &G.arcnum);
	int i, j;
	for (i = 0; i < G.vexnum; i++)
		G.vexs[i] = i + 1;
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
		cin >> v1 >> v2 >> w;
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		G.arcs[i][j].adj = w;
		G.arcs[j][i].adj = w;
	}
	return OK;
}

struct HELP_Array
{
	VertexType adjvex;
	VRType lowcost;
}closedge[NUM];
int minimum(HELP_Array closedge[])
{
	int i = 0, k;
	while (closedge[i].lowcost == 0 && i < NUM)
	{
		i++;
	}
	k = i;
	for (i = 0; i < NUM; i++)
	{
		if (closedge[i].lowcost != 0 && closedge[i].lowcost < closedge[k].lowcost)
			k = i;
	}
	return k;
}

Status print_closedge(HELP_Array closedge[], int n)
{
	for (int i = 0; i < n; i++)
		cout << closedge[i].lowcost;
	cout << endl;
	return OK;
}
Status closedge_zero(HELP_Array closedge[], int n)
{
	int sum=0;
	for (int i = 0; i < n; i++)
		sum += closedge[i].lowcost;
	if (sum == 0)
		return 1;
	else
		return 0;
}
VRType MiniSpanTree_PRIM(MGraph G, VertexType v)
{
	VRType sum = 0;
	int k;
	k = LocateVex(G, v);
	int i, j;
	for (i = 0; i < G.vexnum; i++)
	{
		if (i != k)
			closedge[i] = { v,G.arcs[k][i].adj };
		else
			closedge[i] = { v,0 };
	}//初始化
	for (i = 1; i < G.vexnum; i++)
	{
		k = minimum(closedge);
		sum += closedge[k].lowcost;
		closedge[k].lowcost = 0;
		for (j = 0; j < G.vexnum; j++)
			if (G.arcs[k][j].adj&&G.arcs[k][j].adj < closedge[j].lowcost)
				closedge[j] = { G.vexs[k],G.arcs[k][j].adj };
		if (i < G.vexnum - 1 && closedge_zero(closedge, G.vexnum))
			return -1;
	}
	return sum;

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
	cout<<"---------------图的最小生成树测试-----------------\n"; 
	cout<<"第一行包含两个整数n、m，表示该图共有n个结点和m条无向边。（n<=1000，m<=3000）\n"
        <<"接下来m行每行包含三个整数ui、vi、wi，表示有一条长度为wi的无向边连接结点ui、vi。\n"
        <<"顶点编号从1开始\n";
	CreateUDN(G);
	cout<<"最小生成树长度之和为：\n";
	cout << MiniSpanTree_PRIM(G,1);
	return 0;

}
