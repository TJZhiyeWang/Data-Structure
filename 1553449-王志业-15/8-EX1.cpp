#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <string>
using namespace std;


#define TRUE 1
#define FALSE 0
#define ERROR 0
#define OK 1
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
typedef int ElemType;
typedef int KeyType;
typedef struct SSTable
{
	ElemType *elem;
	int n;
};
Status Init_Table(SSTable &ST)
{
	cin >> ST.n;
	ST.elem = (ElemType*)malloc(ST.n*sizeof(ElemType));
	for (int i = 0; i < ST.n; i++)
	{
		cin >> ST.elem[i];
	}
	return OK;
}
Status Search_Bin(SSTable ST, KeyType key)
{
	int low = 0, high = ST.n - 1, mid;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (key == ST.elem[mid])
		{
			while (ST.elem[--mid] == key);
			return ++mid;
		}

		else if (key < ST.elem[mid])
			high = mid - 1;
		else
			low = mid + 1;
	}
	return -1;
}

int main()
{
	SSTable ST;
	cout<<"-----------------���ַ�����ʵ��--------------------\n";
	cout<< "��1������һ��������n,��ʾ���ұ�ĳ���\n"
         <<"��2������n���������е��������Կո�ָ�\n";

    Init_Table(ST);
    
    while(1)
    {
    	cout<<"���ұ��ѽ���������1������ΪҪ���ҵ�����x\n,���ҵ������λ�ã��Ҳ������-1\n";
		KeyType key;
	    cin >> key;
	    cout << Search_Bin(ST, key);
	    cout<<"\n��q�˳����ң���������������\n";
	    if(_getch()=='q')
	        break;
	}
	return 0;
}
    

