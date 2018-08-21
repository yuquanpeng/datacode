#include<iostream>
using namespace std;
typedef struct LNode {
	int data;
	struct LNode *next;
}LNode, *LinkList;
void josephus(LinkList r, int m, int n) {
	//r��������ͷ���ģ�����ѭ�������βָ��
	LinkList q, p = r;  //p��ָ��βָ��
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= m - 1; ++j)
			p = p->next;
		// p����m-1�Σ���λ��m-1����Ҫ��ϯ����֮ǰ��
		q = p->next; //q��λ��m�ˣ�Ҫ��ϯ���ˣ�
		cout << q->data << " ";//��m�˱���
		p->next = q->next;   //��m����ϯ��ɾ����m��	
	}
}
int main()
{
	int m = 0;
	int n = 0;
	cout << "������Χ��Ȧ������n=";
	cin >> n;
	cout << "���������µ��˱���������m=";
	cin >> m;
	if (n < 0 || m < 0)
	{
		cout << "����������󣬳����˳�";
		exit(-1);
	}

	LinkList p, r, cur;//pΪ��ǰ�ڵ�  rΪp��ǰ���ڵ� 
	p = new LNode;
	if (!p)
	{
		cout << "��������������39";
		exit(-1);
	}
	p->data = 1;
	p->next = p;//ѭ������
	cur = p;
	for (int i = 2; i<=n; i++)
	{
		LinkList t = new LNode;
		if (!t)
		{
			cout << "��������������50" << endl;
		}
		t->data = i;
		t->next = cur->next;
		cur->next = t;
		cur = t;
	}
	josephus(cur, m, n);
	return 0;
}
