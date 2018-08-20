#include<stdio.h>

#define LIST_INIT_SIZE 100 //���Ա�洢�ռ�ĳ�ʼ������
#define LISTINCREMENT 10//��������
typedef int ElemType;//���Ա�洢����������

typedef struct
{
	ElemType *elem; //�洢�ռ��ַ
	int length; //��ǰ����
	int listsize;   //��ǰ����Ĵ洢����
}sqList;

void InitList_Sq(sqList *L);
void DestoryList_Sq(sqList *L);
void ClearList_Sq(sqList *L);
int  ListEmpty_Sq(sqList L);
int ListLength_Sq(sqList L);
int GetElem_Sq(sqList L, int i, ElemType *e);
//��cur_e��L������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ�����������ʧ��
int PriorElem_Sq(sqList L, ElemType cur_e, ElemType *pre_e);
int NextElem_Sq(sqList L, ElemType cur_e, ElemType *next_e);

void InsertList_Sq(sqList *L, int i, ElemType e);
void DeleteList_Sq(sqList *L, int i, ElemType *e);
int Compare(ElemType ve1, ElemType ve2);
int LocateListElem(sqList L, ElemType e);
void TraverseList(sqList L);

void UnionList_Sq(sqList *L, sqList Lb);   /* ���α�ĺϲ�*/
void MergeList(sqList La, sqList Lb, sqList *Lc); /*���α��˳��ϲ�*/

void main()
{
	sqList L, La, Lc;
	int i;
	ElemType e;
	InitList_Sq(&L);//��������
	InitList_Sq(&La);
	InitList_Sq(&Lc);

	for (i = 1; i <= 5; i++)
	{
		InsertList_Sq(&L, i, i);//�ڿձ��в���Ԫ��
	}
	printf("�´����ı�L:");
	TraverseList(L);
	printf("\n");

	InsertList_Sq(&L, 6, 6);//�ڱ�β����6
	printf("��L��β����һ����Ԫ�غ�");
	TraverseList(L);
	printf("\n");

	DeleteList_Sq(&L, 6, &e);
	printf("L��ɾ��һ��Ԫ�غ�");
	TraverseList(L);
	printf("\n");

	for (i = 6; i <= 10; i++)
	{
		InsertList_Sq(&La, i - 5, i);
	}
	printf("�½���La��");
	TraverseList(La);
	printf("\n");

	printf("����L��La��");
	UnionList_Sq(&L, La);
	TraverseList(L);

	DestoryList_Sq(&L);
	DestoryList_Sq(&La);

	for (i = 1; i <= 5; i++)
	{
		InsertList_Sq(&L, i, 5 * (i - 1) + 1);
		InsertList_Sq(&La, i, 5* i);
	}

	printf("\n�½���L:");
	TraverseList(L);
	printf("\n�½���La��");
	TraverseList(La);
	MergeList(L, La, &Lc);
	printf("\nMergeList ��L�ͱ�La��");
	TraverseList(Lc);
}

void InitList_Sq(sqList *L)
{
	//����һ���յ����Ա�
	L->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L->elem)
	{
		printf("������ʧ��\n");
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
		printf("λ�ò���ʧ��!!\n");
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
	if (i<=0 || i>L->length+1)
	{
		printf("�����iֵ���� ����");
		exit(1);
	}
	if (L->length >= L->listsize)
	{
		newbase = (ElemType*)realloc(L->elem, (L->listsize + LISTINCREMENT)*sizeof(ElemType));

		if (!newbase)
		{
			printf("�����ռ�������!!\n");
			exit(1);
		}
		L->elem = newbase;//�»�ַ
		L->listsize = L->listsize + LISTINCREMENT;//���Ӵ洢����
	}
	q = &(L->elem[i - 1]);//����λ��
	for (p = &(L->elem[L->length - 1]); p >= q; p--)//Ԫ�����ƶ�
	{
		*(p + 1) = *p;
	}
	*q = e;//����e
	++L->length;//������1

}

void DeleteList_Sq(sqList *L, int i, ElemType *e)
{
	ElemType *p, *q;
	if (i<1 || i>L->length)
	{
		printf("���Ա�ɾ��ʧ�� i ֵ����!!\n");
		exit(1);
	}
	p = &(L->elem[i - 1]);//pΪɾ��λ�õ�Ԫ��
	*e = *p;//��ɾ��Ԫ�ظ�ֵ��e
	q = &(L->elem[L->length - 1]);//��λԪ�ص�λ��
	for (++p; p <= q; ++p)//Ԫ������
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
	//�����Ա�L�в��ҵ�һ��ֵ��e����compare������Ԫ�ص�λ��
	int i = 1;
	ElemType *p = L.elem;//p��ֵΪ��һ��Ԫ�صĴ洢λ��
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
	L_len = L->length;//����
	Lb_len = Lb.length;
	for (i = 1; i <= Lb.length; i++)
	{
		GetElem_Sq(Lb, i, &e);//���Lb�ĵ�i��Ԫ�ظ�e
		if (LocateListElem(*L, e) == 0)
		{
			InsertList_Sq(L, ++L_len, e);//La�в�����e �����֮
		}
	}
}

/*void MergeList(sqList La, sqList Lb, sqList *Lc)
{
	int i=1, j=1, k=0;
	ElemType La_e, Lb_e;
	int La_len = La.length;
	int Lb_len = Lb.length;

	sqList *pa = La.elem;
	sqList *pb = Lb.elem;
	Lc->listsize = Lc->length = La.elem + Lb.length;
	sqList *pc = Lc->elem = (ElemType *)malloc(Lc->listsize*sizeof(ElemType));
	if (!Lc->elem)
	{
		printf("Lc�洢����ʧ��");
		exit(1);
	}
	sqList *pa_last = La.elem + La.length - 1;
	sqList *pb_last = Lb.elem + Lb.length - 1;
	while (pa <= pa_last && pb <= pb_last)
	{
		if (pa <= pb)
			*pc++ = *pa++;
		else
			*pc++ = *pb++;
	}
	while (pa <= pa_last)
		*pc++ = *pa++;
	while (pb <= pb_last)
		*pc++ = *pb++;
}*/

void MergeList(sqList La, sqList Lb, sqList *Lc)
{
	int i = 1, j = 1, k = 0;
	ElemType La_e, Lb_e;
	int La_len = La.length;
	int Lb_len = Lb.length;

	while (i <= La_len && j <= Lb_len)
	{
		GetElem_Sq(La, i, &La_e);
		GetElem_Sq(Lb, j, &Lb_e);
		if (La_e <= Lb_e)
		{
			InsertList_Sq(Lc, ++k, La_e);
			++i;
		}
		else
		{
			InsertList_Sq(Lc, ++k, Lb_e);
			++j;
		}
	}
	while (i <= La_len)
	{
		GetElem_Sq(La, i++, &La_e);
		InsertList_Sq(Lc, ++k, La_e);
	}
	while (j <= Lb_len)
	{
		GetElem_Sq(Lb, j++, &Lb_e);
		InsertList_Sq(Lc, ++k, Lb_e);
	}
}

void TraverseList(sqList L)
{
	int i;
	if (ListEmpty_Sq(L) == 1)
	{
		printf("�ձ�!!\n");
		return;
	}
	for (i = 0; i<L.length; i++)
	{
		printf("%d ", L.elem[i]);
		if (i + 1 % 8 == 0)
		{
			printf("\n");
		}
	}
}