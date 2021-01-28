/*1553449 ��־ҵ 3��*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>		//malloc/realloc����
#include <conio.h>
#include <cmath>
#define TRUE		1
#define FALSE		0
#define OK		1
#define ERROR		0
#define INFEASIBLE	-1
#define LOVERFLOW	-2		//��Ϊ<math.h>������ OVERFLOW �Ķ��壬��˻�һ��

typedef int Status;

typedef struct polynode
{
	double coef;
	int expn;
	struct polynode *next;
}polynode, *polynomial;

/* ��ʼ�����Ա� */
Status InitList(polynomial *L)
{
	/* ����ͷ���ռ䣬��ֵ��ͷָ�� */
	*L = (polynomial)malloc(sizeof(polynode));
	if (*L == NULL)
		exit(LOVERFLOW);
	(*L)->next = NULL;
	return OK;
}

/* ɾ�����Ա� */
Status DestroyList(polynomial *L)
{
	polynomial q, p = *L; //ָ����Ԫ

						  /* ��������(��ͷ���)�����ͷ� */
	while (p) {    //������Ϊ�գ���ѭ����ִ��
		q = p->next; //ץס�������һ�����
		free(p);
		p = q;
	}
	*L = NULL;	//ͷָ����NULL
	return OK;
}

/* ��ָ����С����������ָ����λ�ò���һ����Ԫ�� */
Status ListInsert(polynomial &L, polynomial e)
{
	polynomial  p = L;	//pָ��ͷ���

						/*�ҵ��ʺϷ�e->expn��λ��*/
	while (p->next) {
		if (p->next->expn > e->expn)
		{
			e->next = p->next;
			p->next = e;
			break;
		}
		if (p->next->expn == e->expn)
		{
			p->next->coef += e->coef;
			break;
		}
		p = p->next;
	}
	if (p->next == NULL)
	{
		e->next = p->next;
		p->next = e;
	}

	return OK;
}

/*����ʽ�鲢������La,Lb�鲢��La*/
Status ListUnion(polynomial *La, polynomial Lb)
{
	polynomial p = (*La)->next, q = Lb->next, pre = *La, temp;
	while (p&&q)
	{
		if (p->expn > q->expn)
		{
			pre->next = q;
			pre = q;
			q = q->next;
		}
		else if (p->expn == q->expn)
		{
			if ((p->coef + q->coef) != 0)
			{
				p->coef = p->coef + q->coef;
				pre->next = p;
				pre = p;
				temp = q;
				q = q->next;
				p = p->next;
				free(temp);
			}
			else
			{
				temp = q;
				q = q->next;
				free(temp);
				temp = p;
				p = p->next;
				free(temp);
			}
		}
		else
		{
			pre->next = p;
			pre = p;
			p = p->next;
		}
	}
	pre->next = p ? p : q;
	return OK;
}
/* �������Ա� */
Status ListTraverse(polynomial L)
{

	polynomial p = L->next;


	while (p)
	{
		printf("%.1f*x^(%d)+", p->coef, p->expn);
		p = p->next;
	}
	printf("\n");
	if (p)
		return ERROR;

	printf("\n");
	return OK;
}
/*������Ԫ�ظ���*/
int Node_count(polynomial L)
{
	int i = 0;
	if (L->next == NULL)
		return 0;
	while (L->next)
	{
		i++;
		L = L->next;
	}
	return i;
}

/*����ʽ�ĳ˷�*/
Status MultiplyPoly(polynomial *La, polynomial *Lb)
{
	polynomial data;
	polynomial pnew = NULL;
	polynomial pa = *La, pb = *Lb;
	InitList(&pnew);
	if (Node_count(*La) == 0 || Node_count(*Lb) == 0)
		return ERROR;
	while (pa->next)
	{
		while (pb->next)
		{
			data = (polynomial)malloc(sizeof(polynode));
			data->coef =pa->next->coef+pb->next->coef;
			data->expn = pa->next->expn + pb->next->expn;
			ListInsert(pnew, data);
			pb = pb->next;
		}
		pb = *Lb;
		pa = pa->next;
	}
	DestroyList(La);
	DestroyList(Lb);
	*La = pnew;
	return OK;
}
Status inverse(polynomial &L)
{
	polynomial p = L->next;
	while (p)
	{
		p->coef = -p->coef;
		p++;
	}
	return OK;
}
/*����ʽ��ֵ*/
double evalue(polynomial L,double x)
{
	double sum = 0;
	polynomial p = L->next;
	while (p)
	{
   		sum += p->coef*pow(x, p->expn);
		p = p->next;
	}
	return sum;
}
void menu()
{
	printf("Ҫ����ÿ�ν�������ʱҪ��1��������Ķ���ʽ����ÿ�ζ���ʽ�����������������ʽ�����ٴ����롣\n1.��������ʽLa��Lb\n2.����1������������ʽ���La+Lb\n3.����1������������ʽ���La-Lb\n4.����ʽ�ĳ˷�\n5.����ʽ��ֵ\n0.�˳�");
}
int main()
{
	polynomial La, Lb, e;
	int flag = 0;
	InitList(&La);
	InitList(&Lb);
	while (1)
	{
		system("cls");
		menu();
		switch (_getch())
		{
			case '1':

				system("cls");
				InitList(&La);
				InitList(&Lb);
				int n;
				printf("������La����");
				scanf("%d", &n);
				printf("�밴��ָ����ϵ����˳���������ʽ,ÿ����һ���밴�س�ȷ�ϡ�");
				while (n > 0)
				{
					e = (polynomial)malloc(sizeof(polynode));

					scanf("%d%lf", &(e->expn), &(e->coef));
					ListInsert(La, e);
					n--;
				}
				ListTraverse(La);
				printf("������Lb����");
				scanf("%d", &n);
				printf("�밴��ָ����ϵ����˳���������ʽ,ÿ����һ���밴�س�ȷ�ϡ�");
				while (n > 0)
				{
					e = (polynomial)malloc(sizeof(polynode));

					scanf("%d%lf", &(e->expn), &(e->coef));
					ListInsert(Lb, e);
					n--;
				}

				ListTraverse(Lb);
				printf("\n���س�������");
				while (_getch() != '\r');
				continue;

			case '2':

				system("cls");
				ListUnion(&La, Lb);
				ListTraverse(La);
				
				while (_getch() != '\r');
				continue;
			case '3':
				system("cls");
				//ȡLb��ϵ�����෴��
				inverse(Lb);
				ListUnion(&La, Lb);
				ListTraverse(La);
				
				while (_getch() != '\r');
				continue;
			case '4':
				system("cls");
				MultiplyPoly(&La, &Lb);
				ListTraverse(La);
				DestroyList(&La);
				while (_getch() != '\r');
				continue;
			case '5':
				system("cls");
				printf("�����������xֵ������ʽΪLa)");
				double x;
				scanf("%lf", &x);
				printf("�ö���ʽ��ֵΪ%lf",evalue(La, x));
				while (_getch() != '\r');
				continue;
			case '0':
				flag = 1;
				printf("���ͷ��ڴ�...");
				break;

		}
		if (flag)
			break;
	}

	DestroyList(&La);
	DestroyList(&Lb);
	return 0;
}