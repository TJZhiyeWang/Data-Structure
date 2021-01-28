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

#define MAX_VERTEX_NUM 20    //��󶥵����
typedef int VRType;
typedef int VertexType;
typedef int Status;

typedef enum {
	DG = 1,  // ����ͼ
	DN,  // ������(��Ȩ����ͼ)
	UDG, // ����ͼ
	UDN  // ������(��Ȩ����ͼ)
} GraphKind;  //DG��DN��UDG��UDN������ֵ

typedef struct ArcCell {
	VRType adj; //��/����ֵ(�ߣ�0/1 ����Ȩֵ)
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct ArcNode {     //�ڽӱ���
	int adjvex;  //�ڽӶ�������
	struct ArcNode *nextarc;  //ָ����һ����/����ָ��
}ArcNode;
typedef struct VNode {       //�ڽӱ�ͷ���
	int data;   //������Ϣ
	ArcNode *firstarc;  //ָ���1����/����ָ��
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {
	VertexType vexs[MAX_VERTEX_NUM]; //������Ϣ
	AdjMatrix arcs;    //�ڽӾ���(��ά�����ʾ��/��)
	AdjList vertices;  //���ڽӱ���һά���飬�������ͷ���
	int vexnum, arcnum;//������������/��������
	GraphKind kind;    //ͼ�����ͣ�4��֮һ
} MGraph;

int LocateVex(MGraph G, VertexType v) {
	int i;
	for (i = 0; i < G.vexnum; i++)
		if (v == G.vexs[i])
			return i;
	exit(1);
}
int CreatDN(MGraph &G) {
	int v1, v2;   //��������
	int w;  //Ȩ��
	int i, j;
	ArcNode *p;
	cin >> G.vexnum >> G.arcnum;   //���붥����������,��������
	for (i = 0; i < G.vexnum; i++) {
		G.vexs[i] = i + 1;     //����
		G.vertices[i].firstarc = NULL;
	}
	for (i = 0; i < G.vexnum; i++)      //��ʼ���ڽӾ���
		for (j = 0; j < G.vexnum; j++) {
			if (i == j)
				G.arcs[i][j].adj = 0;
			else
				G.arcs[i][j].adj = 2147483647;   //��
		}
	for (int k = 0; k < G.arcnum; k++) {
		cin >> v1 >> v2 >> w;
		i = LocateVex(G, v1);    //����v1,v2��Ӧ���±�
		j = LocateVex(G, v2);
		G.arcs[i][j].adj = w;  //��Ȩֵ

		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = j;
		p->nextarc = G.vertices[i].firstarc;
		G.vertices[i].firstarc = p;
	}
	return OK;    ///���س�������
}

//�����ڽӱ����ڽӾ���Ļ����ϣ�
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
#define STACK_INIT_SIZE   100  //����˳��ջ�ĳ�ʼ�ռ��С
#define STACKINCREMENT    10   //�ռ䲻����ÿ������10���ռ�

typedef struct {
	SElemType *base;   //���ջ��λ�ã�����ռ���׵�ַ��
	SElemType *top;    //ջ��ָ�룬ָ��ջ��Ԫ�ص���һ��Ԫ��
	int stacksize;     //��ǰ�����Ԫ�صĸ���
} SqStack;

//��ʼ��ջ
Status InitStack(SqStack *S)
{
	S->base = (SElemType *)malloc(
		STACK_INIT_SIZE*sizeof(SElemType));
	if (S->base == NULL)
		exit(OVERFLOW);

	S->top = S->base;  //��ʼջΪ�գ�ջ��ջ��ָ��ͬһ����ַ
	S->stacksize = STACK_INIT_SIZE; //����ջ�ĳ�ʼ��С

	return OK;
}

//Ԫ����ջ
Status Push(SqStack *S, SElemType e)
{
	if (S->top - S->base >= S->stacksize) {    //ջ����������ռ�
		S->base = (SElemType *)realloc(S->base, (S->stacksize + STACKINCREMENT)*sizeof(SElemType));
		if (S->base == NULL)
			return OVERFLOW;
		S->top = S->base + S->stacksize;  //����ռ��S->base��ֵ���ܻ�䣬����У��S->top
		S->stacksize += STACKINCREMENT;
	}
	*(S->top) = e;
	S->top++;
	return OK;
}

//Ԫ�س�ջ
Status Pop(SqStack *S, SElemType *e)
{
	int len;
	if (S->top == S->base)
		return ERROR;     //��ջ
	--S->top;
	*e = *(S->top);
	len = S->top - S->base;
	if (S->stacksize > STACK_INIT_SIZE &&S->stacksize - len >= STACKINCREMENT) {
		S->base = (SElemType *)realloc(S->base, (S->stacksize - STACKINCREMENT) * sizeof(SElemType));
		if (S->base == NULL) return OVERFLOW;
		S->top = S->base + len; //��S->base�ı�������S->top��ֵ 
		S->stacksize -= STACKINCREMENT;
	}
	return OK;
}
//�ж�ջ�Ƿ�Ϊ��
Status StackEmpty(SqStack S)
{
	if (S.top == S.base)
		return TRUE;
	else
		return FALSE;
}
//ɾ��ջ
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
	InitStack(&S);   //��0���ջ
	for (i = 0; i < G.vexnum; i++)
		if (!indegree[i])
			Push(&S, i);

	InitStack(&T);    //��ʼ�����ڴ�������������е�ջ
	int count = 0;

	for (i = 0; i < G.vexnum; i++)
		ve[i] = 0;
	while (!StackEmpty(S)) {
		Pop(&S, &j);   //��0���ջ��ջ
		Push(&T, j);   //������������ջ
		count++;
		for (p = G.vertices[j].firstarc; p; p = p->nextarc) {
			k = p->adjvex;    //kΪ�ڽӵ���±�
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
			dut = G.arcs[j][k].adj;   //ȡ�ߵ�Ȩֵ
			if (vl[k] - dut < vl[j])
				vl[j] = vl[k] - dut;
		}
	for (j = 0; j < G.vexnum; j++)
		for (p = G.vertices[j].firstarc; p; p = p->nextarc) {
			k = p->adjvex;
			dut = G.arcs[j][k].adj;
			ee = ve[j];
			el = vl[k] - dut;
			if (ee == el) {  //�ж��Ƿ�ؼ��
				cout << j + 1 << "->" << k + 1 << endl;
			}
		}
	DestroyStack(&T);
	return OK;
}
int main()
{
	MGraph G;
	cout<<"---------------ͼ�Ĺؼ�·������-----------------\n"; 
	cout<<"��һ�а�����������n��m������n��ʾ��������m��ʾ�����������㰴1~n��š���n<=100)\n"
        <<"������m�б�ʾm������ÿ�а�������������ui��vi��wi���ֱ��ʾ������ʼ����ɵĶ�����ţ���������ɵ�ʱ�䡣\n"
        <<"����֮���ÿո��ʾ��\n";
	CreatDN(G);
	cout<<"�ؼ�·��Ϊ�����л������Ϊ0��\n";
	if (CriticalPath(G) == 0)
		cout << 0 << endl;
	return 0;
}
