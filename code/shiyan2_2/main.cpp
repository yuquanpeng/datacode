#include<iostream>
#include<string>
#define S_INIT_SIZE 100;//ջ�Ĵ洢�ռ��ʼ��
#define S_AGAIN 10;//ջ�Ĵ洢�ռ�����
using namespace std;
typedef struct SqStack //����ջ����(�Ȧ�1��2����m)��(�Ȧ�m����2�Ȧ�1��)
{
	char *top;
	char *base;
	int stacksize;
}SqStack;

typedef struct QNode//���ö��д���B��tsaedsae ����B��tAdA, A��sae�ã�
{
	char word;
	struct QNode *next;
}QNode, * QPtr;
typedef struct 
{
	QPtr front;
	QPtr rear;
}LinkQueue;

//***********************ջ����ز���
void InitStack(SqStack &S)
{
	S.base = (char*)malloc(100 * sizeof(char));
	if (!S.base)
	{
		cout << "ջ���ڴ����ʧ��" << endl;
		exit(0);
	}
	S.top = S.base;
	S.stacksize = S_INIT_SIZE;
}

void Push_S(SqStack &S,char e)
{
	char t;
	if (S.top - S.base >= S.stacksize)//ջ��׷�ӿռ�
	{
		S.base = (char*)realloc(S.base, (S.stacksize + 10)*sizeof(char));
		if (!S.base)
			cout << "����ջ�ռ����ʧ��" << endl;
		S.top = S.base + S.stacksize;
		S.stacksize += S_AGAIN;
	}
	*S.top++ = e;
	t = *S.top--;
}
void Pop_S(SqStack &S,char &e)
{
	if (S.top == S.base)
	{
		cout << "ջ�ǿյ�52" << endl;
		exit(0);
	}
	else
		e = *--S.top;
}
int StackEmpty(SqStack &S)
{
	return S.top == S.base;
}
//##############################���е���ز���
void InitQueue(LinkQueue &Q)
{
	Q.front = Q.rear = new QNode;
	if (!Q.front)
		cout << "���г�ʼ��ʧ��" << endl;
	Q.front->next = NULL;
}
void Push_Q(LinkQueue &Q, char e)
{
	QPtr p = new QNode;
	if (!p)
		cout << "�ռ����ʧ��78" << endl;
	p->word = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
}
void Pop_Q(LinkQueue &Q, char &e)
{
	if (Q.front == Q.rear)
		cout << "����Ϊ��" << endl;  
	QPtr p = Q.front->next;  
	e = p->word;
	Q.front->next = p->next;  
	if (Q.rear == p)
		Q.rear = Q.front;//������ֻ��һ���������  
	delete p;
}

int QueueEmpty(LinkQueue &Q)
{
	if (Q.front == Q.rear)
		return 1;
	return 0;
}
void A_Push_Q(LinkQueue &Q)
{
	Push_Q(Q, 's');
	Push_Q(Q, 'a');
	Push_Q(Q, 'e');
}
void B_Push_Q(LinkQueue &Q)
{
	Push_Q(Q, 't');
	A_Push_Q(Q);
	Push_Q(Q, 'd');
	A_Push_Q(Q);
}
void ReadIn(SqStack &S)//��ħ������ѹ��ջ��
{
	int left = 0, right = 0;
	int n;
	string m;
	cout << "������ħ��de���ԣ�";
	cin >> m;
	n = m.length();
	for (int i = 0; i < n; i++)
	{
		if (m[i] == '(')
			left++;
		else if (m[i] == ')')
			right++;
	}
	if (left != right)
		cout << "ħ�������������" << endl;
	for (int i = n- 1; i >= 0; i--)
		Push_S(S,m[i]);
}
void Tranlate(SqStack &S1, SqStack &S2)      //�������2  
{
	char e, e1;
	SqStack S3;    //ջS3��Ϊ����ת�����м����  
	SqStack();
	while (!StackEmpty(S1))
	{
		Pop_S(S1, e);
		if (e == '(')
		{
			Pop_S(S2, e);
			e1 = e;       //e1�б���ľ���ħ�������У��ұߵĵ�һ����ĸ�����ǵڶ��ֹ����еĦ�  
			if (e != ')')
				Pop_S(S1, e);
			while (e != ')')
			{
				Push_S(S3, e);
				Pop_S(S1, e);
			}
			while (!StackEmpty(S3))
			{
				Push_S(S2, e1);
				Pop_S(S3, e);//���ݵڶ��ֽ��͹��򣬽��Ƚ��ж��ѹջ����  
				Push_S(S2, e);
			}
			Push_S(S2, e1);
		}
	}
}
int main()
{
	char e=' ';
	SqStack S, S1, S2;
	LinkQueue Q;
	InitQueue(Q);
	InitStack(S);
	InitStack(S1);
	InitStack(S2);

	ReadIn(S);

	while (!StackEmpty(S))
	{
		Push_S(S, e);
		if (e == ')')
		{
			Push_S(S1, e);
			Pop_S(S2, e);
			while (e!='(')
			{
				Push_S(S1, e);
				Pop_S(S2, e);
			}
			if (e == '(')
				Push_S(S1, e);
			Tranlate(S1, S2);
		}
		else
			Push_S(S2, e);
	}
	while (!StackEmpty(S2))
	{
		Pop_S(S2, e);
		Push_S(S, e);
	}
	while (!StackEmpty(S))
	{
		Pop_S(S, e);
		if (e == 'A')
			A_Push_Q(Q);
		if (e == 'B')
			B_Push_Q(Q);
		else
			Pop_Q(Q, e);
	}
	cout << "ħ�����Կ��Խ���Ϊ��";
	QPtr p = Q.front->next;
	while (p)
	{
		cout << p->word;
		p = p->next;
	}
	cout << endl;
	return 0;
}