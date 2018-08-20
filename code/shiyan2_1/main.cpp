#include<iostream>
using namespace std;

#define MAX 16 
#define AGAIN 10 

typedef struct//�����
{
	char *base;
	char *top;
	int stacksize;
}SqStackR;

typedef struct {//����
	float *base;
	float *top;
	int stacksize;
}SqStackD;

void InitStack(SqStackR &S) //�������ջ�ĳ�ʼ��
{        
	S.base = (char*)malloc(MAX * sizeof(char));
	if (!S.base) 
	{
		cout << "��������д���ʧ��" << endl;
		exit(0);
	}
	S.top = S.base;
	S.stacksize = MAX;
}   

void InitStack(SqStackD &S) //���ݶ�ջ�ĳ�ʼ��
{        
	S.base = (float *)malloc(MAX * sizeof(float));
	if (!S.base) 
	{
		cout << "���ݶ��д���ʧ��" << endl;
		exit(0);
	}
	S.top = S.base;
	S.stacksize = MAX;
} 
int StackEmpty(SqStackR &S) //�ж��Ƿ��ջ 
{  
	if (S.top == S.base)
		return 1;
	else
		return 0;
} 
int StackEmpty(SqStackD &S) //�ж��Ƿ��ջ
{
	if (S.top == S.base)
		return 1;
	else
		return 0;
} 

void DestroyStack(SqStackR &S) //�������������
{  
	S.top = S.base;
	S.stacksize = 0;
} 
void DestroyStack(SqStackD *S) //�������ݶ���
{
	S->top = S->base;
	S->stacksize = 0;
}  

void Push(SqStackR &S, char e) //�������ջ
{     
	int Top = (int)S.top, Base = (int)S.base;
	if ((Top - Base) == S.stacksize)//�ж�ջ����
	{
		S.base = (char *)realloc(S.base, (S.stacksize +AGAIN)*sizeof(char));
		if (!S.base)
		{
			cout << "���������������ʼ��ʧ��" << endl;
			exit(0);
		}
		S.top = S.base + S.stacksize;//�µ�վ��
		S.stacksize = S.stacksize + AGAIN;//�µ�վ�ĳ���
	}
	*(S.top) = e;
	S.top++;
}  
void Push(SqStackD &S, float e) //���ݵ���ջ
{
	int Top = (int)S.top, Base = (int)S.base;
	if ((Top - Base) == S.stacksize)
	{
		S.base = (float *)realloc(S.base, (S.stacksize +AGAIN)*sizeof(float));
		if (!S.base)
		{
			cout << "���ݶ���������ʼ��ʧ��" << endl;
			exit(0);
		}
		S.top = S.base + S.stacksize;
		S.stacksize = S.stacksize + AGAIN;
	}
	*(S.top) = e;
	S.top++;
}  


char Pop(SqStackR &S) //��ջ����ջ��Ԫ�غ�ɾ��ջ��Ԫ��

{
	char e;
	if (StackEmpty(S))
	{
		cout << "�����ջ�ǿյ�111" << endl;
		exit(0);
	}
	S.top--;
	e = *(S.top);
	return e;
}  

float Pop(SqStackD &S) //��ջ����ջ��Ԫ�غ�ɾ��ջ��Ԫ��
{
	float e;
	if (StackEmpty(S))
	{
		cout << "����ջ�ǿյ�124" << endl;
		exit(0);
	}
	S.top--;
	e = *(S.top);
	return e;
}  

char GetTop(SqStackR &S)//ȡ�����ջ��Ԫ��
{
	char e;
	if (StackEmpty(S))
	{
		cout << "�����ջ�ǿյ�137" << endl;
		exit(0);
	}
	e = *(S.top - 1);
	return e;
} 

float GetTop(SqStackD &S) {//ȡ����ջ��Ԫ��
	float e;
	if (StackEmpty(S))
	{
		cout << "����ջ�ǿյ�148" << endl;
		exit(0);
	}
	e = *(S.top - 1);
	return e;
} 

int OpJudge(char c)  //�ж��Ƿ�Ϊ�����
{
	char ch[7] = { '+','-','*','/','(',')','#' };
	for (int i = 0; i < 7; i++)
	{
		if (c == ch[i])
			return 1;
	}
	return 0;
} 

char OpPriority(char top, char c) 
{
	char ch;
	if (top == '(' && c == ')' || top == '#' && c == '#')
		ch = '=';
	else if (top == '+' || top == '-')     //ջ��Ԫ��Ϊ��+����-����ʱ��
			switch (c)
			{
			case '+':
			case '-': 
			case ')':
			case '#': ch = '>'; break;
			case '*':
			case '/':
			case '(': ch = '<';
			}
	else if (top == '*' || top == '/')    //ջ��Ԫ��Ϊ��*����/����ʱ��
		switch (c)
			{
			case '+':
			case '-':
			case '*':
			case '/':
			case ')':
			case '#': ch = '>'; break;
			case '(': ch = '<';
			}
	else if (top == '(')             //ջ��Ԫ��Ϊ��(����ʱ��
		switch (c)
			{
			case '+':
			case '-':
			case '*':
			case '/':
			case '(': ch = '<'; break;
			case '#':   cout<<"���ʽ��������201"<<endl;
				exit(0);
			}
	else if (top == ')')     /*ջ��Ԫ��Ϊ��)����ʱ��*/
		switch (c)
			{
			case '+':
			case '-':
			case '*':
			case '/':
			case '#': ch = '>'; break;
			case '(': cout << "���ʽ��������212" << endl;
				exit(0);
			}
	else if (top == '#')              /*ջ��Ԫ��Ϊ��#����ʱ��*/      
		switch (c)
			{
			case '+':
			case '-':
			case '*':
			case '/':
			case '(': ch = '<'; break;
			case ')':   cout << "���ʽ��������224" << endl;
				exit(0); 
			}
	return ch;
}


float Operate(float a, char r, float b) 
{
	float s, d1 = a, d2 = b;
	switch (r) 
	{
		case '+':s = d1 + d2; break;
		case '-':s = d2 - d1; break;
		case '*':s = d1 * d2; break;
		case '/':
			if (d1 == 0) 
				{ s = 0; break; } 
			s = d2 / d1; 
			break;
	}
	return s;
}


float Expression(char c[], SqStackR &S, SqStackD &D) {
	float a, b, s = 0, e = 1.0;
	int i = 0;
	char r;
	while (c[i] != '#' || GetTop(S) != '#')
	{
		if (!OpJudge(c[i]))
		{
			if (c[i] >= '0' && c[i] <= '9')
			{
				s += c[i] - '0';
				while (!OpJudge(c[++i])) //��С��λ���ж�
				{
					if (c[i] != '.')
					{
						s *= 10; 
						s += c[i] - '0';
					}
					else
					{
						while (!OpJudge(c[++i]))
						{
							e *= 0.1;
							s += (c[i] - '0') * e;
						}
						break;
					}
				}
				Push(D, s);
				s = 0; 
				e = 1.0;
			}
			else
			{
				cout << "���ʽ��������282" << endl;
				return 0;
			}
		}
		else
			switch (OpPriority(GetTop(S), c[i]))
			{
			case '<':
				Push(S, c[i]);
				i++;
				break;
			case '=':
				Pop(S);
				i++;
				break;
			case '>':
				r = Pop(S);
				a = Pop(D);
				b = Pop(D);
				Push(D, Operate(a, r, b));
				break;
			}
	}
	return (GetTop(D)); 
}

int main() 
{
	char c[50], x;
	SqStackR S;
	SqStackD D;
	InitStack(S);
	Push(S, '#');
	InitStack(D);
	float r = 0;//���
	for (int i = 0; i < 50; i++)
	{
		c[i] = '#';
	}
	cout<<"����һ����׼�ı��ʽ=��";
	for (int i = 0; i < 50; i++)
	{
		if ((x = getchar()) != 10)
			c[i] = x;
		else
			break;
	}
	r = Expression(c, S, D);
	cout << " = "<<r<<endl;
	return 0;
} 