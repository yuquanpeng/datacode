#include<stdio.h>
#define MAXSIZE 5
typedef int ElemType;

typedef struct
{
	ElemType data;
	int cur;
}component, SLinkList[MAXSIZE];

int LocateElem_SL(SLinkList *S, ElemType elem);
void InitSpace_SL(SLinkList *space);
int Malloc_SL(SLinkList *space);
void Free_SL(SLinkList *space, int k);
void Difference_SL(SLinkList *space, int *S);

void main()
{
	int s;
	SLinkList space;
	InitSpace_SL(&space);
	Difference_SL(&space, &s);
}

/*int LocateElem_SL(SLinkList *S, ElemType elem)
{
	int i = S[0].cur;//Iָʾ���еĵ�һ���ڵ�
	while (i && S[i].data != elem)//�ڱ���˳������
		i = S[i].cur;
	return i;
}*/

void InitSpace_SL(SLinkList *space)
{
	//��һλ����space�и��������ӳ�һ���������� space[0].cur λͷָ��
	for (int i = 0; i<MAXSIZE - 1; i++) 
	{
		space[i]->cur = i + 1;
		//space[i]->data = 0;
	}
	space[MAXSIZE - 1]->cur = 0;
}

int Malloc_SL(SLinkList *space)
{
	//���ط����Ԫ�ص��±�
	int i = space[0]->cur;
	if (space[0]->cur) space[0]->cur = space[i]->cur;
	return i;
}
void Free_SL(SLinkList *space, int k)
{
	//���±�Ϊk�Ľڵ���յ���������
	space[k]->cur = space[0]->cur;
	space[0]->cur = k;
}
void Difference_SL(SLinkList *space, int *S)
{
	InitSpace_SL(space);//��ʼ�����ÿռ�
	*S = Malloc_SL(space);//����S��ͷ���
	int r = S;//rָ��S�ĵ�ǰ�����
	printf("�����뼯��A�ͼ���B��Ԫ�ظ���:\n");
	int m, n;
	scanf_s("%d %d", &m, &n);
	for (int j = 1; j <= m; j++)
	{
		int i = Malloc_SL(space);//����ڵ�
		scanf_s("%d", &space[i]->data);//����A��Ԫ�ص�ֵ
		space[r]->cur = i;  
		r = i;//���뵽��β
	}
	space[r]->cur = 0;  //Aβ���cur��0
	for (int j = 1; j <= n; j++) //��������B��Ԫ��  �����ڵ�ǰ��������� ����ɾ��
	{
		int b;
		scanf_s("%d", &b);
		int p = S; int k = space[*S]->cur;//��kָ�򼯺�A�еĵ�һ���ڵ�
		while (k != space[r]->cur&&space[k]->data != b) //�ڵ�ǰ���в���
		{
			p = k; k = space[k]->cur;
		}
		if (k == space[r]->cur) //��ǰ���в����ڸ�Ԫ��  ������r��ָ���֮��
		{
			int i = Malloc_SL(space);
			space[i]->data = b;
			space[i]->cur = space[r]->cur;
			space[r]->cur = i;//�����в����ڸ�Ԫ�أ�����r��ָ�ڵ����r��λ�ò���
		}
		else//��Ԫ�����ڱ��� ɾ��
		{
			space[p]->cur = space[k]->cur;
			Free_SL(space, k);
			if (r == k) 
				r = p;//rʼ��ָ��A�����
		}
	}
}