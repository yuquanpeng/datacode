#include<stdio.h>
#include<stdlib.h>
/*单链表
*/
typedef int ElemType;
typedef struct LNode
{
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;

void InitList_L(LinkList *L);
void DestroyList_L(LinkList *L);
int GetELem_L(LinkList L, int i, ElemType *e);
void ListInsert_L(LinkList L, int i, ElemType e);
void ListDelete_L(LinkList L, int i, ElemType e);
void CreateList_L(LinkList *L, int n);
void MergeList_L(LinkList La, LinkList *Lb, LinkList *Lc);
int ListLength_L(LinkList L);
int ListEmpty_L(LinkList L);
void ClearList_L(LinkList L);
//若cur_e是L的数据元素，且不是第一个，则用pre_e返回他的前驱，否则操作失败
int PriorElem_L(LinkList L, ElemType cur_e, ElemType *pre_e);
int NextElem_L(LinkList L, ElemType cur_e, ElemType *next_e);
int Compare_L(ElemType ve1, ElemType ve2);
int LocateElem_L(LinkList L, ElemType e);
void PrintList_L(LinkList L);

void main()
{
	int n = 5;
	LinkList La, Lb, Lc;

	CreateList_L(&La, n); //逆位序输入n个元素的值
	printf("新创建的La："); //输出链表La的内容 
	PrintList_L(La);
	printf("\n");

	CreateList_L(&Lb, n); /* 逆位序输入n个元素的值 */
	printf("新创建的Lb："); /* 输出链表Lb的内容 */
	PrintList_L(Lb);
	printf("\n");
	MergeList_L(La, &Lb, &Lc); /* 按非递减顺序归并La和Lb,得到新表Lc */
	printf("MergeList_L 后的Lc："); /* 输出链表Lc的内容 */
	PrintList_L(Lc);
	printf("\n");
}

void InitList_L(LinkList *L)//构造一个空的线性表L
{
	*L = (LinkList)malloc(sizeof(LNode));
	if (!*L)
	{
		printf("空线性表构造失败");
		exit(1);
	}
	(*L)->next = NULL;

}

void DestroyList_L(LinkList *L)
{
	LinkList q;
	while (*L)
	{
		q = (*L)->next;
		free(*L);
		*L = q;
	}
}
void ClearList_L(LinkList L)//将L重置为NULL
{
	LinkList p, q;
	p = L->next;
	while (p) //没到表尾 
	{
		q = p->next;
		free(p);
		p = q;
	}
	L->next = NULL; //头结点指针域为空 
}
int ListLength_L(LinkList L)
{
	int i = 0;
	LinkList p = L->next;
	while (p)
	{
		i++;
		p = p->next;
	}
	return i;
}
int ListEmpty_L(LinkList L)
{
	if (L->next)
		return 0;
	else
		return 1;
}
void CreateList_L(LinkList *L, int n)
{
	//逆位序输入n个元素的值 建立带表头结点的单链线性表L
	LinkList p;
	int i;
	*L = (LinkList)malloc(sizeof(LNode));
	(*L)->next = NULL;//先建立一个带头结点的单链表
	for (i = n; i > 0; i--)
	{
		p = (LinkList)malloc(sizeof(LNode));//生成新节点
		scanf_s("%d", &p->data); //输入元素值 
		p->next = (*L)->next; // 插入到表头 
		(*L)->next = p;
	}
}

int GetELem_L(LinkList L, int i, ElemType *e)
{
	//L为带头结点的单链表的头指针
	//i元素存在返回1 并将之付给e
	LinkList p = L->next;//初始化  p指向第一个节点 j 为计数器
	int j = 1;
	while (p&&j < i)
	{
		p = p->next;
		++j;
	}
	if (!p || j>i)
	{
		printf("获取值i非法 程序退出");
		exit(1);
	}
	*e = p->data;//取第i个元素
	return 1;
}

int Compare_L(ElemType ve1, ElemType ve2)//数据元素判定函数
{
	if (ve1 == ve2)
	{
		return 1;
	}
	return 0;
}
int LocateElem_L(LinkList L, ElemType e)
{
	int i = 0;
	LinkList p = L->next;
	while (p)
	{
		i++;
		if (Compare_L(p->data, e)) //找到数据元素
			return i;
		p = p->next;
	}
	return 0;
}

int PriorElem_L(LinkList L, ElemType cur_e, ElemType *pre_e)
{
	LinkList q, p = L->next; // p指向第一个结点
	while (p->next) //p所指结点有后继 
	{
		q = p->next; // q为p的后继 
		if (q->data == cur_e)
		{
			*pre_e = p->data;
			return 1;
		}
		p = q; // p向后移 
	}
	return 0;
}
int NextElem_L(LinkList L, ElemType cur_e, ElemType *next_e)
{
	LinkList p = L->next; // p指向第一个结点
	while (p->next) //p所指结点有前驱 
	{
		if (p->data == cur_e)
		{
			*next_e = p->data;
			return 1;
		}
		p = p->next; // p向后移 
	}
	return 0;
}
void ListInsert_L(LinkList L, int i, ElemType e)
{
	LinkList p = L;
	int j = 0;
	while (p && j < i - 1)//寻找第i-1个节点
	{
		p = p->next;
		++j;
	}
	if (!p || j>i - 1)
	{
		printf("插入值i非法 程序退出");
		exit(1);
	}
	LinkList s = (LinkList)malloc(sizeof(LNode));//生成新节点
	s->data = e;//插入L
	s->next = p->next;
	p->next = s;
}
void ListDelete_L(LinkList L, int i, ElemType e)
{
	//删除第i个元素 并有e返回旗帜
	LinkList p = L;
	int j = 0;
	while (p->next && j < i - 1)//寻找第i-1个节点
	{
		p = p->next;
		++j;
	}
	if (!p->next || j>i - 1)
	{
		printf("删除值i非法 程序退出");
		exit(1);
	}
	LinkList q = (LinkList)malloc(sizeof(LNode));//生成新节点
	q = p->next;//删除并释放结点
	p->next = q->next;
	e = q->data;
	free(q);
}
void PrintList_L(LinkList L)
{
	LinkList p = L->next;
	while (p)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}

void MergeList_L(LinkList La, LinkList *Lb, LinkList *Lc)
{
	//已知单链线性表La和Lb的元素按值非递减排列
	//归并La和Lb得到新的单链线性表Lc，Lc的元素也按值非递减排列

	LinkList pa = (*La).next, pb = (*Lb)->next, pc;
	*Lc = pc = La; //用La的头结点作为Lc的头结点 

	while (pa&&pb)
		if (pa->data <= pb->data)
		{
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}
		else
		{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}

	pc->next = pa ? pa : pb; //插入剩余段 
	free(*Lb); // 释放Lb的头结点 
	Lb = NULL;
}