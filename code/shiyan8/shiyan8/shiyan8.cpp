#include<iostream>
#include<time.h>
using namespace std;

#define LIST_INIT_SIZE 100 //���Ա�洢�ռ�ĳ�ʼ������
#define LISTINCREMENT 10//��������
#define random(x) (rand()%x)//�����

int compareNum[2];//������¼�ȽϵĴ���
int changeNum[2];//�����ȽϽ����Ĵ��� 

typedef struct
{
	int *elem; //�洢�ռ��ַ �洢���ݵ�����
	int length; //��ǰ����
	int listsize;   //��ǰ����Ĵ洢����
}SqList;



void InitList_Sq(SqList &L)
{
	//����һ���յ����Ա�
	L.elem = (int *)malloc(LIST_INIT_SIZE * sizeof(int));
	if (!L.elem)
	{
		cout << "������ʧ��/n";
		exit(1);
	}
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
}

void InsertList_Sq(SqList &L, int i, int e)
{
	int *newbase = NULL;
	int *p, *q;
	if (i<1 || i>L.length+1)
	{
		cout << "�����iֵ���� ����" << endl;
		exit(1);
	}
	if (L.length >= L.listsize)
	{
		newbase = (int*)realloc(L.elem, (L.listsize + LISTINCREMENT)*sizeof(int));

		if (!newbase)
		{
			cout << "�����ռ�������!!/n";
			exit(1);
		}
		L.elem = newbase;//�»�ַ
		L.listsize = L.listsize + LISTINCREMENT;//���Ӵ洢����
	}
	q = &(L.elem[i - 1]);//����λ��
	for (p = &(L.elem[L.length - 1]); p >= q; p--)//Ԫ�����ƶ�
	{
		*(p + 1) = *p;
	}
	*q = e;//����e
	++L.length;//������1

}

void PrintSqList(SqList &L,int num)
{
	int i;
	if (L.length == 0)
	{
		cout << "���� �ձ�\n";
		return;
	}
	for (i = 0; i < num; i++)
		cout << L.elem[i]<<", ";
	cout << endl;
}
/*********************�������㷨***********************/
int SelectMinKey(SqList &L, int i)
{
	int k = 0;
	compareNum[0] += L.length - i;
	for (k = i; i < L.length; i++)
	{
		compareNum[0]++;//��¼����i��length�ıȽ�
		compareNum[0]++;//�����ѡ������еıȽ�
		if (L.elem[i] > L.elem[k])
		{
			k = i; changeNum[0]++;
		}
	}
	return k;
}

void SelectSort(SqList &L)
{
	int j = 0;
	int temp = 0;
	//��˳�����м�����
	for (int i = 0; i < L.length;++i)
	{
		compareNum[0]++;//��¼����i��length�ıȽ�
		j = SelectMinKey(L, i);
		compareNum[0]++;
		if (i != j)
		{
			temp = L.elem[i];
			L.elem[i] = L.elem[j];
			L.elem[j] = temp;
			changeNum[0] += 3;//����+3
		}
	}
}
/********************�������㷨*********************/
void HeadAdjust(SqList &H, int s, int m)
{
	int rc = H.elem[s];
	for (int j = 2 * s; j <= m; j *= 2)
	{
		compareNum[1]++;//forѭ�����ж�
		if (j < m && (compareNum[1]++) && (H.elem[j] < H.elem[j + 1])) 
			++j;
		if (rc < H.elem[j]) 
		{ compareNum[1]++; break; }
		H.elem[s] = H.elem[j]; s = j;
		changeNum[1]++;
	}
	H.elem[s] = rc;
	changeNum[1]++;
}
void HeadSort(SqList &H)
{
	int temp;//�м�������ڱ�����ֵ��
	for (int i = H.length / 2; i>0; --i) {
		compareNum[1]++;
		HeadAdjust(H, i, H.length);//�����ĵ���
	}
	for (int i = H.length; i>1; --i) {
		compareNum[1]++;
		temp = H.elem[1]; H.elem[1] = H.elem[i]; H.elem[i] = temp;//����һ�μ�¼�໥����
		changeNum[1] += 3;
		HeadAdjust(H, 1, i - 1);//��һ�εĵ���
	}
}
int main()
{
	int na = 10;
	int nb = 10000;
	int m = 10;
	SqList La, Lb, La1,Lb1;
	InitList_Sq(La);
	InitList_Sq(Lb);
	InitList_Sq(La1);
	InitList_Sq(Lb1);

	for (int i = 1; i <= na; i++)
	{
		int temp;
		cout << "�������" << i <<"��ֵ=";
		cin >> temp;
		InsertList_Sq(La, i, temp);
		InsertList_Sq(La1, i, temp);
	}

	srand((int)time(0));
	//�������һ���20000���ڵ���
	for (int i = 1; i < nb; i++)
	{
		int temp = random(20000);
		InsertList_Sq(Lb, i, temp);
		InsertList_Sq(Lb1, i, temp);
	}

	//��ѡ������
	//PrintSqList(La, m);
	SelectSort(La);
	cout << "��ѡ������ �Ե�һ��Ƚ���" << compareNum[0] << "��" << endl;
	cout << "��ѡ������ �Ե�һ�齻����" << changeNum[0] << "��" << endl;
	PrintSqList(La, m);
	cout << endl;

	//PrintSqList(Lb, m);
	SelectSort(Lb);
	cout << "��ѡ������ �Եڶ���Ƚ���" << compareNum[0] << "��" << endl;
	cout << "��ѡ������ �Եڶ��齻����" << changeNum[0] << "��" << endl;
	PrintSqList(Lb, m);
	cout << endl;

	//������
	//PrintSqList(La1, m);
	HeadSort(La1);
	cout << "������ �Ե�һ��Ƚ���" << compareNum[1] << "��" << endl;
	cout << "������ �Ե�һ�齻����" << changeNum[1] << "��" << endl;
	PrintSqList(La, m);
	cout << endl;

	//PrintSqList(Lb1, m);
	HeadSort(Lb1);
	cout << "������ �Եڶ���Ƚ���" << compareNum[1] << "��" << endl;
	cout << "������ �Եڶ��齻����" << changeNum[1] << "��" << endl;
	PrintSqList(Lb, m);
	cout << endl;

	return 0;
}