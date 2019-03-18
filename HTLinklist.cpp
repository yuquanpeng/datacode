#include<iostream>
#include<cstring>
#define TURE 1
#define OK 0
#define FALSE 0
#define ERROR 0
/*带有头结点和尾结点的单链表*/
typedef int Status;
typedef int ElemType;

using namespace std;

typedef struct LNode {
	ElemType data;
	struct LNode *next;
}*Link, *Position;
typedef struct {
	Link head, tail;
	int len;
}LinkList;

Status MakeNode(Link &p, ElemType e);   //分配由p指向e的结点，并返回Ok；若分配失败，则返回ERROR
void FreeNode(Link &p);                 //释放p所指结点
Status InitList(LinkList &L);           //构造一个空的线性链表L
Status DestroyList(LinkList &L);        //销毁链表L，L不再存在
Status ClearList(LinkList &L);          //将线性链表L重置为空表，并释放原链表的结点空间
Status InsFirst(Link h, Link s);         //已知h指向线性链表的头结点，将s所指结点插入在第一个结点之前
Status DelFirst(Link h, Link &q);       //已知h指向线性链表的头结点，删除链表中的第一个结点并以q返回
Status Append(LinkList &L, Link s);      //将指针s所指的一串结点连接在线性链表L的最后一个结点之后，
										 //并改变链表L的尾指针指向新的尾结点
Status Remove(LinkList &L, Link &q);    //删除线性链表L中的尾结点并以q返回，改变链表L的尾指针指向新的尾结点
Status InsBefore(LinkList &L, Link &p, Link s);
//已知p指向线性链表L中的一个结点，将s所指结点插入在p所指结点之前，并修改指针p指向新插入的结点
Status InsAfter(LinkList &L, Link &p, Link s);
//已知p指向线性链表L中的一个结点，将s所指结点插入在p所指结点之后，并修改指针p指向新插入的结点
Status SetCurElem(Link &p, ElemType e);  //已知p指向线性链表中的一个结点，用e更新p所指结点中数据元素的值
ElemType GetCurElem(Link p);            //已知p指向线性链表中的一个结点，返回p所指结点中数据元素的值
Status  ListEmpty(LinkList L);          //若线性表L为空表，则返回TRUE，否则返回FALSE
int ListLength(LinkList L);             //返回线性链表L中的元素个数
Position GetHead(LinkList L);           //返回线性链表L中头结点的位置
Position GetLast(LinkList L);           //返回线性链表L中最后一个节点的位置
Position PriorPos(LinkList L, Link p);   //已知p指向线性链表L中的一个结点，返回p所指结点的直接前驱位置，无返回NULL
Position NextPos(LinkList L, Link p);    //已知p指向线性链表L中的一个结点，返回p所指结点的直接后继位置，无返回NULL
Status LocatePos(LinkList L, int i, Link &p);//返回p指示线性链表L第i个结点并返回OK，i值不合法时返回ERROR
Position LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType, ElemType));
//返回线性链表L中第一个与e满足函数compare（）判定关系的元素的位置，若不存在这样的元素则返回NULL
Status ListTraverse(LinkList L, Status(*visit)());//依次对L的每个元素调用函数visit（）。一但visit（）失败，则操作失败
void Directory();                       //目录显示
Status FunctionCall(LinkList & L, int i);  //函数调用
Status Input_L(LinkList &L, int i);        //接受元素
Status Output_L(LinkList L);              //输出元素

Status ListInsert_L(LinkList &L, int i, ElemType e);

int main()
{
	LinkList L;
	InitList(L);

	cout <<"表空否："<< ListEmpty(L);

	Input_L(L, 5);
	Output_L(L);
	cout << "表空否"<< ListEmpty(L);

	return 0;
}

//分配由p指向e的结点，并返回Ok；若分配失败，则返回ERROR
Status MakeNode(Link &p, ElemType e) {//分配由p指向e的结点，并返回Ok；若分配失败，则返回ERROR
	p = (LNode*)new(LNode);
	if (!p)
		return ERROR;
	p->next = NULL;
	p->data = e;
	return OK;
}

//释放p所指结点
void FreeNode(Link &p) {//释放p所指结点
	delete(p);
}


Status InitList(LinkList &L) {//构造一个空的线性链表L
	Link p = (Link)new(LNode);
	if (!p) return ERROR;
	p->next = NULL;
	L.head = L.tail = p;
	L.len = 0;
	return OK;
}
Status DestroyList(LinkList &L) {//销毁链表L，L不再存在
	Link p;
	p = L.head;
	while (p) {
		L.head = p->next;
		delete(p);
		p = L.head;
	}
	L.len = 0;
	return OK;
}
Status ClearList(LinkList &L) {//将线性链表L重置为空表，并释放原链表的结点空间
	DestroyList(L);
	InitList(L);
	return OK;
}
Status InsFirst(Link h, Link s) {//已知h指向线性链表的头结点，将s所指结点插入在第一个结点之前
	s->next = h->next;
	h->next = s;
	return OK;
}                       //为什么这一个和下一个参数没有linklist改变他的长度！！！！！！
Status DelFirst(Link h, Link &q) {//已知h指向线性链表的头结点，删除链表中的第一个结点并以q返回
	q = h->next;
	h->next = q->next;
	return OK;
}
Status Append(LinkList &L, Link s) {//将指针s所指的一串结点连接在线性链表L的最后一个结点之后，并改变链表L的尾指针指向新的尾结点
	Link p = L.tail;               //默认这串结点左后一个指向null
	p = PriorPos(L, p);
	p->next = s;
	int i = 0;
	while (p->next) {
		p = p->next;
		i++;
	}
	L.tail = p;
	L.len += i;
	return OK;
}
Status Remove(LinkList &L, Link &q) {//删除线性链表L中的尾结点并以q返回，改变链表L的尾指针指向新的尾结点
	Link p = PriorPos(L, L.tail);
	q = L.tail;
	L.tail = p;
	L.len -= 1;
	return OK;
}
Status InsBefore(LinkList &L, Link &p, Link s) {
	//已知p指向线性链表L中的一个结点，将s所指结点插入在p所指结点之前，并修改指针p指向新插入的结点
	s->next = p->next;
	p->next = s;
	p = s;
	L.len += 1;
	return OK;
}
Status InsAfter(LinkList &L, Link &p, Link s) {
	//已知p指向线性链表L中的一个结点，将s所指结点插入在p所指结点之后，并修改指针p指向新插入的结点
	p = p->next;
	InsBefore(L, p, s);
	return OK;
}
Status SetCurElem(Link &p, ElemType e) {//已知p指向线性链表中的一个结点，用e更新p所指结点中数据元素的值
	p->data = e;
	return OK;
}
ElemType GetCurElem(Link p) {//已知p指向线性链表中的一个结点，返回p所指结点中数据元素的值
	return p->data;
}
Status  ListEmpty(LinkList L) {//若线性表L为空表，则返回TRUE，否则返回FALSE
	if (L.head->next) return FALSE;
	return TURE;
}
int ListLength(LinkList L) {//返回线性链表L中的元素个数
	return L.len;
}
Position GetHead(LinkList L) {//返回线性链表L中头结点的位置
	return L.head;
}
Position GetLast(LinkList L) {//返回线性链表L中最后一个节点的位置
	return L.tail;
}
Position PriorPos(LinkList L, Link p) {//已知p指向线性链表L中的一个结点，返回p所指结点的直接前驱位置，无返回NULL
	if (p == L.head)
		return NULL;
	Link q = L.head;
	while (q->next != p) q = q->next;
	return q;
}
Position NextPos(LinkList L, Link p) {//已知p指向线性链表L中的一个结点，返回p所指结点的直接后继位置，无返回NULL
	if (p->next == NULL)
		return NULL;
	return p->next;
}
Status LocatePos(LinkList L, int i, Link &p) {//返回p指示线性链表L第i个结点并返回OK，i值不合法时返回ERROR
	if (i < 1 || i > L.len) return ERROR;
	p = L.head->next;
	for (int j = 0; j < i; j++)
		p = p->next;
	return OK;
}

/*void Directory() {//目录显示
	cout << "请选择操作：" << endl
		<< "1.输入" << " " << "2.输出" << " " << "3.插入" << endl
		<< "4.删除" << " " << "5.查找" << " " << "6.结束" << endl;
}
Status FunctionCall(LinkList &L, int i) {//函数调用
										 //看看switch 泪奔 = =
	int j = 0;
	if (i == 1) {
		cout << "请输入数据个数：\n";
		cin >> j;
		cout << "请一次输入数据：\n";
		Input_L(L, j);
	}
	if (i == 2) {
		cout << "数据依次为：" << endl;
		Output_L(L);
	}
	if (i == 3) {
		cout << "建设中..." << endl;
	}
	if (i == 4) {
		cout << "建设中..." << endl;
	}
	if (i == 5) {
		cout << "建设中..." << endl;
	}
	return OK;
}*/
Status Input_L(LinkList &L, int i) {//接受元素
	Link q, p;
	q = L.head;
	int j = i;
	while (j--) {
		int e;
		cin >> e;
		MakeNode(p, e);
		q->next = p;
		q = p;
	}
	q->next = NULL;
	L.tail = q;
	L.len += i;
	return OK;
}
Status Output_L(LinkList L) {//输出元素
	Link q;
	q = L.head->next;
	while (q) {
		cout << q->data << endl;
		q = q->next;
	}
	return OK;
}
Status ListInsert_L(LinkList &L, int i, ElemType e)
{
	Link h,s;
	if (!LocatePos(L, i - 1, h))
		return ERROR;
	if (!MakeNode(s, e))
		return ERROR;
	InsFirst(h, s);
	return OK;
}
