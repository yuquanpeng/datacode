#include<iostream>
#include<string>
#define S_INIT_SIZE 100;//栈的存储空间初始量
#define S_AGAIN 10;//栈的存储空间增量
using namespace std;
typedef struct SqStack //利用栈处理：(θβ1β2…βm)→(θβm…β2θβ1θ)
{
	char *top;
	char *base;
	int stacksize;
}SqStack;

typedef struct QNode//利用队列处理B：tsaedsae （由B→tAdA, A→sae得）
{
	char word;
	struct QNode *next;
}QNode, * QPtr;
typedef struct 
{
	QPtr front;
	QPtr rear;
}LinkQueue;

//***********************栈的相关操作
void InitStack(SqStack &S)
{
	S.base = (char*)malloc(100 * sizeof(char));
	if (!S.base)
	{
		cout << "栈的内存分配失败" << endl;
		exit(0);
	}
	S.top = S.base;
	S.stacksize = S_INIT_SIZE;
}

void Push_S(SqStack &S,char e)
{
	char t;
	if (S.top - S.base >= S.stacksize)//栈满追加空间
	{
		S.base = (char*)realloc(S.base, (S.stacksize + 10)*sizeof(char));
		if (!S.base)
			cout << "新增栈空间分配失败" << endl;
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
		cout << "栈是空的52" << endl;
		exit(0);
	}
	else
		e = *--S.top;
}
int StackEmpty(SqStack &S)
{
	return S.top == S.base;
}
//##############################队列的相关操作
void InitQueue(LinkQueue &Q)
{
	Q.front = Q.rear = new QNode;
	if (!Q.front)
		cout << "队列初始化失败" << endl;
	Q.front->next = NULL;
}
void Push_Q(LinkQueue &Q, char e)
{
	QPtr p = new QNode;
	if (!p)
		cout << "空间分配失败78" << endl;
	p->word = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
}
void Pop_Q(LinkQueue &Q, char &e)
{
	if (Q.front == Q.rear)
		cout << "队列为空" << endl;  
	QPtr p = Q.front->next;  
	e = p->word;
	Q.front->next = p->next;  
	if (Q.rear == p)
		Q.rear = Q.front;//队列中只有一个结点的情况  
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
void ReadIn(SqStack &S)//将魔王语言压入栈中
{
	int left = 0, right = 0;
	int n;
	string m;
	cout << "请输入魔王de语言：";
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
		cout << "魔王语言输入错误" << endl;
	for (int i = n- 1; i >= 0; i--)
		Push_S(S,m[i]);
}
void Tranlate(SqStack &S1, SqStack &S2)      //处理规则2  
{
	char e, e1;
	SqStack S3;    //栈S3作为进行转换的中间变量  
	SqStack();
	while (!StackEmpty(S1))
	{
		Pop_S(S1, e);
		if (e == '(')
		{
			Pop_S(S2, e);
			e1 = e;       //e1中保存的就是魔王语言中（右边的第一个字母，就是第二种规则中的θ  
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
				Pop_S(S3, e);//根据第二种解释规则，将θ进行多次压栈操作  
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
	cout << "魔王语言可以解释为：";
	QPtr p = Q.front->next;
	while (p)
	{
		cout << p->word;
		p = p->next;
	}
	cout << endl;
	return 0;
}