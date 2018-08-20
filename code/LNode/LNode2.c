//���Ա�ĵ�����洢�ṹ
#include<stdio.h>
#include<stdlib.h>
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
//��cur_e��L������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ�����������ʧ��
int PriorElem_L(LinkList L, ElemType cur_e, ElemType *pre_e);
int NextElem_L(LinkList L, ElemType cur_e, ElemType *next_e);

int Compare_L(ElemType ve1, ElemType ve2);
int LocateElem_L(LinkList L, ElemType e);
void PrintList_L(LinkList L);

void main()
{
	int n = 5;
	LinkList La, Lb, Lc;

	CreateList_L(&La, n); //��λ������n��Ԫ�ص�ֵ
	printf("�´�����La��"); //�������La������ 
	PrintList_L(La);
	printf("\n");

	CreateList_L(&Lb, n); /* ��λ������n��Ԫ�ص�ֵ */
	printf("�´�����Lb��"); /* �������Lb������ */
	PrintList_L(Lb);
	printf("\n");
	MergeList_L(La, &Lb, &Lc); /* ���ǵݼ�˳��鲢La��Lb,�õ��±�Lc */
	printf("MergeList_L ���Lc��"); /* �������Lc������ */
	PrintList_L(Lc);
	printf("\n");
}

void InitList_L(LinkList *L)//����һ���յ����Ա�L
{
	*L = (LinkList)malloc(sizeof(LNode));
	if (!*L)
	{
		printf("�����Ա���ʧ��");
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
void ClearList_L(LinkList L)//��L����ΪNULL
{
	LinkList p, q;
	p = L->next;
	while (p) //û����β 
	{
		q = p->next;
		free(p);
		p = q;
	}
	L->next = NULL; //ͷ���ָ����Ϊ�� 
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
void CreateList_L(LinkList *L, int n)/////////////////////////////////////////
{
	//��λ������n��Ԫ�ص�ֵ ��������ͷ���ĵ������Ա�L
	LinkList p;
	*L = (LinkList)malloc(sizeof(LNode));
	(*L)->next = NULL;//�Ƚ���һ����ͷ���ĵ�����
	for (int i = n; i > 0; i--)
	{
		p = (LinkList)malloc(sizeof(LNode));//�����½ڵ�
		scanf_s("%d", &p->data); //����Ԫ��ֵ 
		p->next = (*L)->next; // ���뵽��ͷ 
		(*L)->next = p;
	}
}

int GetELem_L(LinkList L, int i, ElemType *e)
{
	//LΪ��ͷ���ĵ������ͷָ��
	//iԪ�ش��ڷ���1 ����֮����e
	LinkList p = L->next;//��ʼ��  pָ���һ���ڵ� j Ϊ������
	int j = 1;
	while (p&&j < i)
	{
		p = p->next;
		++j;
	}
	if (!p || j>i)
	{
		printf("��ȡֵi�Ƿ� �����˳�");
		exit(1);
	}
	*e = p->data;//ȡ��i��Ԫ��
	return 1;
}

int Compare_L(ElemType ve1, ElemType ve2)//����Ԫ���ж�����
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
		if (Compare_L(p->data, e)) //�ҵ�����Ԫ��
			return i;
		p = p->next;
	}
	return 0;
}

int PriorElem_L(LinkList L, ElemType cur_e, ElemType *pre_e)
{
	LinkList q, p = L->next; // pָ���һ�����
	while (p->next) //p��ָ����к�� 
	{
		q = p->next; // qΪp�ĺ�� 
		if (q->data == cur_e)
		{
			*pre_e = p->data;
			return 1;
		}
		p = q; // p����� 
	}
	return 0;
}
int NextElem_L(LinkList L, ElemType cur_e, ElemType *next_e)
{
	LinkList p = L->next; // pָ���һ�����
	while (p->next) //p��ָ�����ǰ�� 
	{
		if (p->data == cur_e)
		{
			*next_e = p->data;
			return 1;
		}
		p = p->next; // p����� 
	}
	return 0;
}
void ListInsert_L(LinkList L, int i, ElemType e)
{
	LinkList p = L;
	int j = 0;
	while (p && j < i - 1)//Ѱ�ҵ�i-1���ڵ�
	{
		p = p->next;
		++j;
	}
	if (!p || j>i - 1)
	{
		printf("����ֵi�Ƿ� �����˳�");
		exit(1);
	}
	LinkList s = (LinkList)malloc(sizeof(LNode));//�����½ڵ�
	s->data = e;//����L
	s->next = p->next;
	p->next = s;
}
void ListDelete_L(LinkList L, int i, ElemType e)
{
	//ɾ����i��Ԫ�� ����e��������
	LinkList p = L;
	int j = 0;
	while (p->next && j < i - 1)//Ѱ�ҵ�i-1���ڵ�
	{
		p = p->next;
		++j;
	}
	if (!p->next || j>i - 1)
	{
		printf("ɾ��ֵi�Ƿ� �����˳�");
		exit(1);
	}
	LinkList q = (LinkList)malloc(sizeof(LNode));//�����½ڵ�
	q = p->next;//ɾ�����ͷŽ��
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
	//��֪�������Ա�La��Lb��Ԫ�ذ�ֵ�ǵݼ�����
	//�鲢La��Lb�õ��µĵ������Ա�Lc��Lc��Ԫ��Ҳ��ֵ�ǵݼ�����

	LinkList pa = (*La).next, pb = (*Lb)->next, pc;
	*Lc = pc = La; //��La��ͷ�����ΪLc��ͷ��� 

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

	pc->next = pa ? pa : pb; //����ʣ��� 
	free(*Lb); // �ͷ�Lb��ͷ��� 
	Lb = NULL;
}