#include<iostream>
using namespace std;

#define MAX 16 
#define AGAIN 10 

typedef struct//运算符
{
	char *base;
	char *top;
	int stacksize;
}SqStackR;

typedef struct {//数据
	float *base;
	float *top;
	int stacksize;
}SqStackD;

void InitStack(SqStackR &S) //运算符堆栈的初始化
{        
	S.base = (char*)malloc(MAX * sizeof(char));
	if (!S.base) 
	{
		cout << "运算符队列创建失败" << endl;
		exit(0);
	}
	S.top = S.base;
	S.stacksize = MAX;
}   

void InitStack(SqStackD &S) //数据堆栈的初始化
{        
	S.base = (float *)malloc(MAX * sizeof(float));
	if (!S.base) 
	{
		cout << "数据队列创建失败" << endl;
		exit(0);
	}
	S.top = S.base;
	S.stacksize = MAX;
} 
int StackEmpty(SqStackR &S) //判断是否空栈 
{  
	if (S.top == S.base)
		return 1;
	else
		return 0;
} 
int StackEmpty(SqStackD &S) //判断是否空栈
{
	if (S.top == S.base)
		return 1;
	else
		return 0;
} 

void DestroyStack(SqStackR &S) //销毁运算符队列
{  
	S.top = S.base;
	S.stacksize = 0;
} 
void DestroyStack(SqStackD *S) //销毁数据队列
{
	S->top = S->base;
	S->stacksize = 0;
}  

void Push(SqStackR &S, char e) //运算符入栈
{     
	int Top = (int)S.top, Base = (int)S.base;
	if ((Top - Base) == S.stacksize)//判断栈满否
	{
		S.base = (char *)realloc(S.base, (S.stacksize +AGAIN)*sizeof(char));
		if (!S.base)
		{
			cout << "运算符队列新增初始化失败" << endl;
			exit(0);
		}
		S.top = S.base + S.stacksize;//新的站定
		S.stacksize = S.stacksize + AGAIN;//新的站的长度
	}
	*(S.top) = e;
	S.top++;
}  
void Push(SqStackD &S, float e) //数据的入栈
{
	int Top = (int)S.top, Base = (int)S.base;
	if ((Top - Base) == S.stacksize)
	{
		S.base = (float *)realloc(S.base, (S.stacksize +AGAIN)*sizeof(float));
		if (!S.base)
		{
			cout << "数据队列新增初始化失败" << endl;
			exit(0);
		}
		S.top = S.base + S.stacksize;
		S.stacksize = S.stacksize + AGAIN;
	}
	*(S.top) = e;
	S.top++;
}  


char Pop(SqStackR &S) //出栈返回栈顶元素后删除栈顶元素

{
	char e;
	if (StackEmpty(S))
	{
		cout << "运算符栈是空的111" << endl;
		exit(0);
	}
	S.top--;
	e = *(S.top);
	return e;
}  

float Pop(SqStackD &S) //出栈返回栈顶元素后删除栈顶元素
{
	float e;
	if (StackEmpty(S))
	{
		cout << "数据栈是空的124" << endl;
		exit(0);
	}
	S.top--;
	e = *(S.top);
	return e;
}  

char GetTop(SqStackR &S)//取运算符栈顶元素
{
	char e;
	if (StackEmpty(S))
	{
		cout << "运算符栈是空的137" << endl;
		exit(0);
	}
	e = *(S.top - 1);
	return e;
} 

float GetTop(SqStackD &S) {//取数据栈顶元素
	float e;
	if (StackEmpty(S))
	{
		cout << "数据栈是空的148" << endl;
		exit(0);
	}
	e = *(S.top - 1);
	return e;
} 

int OpJudge(char c)  //判断是否为运算符
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
	else if (top == '+' || top == '-')     //栈顶元素为‘+’或‘-’的时候
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
	else if (top == '*' || top == '/')    //栈顶元素为‘*’或‘/’的时候
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
	else if (top == '(')             //栈顶元素为‘(’的时候
		switch (c)
			{
			case '+':
			case '-':
			case '*':
			case '/':
			case '(': ch = '<'; break;
			case '#':   cout<<"表达式解析错误201"<<endl;
				exit(0);
			}
	else if (top == ')')     /*栈顶元素为‘)’的时候*/
		switch (c)
			{
			case '+':
			case '-':
			case '*':
			case '/':
			case '#': ch = '>'; break;
			case '(': cout << "表达式解析错误212" << endl;
				exit(0);
			}
	else if (top == '#')              /*栈顶元素为‘#’的时候*/      
		switch (c)
			{
			case '+':
			case '-':
			case '*':
			case '/':
			case '(': ch = '<'; break;
			case ')':   cout << "表达式解析错误224" << endl;
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
				while (!OpJudge(c[++i])) //对小数位的判断
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
				cout << "表达式解析错误282" << endl;
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
	float r = 0;//结果
	for (int i = 0; i < 50; i++)
	{
		c[i] = '#';
	}
	cout<<"输入一个标准的表达式=：";
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