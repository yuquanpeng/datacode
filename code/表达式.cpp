#include <stdio.h> 
#include <stdlib.h> 
#include <malloc.h> 
#include<cstdlib> 
 
#define MAX 16 
#define AGAIN 10 
typedef char R_SElemType;  //针对运算符// 
typedef float D_SElemType;  //针对数据// 
typedef struct   
{ 
 R_SElemType  *base; 
 R_SElemType *top; 
 int stacksize; 
}SqStackR; 
 
typedef struct{ 
 D_SElemType *base; 
 D_SElemType *top; 
 int stacksize; 
}SqStackD; 
 
void InitStack(SqStackR *S){        //针对运算符堆栈的初始化// 
 S->base = (R_SElemType *)malloc(MAX * sizeof(R_SElemType)); 
 if (!S->base){ 
  printf("糟糕出初始存储空间分配失败"); 
  exit(0); 
 } 
 S->top = S->base;
 S->stacksize = MAX; 
}  //初始化堆栈// 
 
void InitStack(SqStackD *S){        //针对数据堆栈的初始
 S->base = (D_SElemType *)malloc(MAX * sizeof(D_SElemType)); 
 if (!S->base){ 
  printf("糟糕出初始存储空间分配失败"); 
  exit(0); 
 } 
 S->top = S->base; 
 S->stacksize = MAX; 
}  //初始化堆栈// 

int StackEmpty(SqStackR *S){  //针对运算符的清空// 
 if(S->top == S->base) 
  return 1; 
 else 
  return 0; 
} //判断是否空栈// 
 
 
int StackEmpty(SqStackD *S){  
 if(S->top == S->base) 
  return 1; 
 else 
  return 0; 
} //判断是否空栈// 
 
void DestroyStack(SqStackR *S){  //针对字符的清空// 
 S->top = S->base; 
 S->stacksize=0; 
} //销毁// 
 
void DestroyStack(SqStackD *S){  //针对数据的清空// 
 S->top = S->base; 
 S->stacksize=0; 
} //销毁// 
 
void Push(SqStackR *S,R_SElemType e){      //针对运算符的入栈// 
 //int T = (int)S->top,B =(int)S->base; 
 if ((S->top - S->base) == (S->stacksize)*sizeof(char))//判断栈满否
 { 
  S->base = (R_SElemType *)realloc(S->base ,(S->stacksize + AGAIN)*sizeof(R_SElemType)); 
  if (!S->base) 
  { 
   printf("糟糕堆栈的重新分配失败悲剧啦"); 
   exit(0); 
  } 
  S->top = S->base + S->stacksize; 
  S->stacksize = S->stacksize + AGAIN; 
 } 
 *(S->top) = e; 
 S->top++; 
}  //入栈// 
void Push(SqStackD *S,D_SElemType e){      //针对运算符的入栈// 
 //int T = (int)S->top,B =(int)S->base; 
 if ((S->top - S->base) == (S->stacksize)*sizeof(float))//判断栈满否
 { 
  S->base = (D_SElemType *)realloc(S->base ,(S->stacksize + AGAIN)*sizeof(D_SElemType)); 
  if (!S->base) 
  { 
   printf("糟糕堆栈的重新分配失败悲剧啦"); 
   exit(0); 
  } 
  S->top = S->base + S->stacksize; 
  S->stacksize = S->stacksize + AGAIN; 
 } 
 *(S->top) = e; 
 S->top++; 
}  //入栈// 
 
 
char Pop(SqStackR *S){ 
 R_SElemType e; 
 if (StackEmpty(S)) 
 { 
  printf("堆栈是空的。"); 
  exit(0); 
 } 
 S->top--; 
 e = *(S->top); 
 return e; 
}  //出栈e返回栈顶元素后删除栈顶元素// 
 
 
float Pop(SqStackD *S){ 
 D_SElemType e; 
 if (StackEmpty(S)) 
 { 
  printf("堆栈是空的。"); 
  exit(0); 
 } 
 S->top--; 
 e = *(S->top); 
 return e; 
}  //出栈e返回栈顶元素后删除栈顶元素// 

char GetTop(SqStackR *S){ 
 char e; 
 if (StackEmpty(S)) 
 { 
  printf("堆栈是空的。"); 
  exit(0); 
 } 
 e = *(S->top - 1); 
 return e; 
} //取栈顶元素// 
 
float GetTop(SqStackD *S){ 
 float e; 
 if (StackEmpty(S)) 
 { 
  printf("堆栈是空的。"); 
  exit(0); 
 } 
 e = *(S->top - 1); 
 return e; 
} //取栈顶元素// 
 
int Determine(char c){ 
 char ch[7] = {'+','-','*','/','\n','(',')'}; 
 int i; 
 for (i = 0;i < 7;i++) 
 { 
  if(c == ch[i]) 
   return 1; 
 } 
 return 0; 
}  //判断是否为字符// 
 
char OperatorPriority(char top,char c){ 
 char ch; 
 if (top == '(' && c == ')' ||top == '\n' && c == '\n') 
  ch = '='; 
 else  
  if(top=='+' || top=='-')     //栈顶元素为‘+’或‘-’的时候// 
   switch(c) 
  { 
   case '+': 
   case '-': 
   case ')': 
   case '\n': ch = '>'; break; 
   case '*': 
   case '/': 
   case '(': ch = '<'; 
  } 
  else  
   if(top=='*' || top=='/')    /*栈顶元素为‘*’或‘/’的时候*/ 
    switch(c) 
   { 
    case '+': 
    case '-': 
    case '*': 
    case '/':      
    case ')': 
    case '\n':    ch = '>'; break; 
    case '(':    ch = '<';  
   } 
   else 
    if(top=='(')             /*栈顶元素为‘(’的时候*/ 
     switch(c) 
    {  
     case '+': 
     case '-': 
     case '*': 
     case '/':  
     case '(': ch = '<'; break;  
     case '\n':   printf("悲剧出错啦!------(温馨提示错误1)\n"); 
exit(0); 
    } 
    else 
     if(top==')')     /*栈顶元素为‘)’的时候*/ 
      switch(c) 
     { 
      case '+': 
      case '-': 
      case '*': 
      case '/':  
      case '\n': ch = '>'; break;  
      case '(': printf("悲剧出错啦!-------(温馨提示错误2)\n"); 
exit(0); 
     } 
     else  
      if(top=='\n')              /*栈顶元素为‘#’的时候*/
	      switch(c) 
      { 
       case '+': 
       case '-': 
       case '*': 
       case '/':  
       case '(': ch = '<'; break;  
       case ')':   printf("悲剧出错啦!-------(温馨错误3)\n"); exit(0); 
      }  
      return ch;                               
} 
 
 
float Operate(float a,char r,float b){ 
 float s, d1 = a, d2 = b; 
 switch(r){ 
 case '+':s = d1 + d2;break; 
 case '-':s = d2 - d1;break; 
 case '*':s = d1 * d2;break; 
 case '/':if(d1 == 0){s = 0; break;} s = d2 / d1;break; 
 } 
 return s; 
} 
 
 
float Expression(char c[],SqStackR *S,SqStackD *D){ 
 float a,b,s = 0,e = 1.0; 
 int i = 0; 
 char r; 
// SqStackR S; 
// SqStackD D; 
// InitStack(&S); 
// Push(&S,'\n'); 
// InitStack(&D); 
 i = 0; 
 while (c[i] != '\n' || GetTop(S) != '\n') 
 { 
  if (!Determine(c[i])) 
  { 
   if (c[i] >= '0' && c[i] <= '9') 
   { 
    s += c[i] - '0'; 
    while(!Determine(c[++i]))     { 
     if (c[i] != '.') 
     { 
      s *= 10; s += c[i] - '0'; 
     } 
     else 
     { 
      while(!Determine(c[++i])) 
      { 
       e *= 0.1; 
       s += (c[i] - '0') * e; 
      } 
      break; 
     } 
    } 
    Push(D,s); 
    s = 0; e = 1.0; 
   } 
   else 
   { 
    printf(" 好一个悲剧出错啦!"); 
    return 0; 
   } 
  } 
  else 
   switch(OperatorPriority(GetTop(S),c[i])) 
  { 
   case '<': 
    Push(S,c[i]); 
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
    Push(D,Operate(a,r,b)); 
    break; 
  } 
 } 
 return (GetTop(D)); 
 } 
 
int main(){ 
 char c[20],x; 
 int i = 0; 
 SqStackR S; 
 SqStackD D; 
 InitStack(&S); 
 Push(&S,'\n'); 
 InitStack(&D); 
 float r = 0; 
  
 for (i = 0;i < 20;i++) 
 { 
  c[i] = '\n'; 
 } 
 printf("开始输入啦\n"); 
 for(i = 0 ; i < 30 ;i++) 
 { 
  if((x = getchar())!= 10) 
   c[i] = x; 
  else 
   break; 
 } 
 r = Expression(c , &S ,&D); 
 
 printf("= %.2f \n",r); 
 getchar(); 
 return 0;
}
