#include<iostream>
#include<stdlib.h>

//对数值比较的约定定义
#define EQ(a,b) ((a) == (b))
#define LT(a,b) ((a)<(b))
#define LQ(a,b) ((a)<=(b))

using namespace std;
typedef int ElemType;//元素的数据类型为Elemtype
typedef int KeyType;

typedef struct BiTNode {//定义二叉链表结构
	ElemType data;
	struct BiTNode * lchild, *rchild;//左右孩子指针
}BiTNode,*BiTree;


/**********************二叉排序树的查找算法***********************/
BiTree SrarchBST_1(BiTree T, KeyType key) {
	if ((!T) || EQ(key, T->data))
		return T;
	else if (LT(key, T->data))
		return (SrarchBST_1(T->lchild, key));
	else return (SrarchBST_1(T->rchild, key));
}

int SearchBST_2(BiTree T, KeyType key, BiTree f,BiTree &p) {
	if (!T) {
		p = f; return 0;//返回失败
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
	if (!SearchBST_2(T, e, NULL, p)) {//查找不成功
		s = (BiTree)malloc(sizeof(BiTNode));
		s->data = e; s->lchild = s->rchild = NULL;
		if (!p) {
			T = s;//被插入节点为新的节点
		}
		else if (LT(e, p->data))
			p->lchild = s;//被插入节点 *s为
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
	cout << "请输入关键字个数：";
	cin >> num;
	cout << "请依次输入关键字：" << endl;
	for (int i = 0; i < num; i++) {
		int temp = 0;
		cin >> temp;
		InsertBST(T, temp);
	}
	cout << "请输入你要查找的值：";
	cin >> key;
	p = SrarchBST_1(T, key);
	if (p) {
		cout <<"查找成功："<< p->data<<endl;
	}
	else
		cout << "未找到你要的关键字" << endl;
	Print(T);
	return 0;
}
