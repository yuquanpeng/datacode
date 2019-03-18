#include<iostream>
#include<assert.h>
#define char ElemType
using namespace std;

typedef struct // ��ı�ʾ,����ʽ������Ϊ LinkList ������Ԫ�� 
{
	float coef; // ϵ�� 
	int expn; // ָ�� 
}term, ElemType;

typedef struct LNode // ������� 
{
	ElemType data;
	struct LNode *next;
}LNode, *Link, *Position;

typedef struct LinkList // �������� 
{
	Link head, tail; // �ֱ�ָ�����������е�ͷ�������һ����� 
	int len; // ָʾ��ǰ��������������Ԫ�صĸ��� 
}LinkList;
typedef LinkList polynomial;

void InitList(LinkList &P);
void CreatPolyn(polynomial &P, int m);
void DestroyPolyn(polynomial &P);
void CreatePolyn(polynomial &P, int m);//������ʾһԪ����ʽ���������� P 
void DestroyPolyn(polynomial &P);//����һԪ����ʽ P 
void PrintPolyn(polynomial P);//��ӡ 
int PolyLength(polynomial P);//�������� 
void AddPolyn(polynomial &Pa, polynomial &Pb);//������� 
void MultiplyPolyn(polynomial &P, polynomial &Pa, polynomial &Pb);//������� 
void SubtractPolyn(polynomial &Pa, polynomial &Pb);//������� 

void InitList(polynomial &P)
{
	P.head = P.tail = (LNode*)malloc(sizeof(LNode));
	if (P.head == NULL)///////////////////////
	{
		cout << "������48 ������ֹ" << endl;
		exit(-1);
	}
	P.head->next = NULL;
	P.len = 0;
}
void CreatePolyn(polynomial &P, int m)//������ʾһԪ����ʽ���������� P 
{
	Position q, s;
	term e;
	int i;
	InitList(P);
	cout << "����������" << m << "��ϵ����ָ����" << endl;
	for (i = 1; i <= m; i++)
	{
		cin >> e.coef >> e.expn;
		q = P.tail;
		s = (LNode*)malloc(sizeof(LNode));
		if (s == NULL)
		{
			cout << "������68 ������ֹ" << endl;
			exit(-1);
		}
		s->data.coef = e.coef;
		s->data.expn = e.expn;
		P.tail->next = s;
		s->next = NULL;
		P.tail = s;
		P.len++;
	}
}

void DestroyPolyn(polynomial &P)//����һԪ����ʽ P 
{
	free(P.head); //�ͷ�ͷβ���
	P.len = 0;
}

void PrintPolyn(polynomial P)//��ӡ 
{
	if (P.len == 0)
	{
		cout << "�㻹û��������ʽŶ!" << endl;
	}
	else
	{
		LNode *p = P.head->next;
		for (int i = 1; i <P.len; i++)
		{
			cout << p->data.coef << "X" << "^" << p->data.expn << "+";
			p = p->next;
		}
		cout << p->data.coef << "X" << "^" << p->data.expn << endl;
	}
}
int PolyLength(polynomial P)//���� 
{
	return P.len;
}
void AddPolyn(polynomial &Pa, polynomial &Pb)//������� 
{
	LNode *pa = Pa.head->next;
	LNode *pb = Pb.head->next;
	while (pa != NULL && pb != NULL)
	{
		if (pa->data.expn < pb->data.expn)//ָ��С 
		{
			pa = pa->next;
		}
		else if (pa->data.expn == pb->data.expn) //ָ����� 
		{
			pa->data.coef = pa->data.coef + pb->data.coef;
			pa = pa->next; pb = pb->next;
		}
		else if (pa->data.expn > pb->data.expn)//ָ���� 
		{
			LNode *q = Pa.head;
			while (q->next != pa)
			{
				q = q->next;
			}
			q->next = pb;
			pb = pb->next;
			Pa.len++;
		}
	}
	if (pa == NULL)
	{
		LNode *q = Pa.head;
		while (q->next != pa)
		{
			q = q->next;
		}
		while (pb != NULL)
		{
			q->next = pb;
			q = pb;
			pb = pb->next;
			Pa.len++;
		}
		Pa.tail = Pb.tail;
	}
}
void SubtractPolyn(polynomial &Pa, polynomial &Pb)//������� 
{
	LNode *pa = Pa.head->next;
	LNode *pb = Pb.head->next;
	while (pa != NULL && pb != NULL)
	{
		if (pa->data.expn < pb->data.expn)
		{
			pa = pa->next;
		}
		else if (pa->data.expn == pb->data.expn)
		{
			pa->data.coef = pa->data.coef - pb->data.coef;
			pa = pa->next;
			pb = pb->next;
		}
		else if ((pa->data.expn) >(pb->data.expn))
		{
			LNode *q = Pa.head;
			while (q->next != pa)
			{
				q = q->next;
			}
			q->next = pb;
			pb->data.coef = -pb->data.coef;
			pb = pb->next;
			Pa.len++;
		}
	}
	if (pa == NULL)
	{
		LNode *q = Pa.head;
		while (q->next != pa)
		{
			q = q->next;
		}
		while (pb != NULL)
		{
			q->next = pb;
			pb->data.coef = -pb->data.coef;
			q = pb;
			pb = pb->next;
			Pa.len++;
		}
		Pa.tail = Pb.tail;
	}
}
void MultiplyPolyn(polynomial &Pd, polynomial &Pa, polynomial &Pb)//������� 
{
	polynomial Pc;
	InitList(Pd);
	LNode *pa = Pa.head->next;
	while (pa != NULL)
	{
		for (int i = 1; i <= Pa.len; i++)
		{
			InitList(Pc);
			LNode *pc = Pc.head;
			LNode *pb = Pb.head->next;
			for (int j = 1; j <= Pb.len; j++)
			{
				LNode *s = (LNode *)malloc(sizeof(LNode));
				if (s == NULL)
				{
					cout << "������212 ������ֹ" << endl;
					exit(-1);
				}
				s->data.coef = pa->data.coef * pb->data.coef;
				s->data.expn = pa->data.expn + pb->data.expn;
				pc->next = s;
				s->next = NULL;
				pc = s;
				pb = pb->next;
				Pc.len++;
			}
			Pc.tail = pb;
			AddPolyn(Pd, Pc);
			free(Pc.head);
			free(Pc.tail);
			pa = pa->next;
		}
	}
}
int main()
{
	polynomial poly;
	polynomial poly1;
	polynomial poly2;
	InitList(poly);
	InitList(poly1);
	InitList(poly2);
	int m;
	int select = 1;
	while (select)
	{
		cout << "*********ѡ�*********" << endl;
		cout << "1 -> ����һԪ����ʽ " << endl;
		cout << "2 -> ����һԪ����ʽ" << endl;
		cout << "3 -> ��ӡһԪ����ʽ" << endl;
		cout << "4 -> һԪ����ʽ���" << endl;
		cout << "5 -> һԪ����ʽ���" << endl;
		cout << "6 -> һԪ����ʽ���" << endl;
		cout << "0 -> �˳�����" << endl;
		cout << "��ѡ����:";
		cin >> select;
		switch (select)
		{
		case 1: cout << "�������һ��һԪ����ʽ������:";
			cin >> m;
			CreatePolyn(poly, m); break;

		case 2: DestroyPolyn(poly); break;

		case 3: PrintPolyn(poly); break;

		case 4: cout << "�������һ��һԪ����ʽ������:";
			cin >> m;
			CreatePolyn(poly1, m);
			cout << "������ڶ���һԪ����ʽ������:";
			cin >> m;
			CreatePolyn(poly2, m);
			cout << "����ʽ Y1= ";//�������ʽ 
			PrintPolyn(poly1);
			cout << "����ʽ Y2= ";
			PrintPolyn(poly2);
			AddPolyn(poly1, poly2);
			cout << "��Ӻ� Y= ";
			PrintPolyn(poly1); break;

		case 5: cout << "�������һ��һԪ����ʽ������:";
			cin >> m;
			CreatePolyn(poly1, m);
			cout << "������ڶ���һԪ����ʽ������:";
			cin >> m;
			CreatePolyn(poly2, m);
			cout << "����ʽ Y1= ";//�������ʽ
			PrintPolyn(poly1);
			cout << "����ʽ Y2= ";
			PrintPolyn(poly2);
			SubtractPolyn(poly1, poly2);
			cout << "����� Y= ";
			PrintPolyn(poly1); break;

		case 6: cout << "�������һ��һԪ����ʽ������:";
			cin >> m;
			CreatePolyn(poly1, m);
			cout << "������ڶ���һԪ����ʽ������:";
			cin >> m;
			CreatePolyn(poly2, m);
			cout << "����ʽ Y1= ";//�������ʽ
			PrintPolyn(poly1);
			cout << "����ʽ Y2= ";
			PrintPolyn(poly2);
			MultiplyPolyn(poly, poly1, poly2);
			cout << "��˺� Y= ";
			PrintPolyn(poly); break;
		case 0:
			cout << "�����˳�" << endl;
			exit(1);
		default:break;
		}

	}
	return 0;
}