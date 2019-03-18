#include<iostream>
#include<assert.h>
#define char ElemType
using namespace std;

typedef struct // 项的表示,多项式的项作为 LinkList 的数据元素 
{
	float coef; // 系数 
	int expn; // 指数 
}term, ElemType;

typedef struct LNode // 结点类型 
{
	ElemType data;
	struct LNode *next;
}LNode, *Link, *Position;

typedef struct LinkList // 链表类型 
{
	Link head, tail; // 分别指向线性链表中的头结点和最后一个结点 
	int len; // 指示当前线性链表中数据元素的个数 
}LinkList;
typedef LinkList polynomial;

void InitList(LinkList &P);
void CreatPolyn(polynomial &P, int m);
void DestroyPolyn(polynomial &P);
void CreatePolyn(polynomial &P, int m);//建立表示一元多项式的有序链表 P 
void DestroyPolyn(polynomial &P);//销毁一元多项式 P 
void PrintPolyn(polynomial P);//打印 
int PolyLength(polynomial P);//返回项数 
void AddPolyn(polynomial &Pa, polynomial &Pb);//相加运算 
void MultiplyPolyn(polynomial &P, polynomial &Pa, polynomial &Pb);//相乘运算 
void SubtractPolyn(polynomial &Pa, polynomial &Pb);//相减运算 

void InitList(polynomial &P)
{
	P.head = P.tail = (LNode*)malloc(sizeof(LNode));
	if (P.head == NULL)///////////////////////
	{
		cout << "出错了48 程序终止" << endl;
		exit(-1);
	}
	P.head->next = NULL;
	P.len = 0;
}
void CreatePolyn(polynomial &P, int m)//建立表示一元多项式的有序链表 P 
{
	Position q, s;
	term e;
	int i;
	InitList(P);
	cout << "请依次输入" << m << "对系数、指数：" << endl;
	for (i = 1; i <= m; i++)
	{
		cin >> e.coef >> e.expn;
		q = P.tail;
		s = (LNode*)malloc(sizeof(LNode));
		if (s == NULL)
		{
			cout << "出错了68 程序终止" << endl;
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

void DestroyPolyn(polynomial &P)//销毁一元多项式 P 
{
	free(P.head); //释放头尾结点
	P.len = 0;
}

void PrintPolyn(polynomial P)//打印 
{
	if (P.len == 0)
	{
		cout << "你还没创建多项式哦!" << endl;
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
int PolyLength(polynomial P)//项数 
{
	return P.len;
}
void AddPolyn(polynomial &Pa, polynomial &Pb)//相加运算 
{
	LNode *pa = Pa.head->next;
	LNode *pb = Pb.head->next;
	while (pa != NULL && pb != NULL)
	{
		if (pa->data.expn < pb->data.expn)//指数小 
		{
			pa = pa->next;
		}
		else if (pa->data.expn == pb->data.expn) //指数相等 
		{
			pa->data.coef = pa->data.coef + pb->data.coef;
			pa = pa->next; pb = pb->next;
		}
		else if (pa->data.expn > pb->data.expn)//指数大 
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
void SubtractPolyn(polynomial &Pa, polynomial &Pb)//相减运算 
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
void MultiplyPolyn(polynomial &Pd, polynomial &Pa, polynomial &Pb)//相乘运算 
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
					cout << "出错了212 程序终止" << endl;
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
		cout << "*********选项卡*********" << endl;
		cout << "1 -> 创建一元多项式 " << endl;
		cout << "2 -> 销毁一元多项式" << endl;
		cout << "3 -> 打印一元多项式" << endl;
		cout << "4 -> 一元多项式相加" << endl;
		cout << "5 -> 一元多项式相减" << endl;
		cout << "6 -> 一元多项式相乘" << endl;
		cout << "0 -> 退出程序" << endl;
		cout << "请选择编号:";
		cin >> select;
		switch (select)
		{
		case 1: cout << "请输入第一个一元多项式的项数:";
			cin >> m;
			CreatePolyn(poly, m); break;

		case 2: DestroyPolyn(poly); break;

		case 3: PrintPolyn(poly); break;

		case 4: cout << "请输入第一个一元多项式的项数:";
			cin >> m;
			CreatePolyn(poly1, m);
			cout << "请输入第二个一元多项式的项数:";
			cin >> m;
			CreatePolyn(poly2, m);
			cout << "多项式 Y1= ";//输出多项式 
			PrintPolyn(poly1);
			cout << "多项式 Y2= ";
			PrintPolyn(poly2);
			AddPolyn(poly1, poly2);
			cout << "相加后 Y= ";
			PrintPolyn(poly1); break;

		case 5: cout << "请输入第一个一元多项式的项数:";
			cin >> m;
			CreatePolyn(poly1, m);
			cout << "请输入第二个一元多项式的项数:";
			cin >> m;
			CreatePolyn(poly2, m);
			cout << "多项式 Y1= ";//输出多项式
			PrintPolyn(poly1);
			cout << "多项式 Y2= ";
			PrintPolyn(poly2);
			SubtractPolyn(poly1, poly2);
			cout << "相减后 Y= ";
			PrintPolyn(poly1); break;

		case 6: cout << "请输入第一个一元多项式的项数:";
			cin >> m;
			CreatePolyn(poly1, m);
			cout << "请输入第二个一元多项式的项数:";
			cin >> m;
			CreatePolyn(poly2, m);
			cout << "多项式 Y1= ";//输出多项式
			PrintPolyn(poly1);
			cout << "多项式 Y2= ";
			PrintPolyn(poly2);
			MultiplyPolyn(poly, poly1, poly2);
			cout << "相乘后 Y= ";
			PrintPolyn(poly); break;
		case 0:
			cout << "程序退出" << endl;
			exit(1);
		default:break;
		}

	}
	return 0;
}