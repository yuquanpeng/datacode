#include<iostream>
#include<Windows.h>
#include<cstring>
#define TURE 1
#define OK 0
#define FALSE 0
#define ERROR 0
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

Status MakeNode(Link &p, ElemType e);   //������pָ��e�Ľ�㣬������Ok��������ʧ�ܣ��򷵻�ERROR
void FreeNode(Link &p);                 //�ͷ�p��ָ���
Status InitList(LinkList &L);           //����һ���յ���������L
Status DestroyList(LinkList &L);        //��������L��L���ٴ���
Status ClearList(LinkList &L);          //����������L����Ϊ�ձ����ͷ�ԭ����Ľ��ռ�
Status InsFirst(Link h, Link s);         //��֪hָ�����������ͷ��㣬��s��ָ�������ڵ�һ�����֮ǰ
Status DelFirst(Link h, Link &q);       //��֪hָ�����������ͷ��㣬ɾ�������еĵ�һ����㲢��q����
Status Append(LinkList &L, Link s);      //��ָ��s��ָ��һ�������������������L�����һ�����֮��
										 //���ı�����L��βָ��ָ���µ�β���
Status Remove(LinkList &L, Link &q);    //ɾ����������L�е�β��㲢��q���أ��ı�����L��βָ��ָ���µ�β���
Status InsBefore(LinkList &L, Link &p, Link s);
//��֪pָ����������L�е�һ����㣬��s��ָ��������p��ָ���֮ǰ�����޸�ָ��pָ���²���Ľ��
Status InsAfter(LinkList &L, Link &p, Link s);
//��֪pָ����������L�е�һ����㣬��s��ָ��������p��ָ���֮�󣬲��޸�ָ��pָ���²���Ľ��
Status SetCurElem(Link &p, ElemType e);  //��֪pָ�����������е�һ����㣬��e����p��ָ���������Ԫ�ص�ֵ
ElemType GetCurElem(Link p);            //��֪pָ�����������е�һ����㣬����p��ָ���������Ԫ�ص�ֵ
Status  ListEmpty(LinkList L);          //�����Ա�LΪ�ձ��򷵻�TRUE�����򷵻�FALSE
int ListLength(LinkList L);             //������������L�е�Ԫ�ظ���
Position GetHead(LinkList L);           //������������L��ͷ����λ��
Position GetLast(LinkList L);           //������������L�����һ���ڵ��λ��
Position PriorPos(LinkList L, Link p);   //��֪pָ����������L�е�һ����㣬����p��ָ����ֱ��ǰ��λ�ã��޷���NULL
Position NextPos(LinkList L, Link p);    //��֪pָ����������L�е�һ����㣬����p��ָ����ֱ�Ӻ��λ�ã��޷���NULL
Status LocatePos(LinkList L, int i, Link &p);//����pָʾ��������L��i����㲢����OK��iֵ���Ϸ�ʱ����ERROR
Position LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType, ElemType));
//������������L�е�һ����e���㺯��compare�����ж���ϵ��Ԫ�ص�λ�ã���������������Ԫ���򷵻�NULL
Status ListTraverse(LinkList L, Status(*visit)());//���ζ�L��ÿ��Ԫ�ص��ú���visit������һ��visit����ʧ�ܣ������ʧ��
void Directory();                       //Ŀ¼��ʾ
Status FunctionCall(LinkList & L, int i);  //��������
Status Input_L(LinkList &L, int i);        //����Ԫ��
Status Output_L(LinkList L);              //���Ԫ��

Status ListInsert_L(LinkList &L, int i, ElemType e);

int main()
{
	LinkList L;
	InitList(L);

	cout << "��շ�" << ListEmpty(L);

	Input_L(L, 5);
	Output_L(L);
	cout << "��շ�" << ListEmpty(L);

	return 0;
}

//������pָ��e�Ľ�㣬������Ok��������ʧ�ܣ��򷵻�ERROR
Status MakeNode(Link &p, ElemType e) {//������pָ��e�Ľ�㣬������Ok��������ʧ�ܣ��򷵻�ERROR
	p = (LNode*)new(LNode);
	if (!p)
		return ERROR;
	p->next = NULL;
	p->data = e;
	return OK;
}

//�ͷ�p��ָ���
void FreeNode(Link &p) {//�ͷ�p��ָ���
	delete(p);
}


Status InitList(LinkList &L) {//����һ���յ���������L
	Link p = (Link)new(LNode);
	if (!p) return ERROR;
	p->next = NULL;
	L.head = L.tail = p;
	L.len = 0;
	return OK;
}
Status DestroyList(LinkList &L) {//��������L��L���ٴ���
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
Status ClearList(LinkList &L) {//����������L����Ϊ�ձ����ͷ�ԭ����Ľ��ռ�
	DestroyList(L);
	InitList(L);
	return OK;
}
Status InsFirst(Link h, Link s) {//��֪hָ�����������ͷ��㣬��s��ָ�������ڵ�һ�����֮ǰ
	s->next = h->next;
	h->next = s;
	return OK;
}                       //Ϊʲô��һ������һ������û��linklist�ı����ĳ��ȣ�����������
Status DelFirst(Link h, Link &q) {//��֪hָ�����������ͷ��㣬ɾ�������еĵ�һ����㲢��q����
	q = h->next;
	h->next = q->next;
	return OK;
}
Status Append(LinkList &L, Link s) {//��ָ��s��ָ��һ�������������������L�����һ�����֮�󣬲��ı�����L��βָ��ָ���µ�β���
	Link p = L.tail;               //Ĭ���⴮������һ��ָ��null
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
Status Remove(LinkList &L, Link &q) {//ɾ����������L�е�β��㲢��q���أ��ı�����L��βָ��ָ���µ�β���
	Link p = PriorPos(L, L.tail);
	q = L.tail;
	L.tail = p;
	L.len -= 1;
	return OK;
}
Status InsBefore(LinkList &L, Link &p, Link s) {
	//��֪pָ����������L�е�һ����㣬��s��ָ��������p��ָ���֮ǰ�����޸�ָ��pָ���²���Ľ��
	s->next = p->next;
	p->next = s;
	p = s;
	L.len += 1;
	return OK;
}
Status InsAfter(LinkList &L, Link &p, Link s) {
	//��֪pָ����������L�е�һ����㣬��s��ָ��������p��ָ���֮�󣬲��޸�ָ��pָ���²���Ľ��
	p = p->next;
	InsBefore(L, p, s);
	return OK;
}
Status SetCurElem(Link &p, ElemType e) {//��֪pָ�����������е�һ����㣬��e����p��ָ���������Ԫ�ص�ֵ
	p->data = e;
	return OK;
}
ElemType GetCurElem(Link p) {//��֪pָ�����������е�һ����㣬����p��ָ���������Ԫ�ص�ֵ
	return p->data;
}
Status  ListEmpty(LinkList L) {//�����Ա�LΪ�ձ��򷵻�TRUE�����򷵻�FALSE
	if (L.head->next) return FALSE;
	return TURE;
}
int ListLength(LinkList L) {//������������L�е�Ԫ�ظ���
	return L.len;
}
Position GetHead(LinkList L) {//������������L��ͷ����λ��
	return L.head;
}
Position GetLast(LinkList L) {//������������L�����һ���ڵ��λ��
	return L.tail;
}
Position PriorPos(LinkList L, Link p) {//��֪pָ����������L�е�һ����㣬����p��ָ����ֱ��ǰ��λ�ã��޷���NULL
	if (p == L.head)
		return NULL;
	Link q = L.head;
	while (q->next != p) q = q->next;
	return q;
}
Position NextPos(LinkList L, Link p) {//��֪pָ����������L�е�һ����㣬����p��ָ����ֱ�Ӻ��λ�ã��޷���NULL
	if (p->next == NULL)
		return NULL;
	return p->next;
}
Status LocatePos(LinkList L, int i, Link &p) {//����pָʾ��������L��i����㲢����OK��iֵ���Ϸ�ʱ����ERROR
	if (i < 1 || i > L.len) return ERROR;
	p = L.head->next;
	for (int j = 0; j < i; j++)
		p = p->next;
	return OK;
}

/*void Directory() {//Ŀ¼��ʾ
cout << "��ѡ�������" << endl
<< "1.����" << " " << "2.���" << " " << "3.����" << endl
<< "4.ɾ��" << " " << "5.����" << " " << "6.����" << endl;
}
Status FunctionCall(LinkList &L, int i) {//��������
//����switch �ᱼ = =
int j = 0;
if (i == 1) {
cout << "���������ݸ�����\n";
cin >> j;
cout << "��һ���������ݣ�\n";
Input_L(L, j);
}
if (i == 2) {
cout << "��������Ϊ��" << endl;
Output_L(L);
}
if (i == 3) {
cout << "������..." << endl;
}
if (i == 4) {
cout << "������..." << endl;
}
if (i == 5) {
cout << "������..." << endl;
}
return OK;
}*/
Status Input_L(LinkList &L, int i) {//����Ԫ��
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
Status Output_L(LinkList L) {//���Ԫ��
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
	Link h, s;
	if (!LocatePos(L, i - 1, h))
		return ERROR;
	if (!MakeNode(s, e))
		return ERROR;
	InsFirst(h, s);
	return OK;
}