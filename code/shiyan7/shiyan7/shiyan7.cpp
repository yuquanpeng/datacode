#include<iostream>
#include<stdlib.h>

//����ֵ�Ƚϵ�Լ������
#define EQ(a,b) ((a) == (b))
#define LT(a,b) ((a)<(b))
#define LQ(a,b) ((a)<=(b))

using namespace std;
typedef int ElemType;//Ԫ�ص���������ΪElemtype
typedef int KeyType;

typedef struct BiTNode {//�����������ṹ
	ElemType data;
	struct BiTNode * lchild, *rchild;//���Һ���ָ��
}BiTNode,*BiTree;


/**********************�����������Ĳ����㷨***********************/
BiTree SrarchBST_1(BiTree T, KeyType key) {
	if ((!T) || EQ(key, T->data))
		return T;
	else if (LT(key, T->data))
		return (SrarchBST_1(T->lchild, key));
	else return (SrarchBST_1(T->rchild, key));
}

int SearchBST_2(BiTree T, KeyType key, BiTree f,BiTree &p) {
	if (!T) {
		p = f; return 0;//����ʧ��
	}
	else if (EQ(key, T->data)) {
		p = T; return 1;
	}
	else if (LT(key, T->data))
		return SearchBST_2(T->lchild, key, T, p);
	else 
		return SearchBST_2(T->rchild, key, T, p);
}

int InsertBST(BiTree &T, ElemType e) {
	BiTree p, s;
	if (!SearchBST_2(T, e, NULL, p)) {//���Ҳ��ɹ�
		s = (BiTree)malloc(sizeof(BiTNode));
		s->data = e; s->lchild = s->rchild = NULL;
		if (!p) {
			T = s;//������ڵ�Ϊ�µĽڵ�
		}
		else if (LT(e, p->data))
			p->lchild = s;//������ڵ� *sΪ
		else
			p->rchild = s;
		return 1;
	}
	else
		return 0;
}

void Print(BiTree root)
{
	BiTree p = root;
	if (p != NULL) {
		Print(p->lchild);
		cout << p->data << ",";
		Print(p->rchild);
	}
}


int main()
{
	BiTree T = NULL;
	BiTree p = NULL;
	int num = 0;
	int key;
	cout << "������ؼ��ָ�����";
	cin >> num;
	cout << "����������ؼ��֣�" << endl;
	for (int i = 0; i < num; i++) {
		int temp = 0;
		cin >> temp;
		InsertBST(T, temp);
	}
	cout << "��������Ҫ���ҵ�ֵ��";
	cin >> key;
	p = SrarchBST_1(T, key);
	if (p) {
		cout <<"���ҳɹ���"<< p->data<<endl;
	}
	else
		cout << "δ�ҵ���Ҫ�Ĺؼ���" << endl;
	Print(T);
	return 0;
}
