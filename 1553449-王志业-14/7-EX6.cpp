#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

#define ERROR - 1
#define OK  1
#define TRUE  1
#define FALSE  0
#define OVERFLOW -1

#define MAX_VERTEX_NUM 20    //最大顶点个数
typedef int VRType;
typedef int VertexType;
typedef int Status;

typedef enum {
	DG = 1,  // 有向图
	DN,  // 有向网(带权有向图)
	UDG, // 无向图
	UDN  // 无向网(带权无向图)
} GraphKind;  //DG、DN、UDG、UDN是整型值

typedef struct ArcCell {
	VRType adj; //边/弧的值(边：0/1 弧：权值)
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct ArcNode {     //邻接表结点
	int adjvex;  //邻接顶点的序号
	struct ArcNode *nextarc;  //指向下一条边/弧的指针
}ArcNode;
typedef struct VNode {       //邻接表头结点
	int data;   //定点信息
	ArcNode *firstarc;  //指向第1条边/弧的指针
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {
	VertexType vexs[MAX_VERTEX_NUM]; //顶点信息
	AdjMatrix arcs;    //邻接矩阵(二维数组表示边/弧)
	AdjList vertices;  //（邻接表），一维数组，存放所有头结点
	int vexnum, arcnum;//顶点数量、边/弧的数量
	GraphKind kind;    //图的类型，4种之一
} MGraph;

int LocateVex(MGraph G, VertexType v) {
	int i;
	for (i = 0; i < G.vexnum; i++)
		if (v == G.vexs[i])
			return i;
	exit(1);
}
int CreatDN(MGraph &G) {
	int v1, v2;   //两个顶点
	int w;  //权重
	int i, j;
	ArcNode *p;
	cin >> G.vexnum >> G.arcnum;   //读入顶点数、边数,出发点编号
	for (i = 0; i < G.vexnum; i++) {
		G.vexs[i] = i + 1;     //顶点
		G.vertices[i].firstarc = NULL;
	}
	for (i = 0; i < G.vexnum; i++)      //初始化邻接矩阵
		for (j = 0; j < G.vexnum; j++) {
			if (i == j)
				G.arcs[i][j].adj = 0;
			else
				G.arcs[i][j].adj = 2147483647;   //边
		}
	for (int k = 0; k < G.arcnum; k++) {
		cin >> v1 >> v2 >> w;
		i = LocateVex(G, v1);    //查找v1,v2对应的下标
		j = LocateVex(G, v2);
		G.arcs[i][j].adj = w;  //赋权值

		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = j;
		p->nextarc = G.vertices[i].firstarc;
		G.vertices[i].firstarc = p;
	}
	return OK;    ///返回出发点编号
}

//建立邻接表（在邻接矩阵的基础上）
Status CreatAdjList(MGraph &G) {
	int i, j;
	ArcNode *p;
	for (i = 0; i < G.vexnum; i++) {
		G.vertices[i].data = i;
		G.vertices[i].firstarc = NULL;
		for (j = G.vexnum - 1; j >= 0; j--) {
			if (G.arcs[i][j].adj != 0 && G.arcs[i][j].adj != 2147483647) {
				p = (ArcNode*)malloc(sizeof(ArcNode));
				p->adjvex = j;
				p->nextarc = G.vertices[i].firstarc;
				G.vertices[i].firstarc = p;
			}
		}
	}
	return OK;
}
typedef int SElemType;
#define STACK_INIT_SIZE   100  //定义顺序栈的初始空间大小
#define STACKINCREMENT    10   //空间不够，每次增加10个空间

typedef struct {
	SElemType *base;   //存放栈底位置（申请空间的首地址）
	SElemType *top;    //栈顶指针，指向栈顶元素的下一个元素
	int stacksize;     //当前分配的元素的个数
} SqStack;

//初始化栈
Status InitStack(SqStack *S)
{
	S->base = (SElemType *)malloc(
		STACK_INIT_SIZE*sizeof(SElemType));
	if (S->base == NULL)
		exit(OVERFLOW);

	S->top = S->base;  //初始栈为空，栈顶栈底指向同一个地址
	S->stacksize = STACK_INIT_SIZE; //设置栈的初始大小

	return OK;
}

//元素入栈
Status Push(SqStack *S, SElemType e)
{
	if (S->top - S->base >= S->stacksize) {    //栈已满，扩充空间
		S->base = (SElemType *)realloc(S->base, (S->stacksize + STACKINCREMENT)*sizeof(SElemType));
		if (S->base == NULL)
			return OVERFLOW;
		S->top = S->base + S->stacksize;  //扩充空间后S->base的值可能会变，重新校正S->top
		S->stacksize += STACKINCREMENT;
	}
	*(S->top) = e;
	S->top++;
	return OK;
}

//元素出栈
Status Pop(SqStack *S, SElemType *e)
{
	int len;
	if (S->top == S->base)
		return ERROR;     //空栈
	--S->top;
	*e = *(S->top);
	len = S->top - S->base;
	if (S->stacksize > STACK_INIT_SIZE &&S->stacksize - len >= STACKINCREMENT) {
		S->base = (SElemType *)realloc(S->base, (S->stacksize - STACKINCREMENT) * sizeof(SElemType));
		if (S->base == NULL) return OVERFLOW;
		S->top = S->base + len; //若S->base改变则修正S->top的值 
		S->stacksize -= STACKINCREMENT;
	}
	return OK;
}
//判断栈是否为空
Status StackEmpty(SqStack S)
{
	if (S.top == S.base)
		return TRUE;
	else
		return FALSE;
}
//删除栈
Status DestroyStack(SqStack *S)
{
	if (S->base)
		free(S->base);
	S->top = NULL;
	S->stacksize = 0;
	return OK;
}
void FindInDegree(MGraph G, int *indegree) {
	int i;
	ArcNode *p;
	for (i = 0; i < G.vexnum; i++)
		indegree[i] = 0;
	for (i = 0; i < G.vexnum; i++) {
		p = G.vertices[i].firstarc;
		while (p) {
			indegree[p->adjvex]++;
			p = p->nextarc;
		}
	}
}
int ve[MAX_VERTEX_NUM];
int TopologicalOrder(MGraph G, SqStack &T) {
	SqStack S;
	int indegree[MAX_VERTEX_NUM];
	int i, j, k;
	ArcNode *p;
	FindInDegree(G, indegree);
	InitStack(&S);   //建0入度栈
	for (i = 0; i < G.vexnum; i++)
		if (!indegree[i])
			Push(&S, i);

	InitStack(&T);    //初始化用于存放拓扑排序序列的栈
	int count = 0;

	for (i = 0; i < G.vexnum; i++)
		ve[i] = 0;
	while (!StackEmpty(S)) {
		Pop(&S, &j);   //从0入度栈出栈
		Push(&T, j);   //进拓扑排序结果栈
		count++;
		for (p = G.vertices[j].firstarc; p; p = p->nextarc) {
			k = p->adjvex;    //k为邻接点的下标
			if (--indegree[k] == 0)
				Push(&S, k);
			if (ve[j] + G.arcs[j][k].adj>ve[k])
				ve[k] = ve[j] + G.arcs[j][k].adj;
		}
	}
	DestroyStack(&S);
	if (count < G.vexnum)
		return ERROR;
	else
		return OK;
}
Status CriticalPath(MGraph G) {
	SqStack T;
	ArcNode *p;
	int vl[MAX_VERTEX_NUM];
	if (!TopologicalOrder(G, T))
		return ERROR;
	for (int i = 0; i < G.vexnum; i++)
		vl[i] = ve[G.vexnum - 1];
	cout << ve[G.vexnum - 1] << endl;
	int j, k, dut, ee, el;
	while (!StackEmpty(T))
		for (Pop(&T, &j), p = G.vertices[j].firstarc; p; p = p->nextarc) {
			k = p->adjvex;
			dut = G.arcs[j][k].adj;   //取边的权值
			if (vl[k] - dut < vl[j])
				vl[j] = vl[k] - dut;
		}
	for (j = 0; j < G.vexnum; j++)
		for (p = G.vertices[j].firstarc; p; p = p->nextarc) {
			k = p->adjvex;
			dut = G.arcs[j][k].adj;
			ee = ve[j];
			el = vl[k] - dut;
			if (ee == el) {  //判断是否关键活动
				cout << j + 1 << "->" << k + 1 << endl;
			}
		}
	DestroyStack(&T);
	return OK;
}
int main()
{
	MGraph G;
	cout<<"---------------图的关键路径测试-----------------\n"; 
	cout<<"第一行包含两个整数n、m，其中n表示顶点数，m表示任务数。顶点按1~n编号。（n<=100)\n"
        <<"接下来m行表示m个任务，每行包含三个正整数ui、vi、wi，分别表示该任务开始和完成的顶点序号，及任务完成的时间。\n"
        <<"整数之间用空格表示。\n";
	CreatDN(G);
	cout<<"关键路径为（若有环则输出为0）\n";
	if (CriticalPath(G) == 0)
		cout << 0 << endl;
	return 0;
}
