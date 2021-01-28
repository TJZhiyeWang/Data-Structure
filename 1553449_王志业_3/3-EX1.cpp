/*1553449 王志业 3班*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>		//malloc/realloc函数
#include <conio.h>
#include <cmath>
#define TRUE		1
#define FALSE		0
#define OK		1
#define ERROR		0
#define INFEASIBLE	-1
#define LOVERFLOW	-2		//因为<math.h>中已有 OVERFLOW 的定义，因此换一下

typedef int Status;

typedef struct polynode
{
	double coef;
	int expn;
	struct polynode *next;
}polynode, *polynomial;

/* 初始化线性表 */
Status InitList(polynomial *L)
{
	/* 申请头结点空间，赋值给头指针 */
	*L = (polynomial)malloc(sizeof(polynode));
	if (*L == NULL)
		exit(LOVERFLOW);
	(*L)->next = NULL;
	return OK;
}

/* 删除线性表 */
Status DestroyList(polynomial *L)
{
	polynomial q, p = *L; //指向首元

						  /* 整个链表(含头结点)依次释放 */
	while (p) {    //若链表为空，则循环不执行
		q = p->next; //抓住链表的下一个结点
		free(p);
		p = q;
	}
	*L = NULL;	//头指针置NULL
	return OK;
}

/* 按指数从小到大排序在指定的位置插入一个新元素 */
Status ListInsert(polynomial &L, polynomial e)
{
	polynomial  p = L;	//p指向头结点

						/*找到适合放e->expn的位置*/
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

/*多项式归并操作，La,Lb归并入La*/
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
/* 遍历线性表 */
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
/*求链表元素个数*/
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

/*多项式的乘法*/
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
/*多项式求值*/
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
	printf("要求：在每次进行运算时要在1中输入你的多项式，在每次多项式运算结束后会清除多项式，需再次输入。\n1.建立多项式La，Lb\n2.将（1）中两个多项式相加La+Lb\n3.将（1）中两个多项式相减La-Lb\n4.多项式的乘法\n5.多项式求值\n0.退出");
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
				printf("请输入La项数");
				scanf("%d", &n);
				printf("请按照指数，系数的顺序输入多项式,每输入一项请按回车确认。");
				while (n > 0)
				{
					e = (polynomial)malloc(sizeof(polynode));

					scanf("%d%lf", &(e->expn), &(e->coef));
					ListInsert(La, e);
					n--;
				}
				ListTraverse(La);
				printf("请输入Lb项数");
				scanf("%d", &n);
				printf("请按照指数，系数的顺序输入多项式,每输入一项请按回车确认。");
				while (n > 0)
				{
					e = (polynomial)malloc(sizeof(polynode));

					scanf("%d%lf", &(e->expn), &(e->coef));
					ListInsert(Lb, e);
					n--;
				}

				ListTraverse(Lb);
				printf("\n按回车键继续");
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
				//取Lb的系数的相反数
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
				printf("请输入想求的x值（多项式为La)");
				double x;
				scanf("%lf", &x);
				printf("该多项式的值为%lf",evalue(La, x));
				while (_getch() != '\r');
				continue;
			case '0':
				flag = 1;
				printf("已释放内存...");
				break;

		}
		if (flag)
			break;
	}

	DestroyList(&La);
	DestroyList(&Lb);
	return 0;
}