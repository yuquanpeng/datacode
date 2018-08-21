#include<stdio.h>
#include<stdlib.h>
/*顺序表的动态分配实现
*/
#define LIST_INIT_SIZE 100 //线性表存储空间的初始分配量
#define LISTINCREMENT 10//分配增量
typedef int ElemType;//线性表存储的数据类型

typedef struct
{
	ElemType *elem; //存储空间基址
	int length; //当前长度
	int listsize;   //当前分配的存储容量
}sqList;

void InitList_Sq(sqList *L);
void DestoryList_Sq(sqList *L);
void ClearList_Sq(sqList *L);
int  ListEmpty_Sq(sqList L);
int ListLength_Sq(sqList L);
int GetElem_Sq(sqList L, int i, ElemType *e);
//若cur_e是L的数据元素，且不是第一个，则用pre_e返回他的前驱，否则操作失败
int PriorElem_Sq(sqList L, ElemType cur_e, ElemType *pre_e);
int NextElem_Sq(sqList L, ElemType cur_e, ElemType *next_e);
void InsertList_Sq(sqList *L, int i, ElemType e);
void DeleteList_Sq(sqList *L, int i, ElemType *e);
int Compare(ElemType ve1, ElemType ve2);
int LocateListElem(sqList L, ElemType e);
void TraverseList(sqList L);
void UnionList_Sq(sqList *L, sqList Lb);   /* 线形表的合并*/
void MergeList(sqList La, sqList Lb, sqList *Lc); /*线形表的顺序合并*/

void main()
{
	sqList L, La, Lc;
	int i;
	ElemType e;
	InitList_Sq(&L);//创建链表
	InitList_Sq(&La);
	InitList_Sq(&Lc);

	for (i = 1; i <= 5; i++)
	{
		InsertList_Sq(&L, i, i);//在空表中插入元素
	}
	printf("新创建的表L:");
	TraverseList(L);
	printf("/n");

	InsertList_Sq(&L, 6, 6);//在表尾插入6
	printf("在L表尾插入一个新元素后：");
	TraverseList(L);
	printf("/n");

	DeleteList_Sq(&L, 6, &e);
	printf("L表删除一个元素后：");
	TraverseList(L);
	printf("/n");

	for (i = 6; i <= 10; i++)
	{
		InsertList_Sq(&La, i - 5, i);
	}
	printf("新建表La：");
	TraverseList(La);
	printf("/n");

	printf("联合L和La：");
	UnionList_Sq(&L, La);
	TraverseList(L);

	DestoryList_Sq(&L);
	DestoryList_Sq(&La);

	for (i = 1; i <= 5; i++)
	{
		InsertList_Sq(&L, i, 5 * (i - 1) + 1);
		InsertList_Sq(&La, i, 5* i);
	}

	printf("/n新建表L:");
	TraverseList(L);
	printf("/n新建表La：");
	TraverseList(La);
	MergeList(L, La, &Lc);
	printf("/nMergeList 表L和表La：");
	TraverseList(Lc);
}

void InitList_Sq(sqList *L)
{
	//构造一个空的线性表
	L->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L->elem)
	{
		printf("链表创建失败/n");
		exit(1);
	}
	L->length = 0;
	L->listsize = LIST_INIT_SIZE;
}

void DestoryList_Sq(sqList *L)
{
	L->elem = NULL;
	L->length = 0;
	L->listsize = 0;
}

void ClearList_Sq(sqList *L)
{
	L->length = 0;
}

int ListEmpty_Sq(sqList L)
{
	if (0 == L.length)
	{
		return 1;
	}
	return 0;
}

int ListLength_Sq(sqList L)
{
	return L.length;
}

int GetElem_Sq(sqList L, int i, ElemType *e)
{
	if (i<1 && i >= L.length)
	{
		printf("位置查找失败!!/n");
		return 1;
	}
	*e = L.elem[i - 1];
	return 0;
}

int PriorElem_Sq(sqList L, ElemType cur_e, ElemType *pre_e)
{
	int i;
	for (i = 1; i<L.length; i++)
	{
		if ((L.elem[i]) == cur_e)
		{
			break;
		}
	}
	if (i >= 1 && i<L.length)
	{
		*pre_e = L.elem[i - 1];
		return 0;
	}
	return 1;
}

int NextElem_Sq(sqList L, ElemType cur_e, ElemType *next_e)
{
	int i;
	for (i = 0; i<L.length - 1; i++)
	{
		if (cur_e == L.elem[i])
		{
			break;
		}
	}
	if (i >= 0 && i<L.length - 1)
	{
		*next_e = L.elem[i + 1];
		return 0;
	}
	return 1;
}

void InsertList_Sq(sqList *L, int i, ElemType e)
{
	ElemType *newbase = NULL;
	ElemType *p, *q;
	if (i<1 || i>L->length)
	{
		printf("插入点i值超标 错误");
		exit(1);
	}
	if (L->length >= L->listsize)
	{
		newbase = (ElemType*)realloc(L->elem, (L->listsize + LISTINCREMENT)*sizeof(ElemType));

		if (!newbase)
		{
			printf("新增空间分配错误!!/n");
			exit(1);
		}
		L->elem = newbase;//新基址
		L->listsize = L->listsize + LISTINCREMENT;//增加存储容量
	}
	q = &(L->elem[i - 1]);//插入位置
	for (p = &(L->elem[L->length - 1]); p >= q; p--)//元素右移动
	{
		*(p + 1) = *p;
	}
	*q = e;//插入e
	++L->length;//表增长1

}

void DeleteList_Sq(sqList *L, int i, ElemType *e)
{
	ElemType *p, *q;
	if (i<1 || i>L->length)
	{
		printf("线性表删除失败 i 值超标!!/n");
		exit(1);
	}
	p = &(L->elem[i - 1]);//p为删除位置的元素
	*e = *p;//被删除元素赋值给e
	q = &(L->elem[L->length - 1]);//表位元素的位置
	for (++p; p <= q; ++p)//元素左移
	{
		*(p - 1) = *p;
	}
	--L->length;
}

int Compare(ElemType ve1, ElemType ve2)
{
	if (ve1 == ve2)
	{
		return 1;
	}
	return 0;
}

int LocateListElem(sqList L, ElemType e)
{
	//在线性表L中查找第一个值与e满足compare（）的元素的位序
	int i = 1;
	ElemType *p = L.elem;//p的值为第一个元素的存储位置
	while (i <= L.length && !Compare(e, *p++))
	{
		++i;
	}
	if (i <= L.length)
	{
		return i;
	}
	return 0;
}

void UnionList_Sq(sqList *L, sqList Lb)
{
	int i, L_len, Lb_len;
	ElemType e;
	L_len = L->length;//长度
	Lb_len = Lb.length;
	for (i = 1; i <= Lb.length; i++)
	{
		GetElem_Sq(Lb, i, &e);//获得Lb的第i个元素给e
		if (LocateListElem(*L, e) == 0)
		{
			InsertList_Sq(L, ++L_len, e);//La中不存在e 则插入之
		}
	}
}

void MergeList(sqList La, sqList Lb, sqList *Lc)
{
	int i=1, j=1, k=0;
	ElemType La_e, Lb_e;
	int La_len = La.length;
	int Lb_len = Lb.length;
 
 while(i<=La_len && j<=Lb_len)
 {
  GetElem_Sq(La,i,&La_e);
  GetElem_Sq(Lb,j,&Lb_e);
  if(La_e<=Lb_e)
  {
   InsertList_Sq(Lc,++k,La_e);
   ++i;
  }
  else
  {
   InsertList_Sq(Lc,++k,Lb_e);
   ++j;
  }
 }
 while(i<=La_len)
 {
  GetElem_Sq(La,i++,&La_e);
  InsertList_Sq(Lc,++k,La_e);
 }
 while(j<=Lb_len)
 {
  GetElem_Sq(Lb,j++,&Lb_e);
  InsertList_Sq(Lc,++k,Lb_e);
 }
}

void TraverseList(sqList L)
{
	int i;
	if (ListEmpty_Sq(L) == 1)
	{
		printf("空表!!/n");
		return;
	}
	for (i = 0; i<L.length; i++)
	{
		printf("%d ", L.elem[i]);
		if (i + 1 % 8 == 0)
		{
			printf("/n");
		}
	}
}
