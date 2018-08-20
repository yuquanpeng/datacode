#include<iostream>
using namespace std;
typedef struct LNode {
	int data;
	struct LNode *next;
}LNode, *LinkList;
void josephus(LinkList r, int m, int n) {
	//r：（不带头结点的）单向循环链表的尾指针
	LinkList q, p = r;  //p：指向尾指针
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= m - 1; ++j)
			p = p->next;
		// p后移m-1次，定位于m-1处（要退席的人之前）
		q = p->next; //q定位于m人（要退席的人）
		cout << q->data << " ";//第m人报数
		p->next = q->next;   //第m人退席，删除第m人	
	}
}
int main()
{
	int m = 0;
	int n = 0;
	cout << "请输入围成圈的人数n=";
	cin >> n;
	cout << "请输入退下的人报出的数字m=";
	cin >> m;
	if (n < 0 || m < 0)
	{
		cout << "数组输入错误，程序退出";
		exit(-1);
	}

	LinkList p, r, cur;//p为当前节点  r为p的前驱节点 
	p = new LNode;
	if (!p)
	{
		cout << "链表创建错误，请检查39";
		exit(-1);
	}
	p->data = 1;
	p->next = p;//循环链表
	cur = p;
	for (int i = 2; i<=n; i++)
	{
		LinkList t = new LNode;
		if (!t)
		{
			cout << "链表创建错误，请检查50" << endl;
		}
		t->data = i;
		t->next = cur->next;
		cur->next = t;
		cur = t;
	}
	josephus(cur, m, n);
	return 0;
}
