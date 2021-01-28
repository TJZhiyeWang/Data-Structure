#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;


#define TRUE 1
#define FALSE 0
#define ERROR 0
#define OK 1
#define INFEASIBLE -1
#define OVERFLOW -2

#define code 37
typedef int Status;

typedef long long ElemType;
typedef long long KeyType;

typedef struct
{
	ElemType *elem;
	int count;
	int size;
}HashTable;

Status InitHashTable(HashTable &H, int p)
{
	H.elem = (ElemType*)malloc(sizeof(ElemType)*p);
	for (int i = 0; i < p; i++)
	{
		H.elem[i] = -1;
	}
	if (!H.elem)
		return OVERFLOW;
	H.count = 0;
	H.size = p;
	return OK;
}

Status InsertHashTable(HashTable &H, KeyType e)
{
	int i = e%H.size;
	if (H.count >= H.size)
		return ERROR;
	while (H.elem[i] != -1)
	{
		i++;
		i %= H.size;
	}
	H.elem[i] = e;
	H.count++;
	return OK;
}
KeyType HashCode(string name,HashTable H)
{
	KeyType key = 0;
	int i = name.length()-1,j=0;
	while (i>=0)
	{
		key += pow(code, j)*(int)name[i];
		j++;
		i--;
	}
	
	return key;
}
Status SearchHash(HashTable H, KeyType key, int &c,int &p)
{
	p = key%H.size;
	while (H.elem[p] != -1 && H.elem[p] != key)
	{
        p++;
		c++;
		p %= H.size;
		if (p == key%H.size)
			return ERROR;
	}
	return OK;
}
int main()
{
	HashTable H;
	int n , p,i;
	cout<<"-----------------��ϣ����ʵ��--------------------\n";
	cout<<"��1������2������N(<=100)��P(>=2N����С����)���ֱ�Ϊ������ؼ���������ɢ�б�ĳ��ȡ�\n"
        <<"��2�и���N���ַ�����ÿһ���ַ�����ʾһ������\n";
	cin >> n >> p;
	InitHashTable(H, p);
	string name[100];
	for (i = 0; i < n; i++)
	{
		cin >> name[i];
		InsertHashTable(H, HashCode(name[i],H));
	}
	int c;
	cout<<"ÿ���ַ������ַ�����ɢ���е�λ��"<<endl;
	for (i = 0; i < n; i++)
	{
		SearchHash(H, HashCode(name[i],H), c, p);
		cout <<name[i]<<" "<< p << " ";
	}
	cout << endl;
	cout<<"ÿ���ַ������ҵĴ���"<<endl;
	for (i = 0; i < n; i++)
	{
		c = 1;
		SearchHash(H, HashCode(name[i],H), c, p);
		cout << c << " ";
	}
	return 0;
}
