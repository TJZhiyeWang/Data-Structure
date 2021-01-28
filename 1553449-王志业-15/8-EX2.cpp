#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <iomanip>
using namespace std;


#define TRUE 1
#define FALSE 0
#define ERROR 0
#define OK 1
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
typedef int ElemType;

typedef int ElemType;
typedef int KeyType;

typedef  struct  BiTNode {
	ElemType  data;
	struct  BiTNode  *lchild, *rchild;
} BiTNode, *BiTree;

Status InsertDSTable(BiTree &DT, ElemType e);
Status InitDSTable(BiTree &DT,int n) //����һ���յĶ�̬���ұ�DT
{
	int i;
	ElemType e;
	for (i = 0; i < n; i++)
	{
		
		cin >> e;
		InsertDSTable(DT, e);
	}
	return OK;
}

Status SearchDSTable(BiTree DT, KeyType key)//���ҹؼ���Ϊkey������Ԫ��
{
		BiTree  p, q=NULL,s;
		p = DT;
		while (p)
		{
			if (p->data == key)
				return OK;
			else if (p->data > key)
			{
				q = p;
				p = p->lchild;
			}
			else
			{
				q = p;
				p = p->rchild;
			}
		}
		s = (BiTNode *)malloc(sizeof(BiTNode));
		s->data = key;
		s->lchild = NULL;
		s->rchild = NULL;
		if (!DT)
			DT = s;
		else  if (q->data > key)
			q->lchild = s;
		else
			q->rchild = s;
		return ERROR;
}
Status InsertDSTable(BiTree &DT, ElemType e)
{
	BiTree p, q=NULL, s;
	p = DT;
	while (p)
	{
		if (p->data == e)
			return ERROR;
		else if (p->data > e)
		{
			q = p;
			p = p->lchild;
		}
		else
		{
			q = p;
			p = p->rchild;
		}
	}
	s = (BiTNode *)malloc(sizeof(BiTNode));
	s->data = e;  
	s->lchild = NULL;
	s->rchild = NULL;
	if (!DT) 
		DT = s;
	else  if (q->data > e) 
		q->lchild = s;
	else 
		q->rchild = s;
	return OK;
}
void delNode(BiTree &T, BiTree p, BiTree f)
{
	BiTree s, q;
	int tag;  tag = 0;
	if (!p->lchild) s = p->rchild; //���Ӳ�����
	else if (!p->rchild) s = p->lchild; //�Һ��Ӳ�����
	else {
		q = p; s = p->lchild;
		while (s->rchild) { q = s; s = s->rchild; }
		p->data = s->data;
		if (q == p) q->lchild = s->lchild;
		else q->rchild = s->lchild;
		free(s);
		tag = 1;
	} //���Һ��Ӷ�����
	if (!tag) {
		if (!f) T = s;
		else if (f->lchild == p) f->lchild = s;
		else f->rchild = s;
		free (p);
		return;
	}
}
Status DeleteDSTable(BiTree &DT, KeyType key)
{
	BiTree p, f;
	p = DT; f = NULL;
	while (p)
	{
		if (p->data == key) 
		{
			delNode(DT, p, f); 
			return OK;
		}
		else if (p->data > key)
		{ 
			f = p; 
			p = p->lchild; 
		}
		else 
		{ 
			f = p; 
			p = p->rchild; 
		}
	}
	return ERROR;
}
void TraverseDSTable(BiTree DT)
{
	if (DT)
	{
		cout << DT->data << " ";
		TraverseDSTable(DT->lchild);
		
		TraverseDSTable(DT->rchild);
	}
}
int sum = 0;
int dep = 1;
int depth(BiTree DT,int dep)
{
	if (DT)
	{
		if (DT->lchild)
			sum = depth(DT->lchild, dep + 1);
		if (DT->rchild)
			sum = depth(DT->rchild, dep + 1);
	}
	return sum+dep;
}
double Length_of_Search(BiTree DT,int n)
{
	return (double)depth(DT,dep) / n;
}
void PrintBiTree(BiTree T,int n=0)
{
	int i;
	char ch = ' ';
	if (T)
	{
		PrintBiTree(T->rchild, n + 1);
		for (i = 1; i <= n; ++i)
			printf("%5c", ch);
		printf("%d\n", T->data);
		PrintBiTree(T->lchild, n + 1);

	}
}
int main()
{
	BiTree DT=NULL;
	int n;
	cout<<"-----------------��������������ʵ��--------------------\n";
	cout<<"��1��һ������n����ʾ����Ĺؼ��ָ���\n"
        <<"��2��n�����ݣ���ʾ����Ĺؼ���\n"
        <<"��3��1�����ݣ���ʾ��ɾ��������ҵĹؼ���\n";
	cin >> n;
	InitDSTable(DT,n);
	cout<<"���ĽṹΪ"<<endl;
	PrintBiTree(DT);
	KeyType e;
	cin >> e;
	cout << DeleteDSTable(DT, e)<<endl;
	cout<<"ɾ����Ԫ�غ���Ϊ"<<endl;
	PrintBiTree(DT);
	
	cout<<"���Ҹ�Ԫ�ؽ��Ϊ"<<endl;
	cout << SearchDSTable(DT, e)<<endl;
	cout<<"���Ҳ����ٲ����ȥ�Ľ��Ϊ"<<endl;
	 	PrintBiTree(DT);
	cout<<"����������Ϊ"<<endl;
	TraverseDSTable(DT);
	cout << endl;
	cout<<"ƽ�����ҳ���Ϊ"<<endl;
	cout << setprecision(2) << setiosflags(ios::fixed) << Length_of_Search(DT, n);
	return 0;
}
