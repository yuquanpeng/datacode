#include <stdio.h> 
#include <stdlib.h> 
#include <malloc.h> 
#include<cstdlib> 
 
#define MAX 16 
#define AGAIN 10 
typedef char R_SElemType;  //��������// 
typedef float D_SElemType;  //�������// 
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
 
void InitStack(SqStackR *S){        //����������ջ�ĳ�ʼ��// 
 S->base = (R_SElemType *)malloc(MAX * sizeof(R_SElemType)); 
 if (!S->base){ 
  printf("��⪫����ʼ�洢�ռ����ʧ�ܪ�"); 
  exit(0); 
 } 
 S->top = S->base;
 S->stacksize = MAX; 
}  //��ʼ����ջ// 
 
void InitStack(SqStackD *S){        //������ݶ�ջ�ĳ�ʼ
 S->base = (D_SElemType *)malloc(MAX * sizeof(D_SElemType)); 
 if (!S->base){ 
  printf("��⪫����ʼ�洢�ռ����ʧ�ܪ�"); 
  exit(0); 
 } 
 S->top = S->base; 
 S->stacksize = MAX; 
}  //��ʼ����ջ// 

int StackEmpty(SqStackR *S){  //�������������// 
 if(S->top == S->base) 
  return 1; 
 else 
  return 0; 
} //�ж��Ƿ��ջ// 
 
 
int StackEmpty(SqStackD *S){  
 if(S->top == S->base) 
  return 1; 
 else 
  return 0; 
} //�ж��Ƿ��ջ// 
 
void DestroyStack(SqStackR *S){  //����ַ������// 
 S->top = S->base; 
 S->stacksize=0; 
} //����// 
 
void DestroyStack(SqStackD *S){  //������ݵ����// 
 S->top = S->base; 
 S->stacksize=0; 
} //����// 
 
void Push(SqStackR *S,R_SElemType e){      //������������ջ// 
 //int T = (int)S->top,B =(int)S->base; 
 if ((S->top - S->base) == (S->stacksize)*sizeof(char))//�ж�ջ����
 { 
  S->base = (R_SElemType *)realloc(S->base ,(S->stacksize + AGAIN)*sizeof(R_SElemType)); 
  if (!S->base) 
  { 
   printf("��⪫��ջ�����·���ʧ�ܪ���������"); 
   exit(0); 
  } 
  S->top = S->base + S->stacksize; 
  S->stacksize = S->stacksize + AGAIN; 
 } 
 *(S->top) = e; 
 S->top++; 
}  //��ջ// 
void Push(SqStackD *S,D_SElemType e){      //������������ջ// 
 //int T = (int)S->top,B =(int)S->base; 
 if ((S->top - S->base) == (S->stacksize)*sizeof(float))//�ж�ջ����
 { 
  S->base = (D_SElemType *)realloc(S->base ,(S->stacksize + AGAIN)*sizeof(D_SElemType)); 
  if (!S->base) 
  { 
   printf("��⪫��ջ�����·���ʧ�ܪ���������"); 
   exit(0); 
  } 
  S->top = S->base + S->stacksize; 
  S->stacksize = S->stacksize + AGAIN; 
 } 
 *(S->top) = e; 
 S->top++; 
}  //��ջ// 
 
 
char Pop(SqStackR *S){ 
 R_SElemType e; 
 if (StackEmpty(S)) 
 { 
  printf("��ջ�ǿյġ�"); 
  exit(0); 
 } 
 S->top--; 
 e = *(S->top); 
 return e; 
}  //��ջ��e����ջ��Ԫ�غ�ɾ��ջ��Ԫ��// 
 
 
float Pop(SqStackD *S){ 
 D_SElemType e; 
 if (StackEmpty(S)) 
 { 
  printf("��ջ�ǿյġ�"); 
  exit(0); 
 } 
 S->top--; 
 e = *(S->top); 
 return e; 
}  //��ջ��e����ջ��Ԫ�غ�ɾ��ջ��Ԫ��// 

char GetTop(SqStackR *S){ 
 char e; 
 if (StackEmpty(S)) 
 { 
  printf("��ջ�ǿյġ�"); 
  exit(0); 
 } 
 e = *(S->top - 1); 
 return e; 
} //ȡջ��Ԫ��// 
 
float GetTop(SqStackD *S){ 
 float e; 
 if (StackEmpty(S)) 
 { 
  printf("��ջ�ǿյġ�"); 
  exit(0); 
 } 
 e = *(S->top - 1); 
 return e; 
} //ȡջ��Ԫ��// 
 
int Determine(char c){ 
 char ch[7] = {'+','-','*','/','\n','(',')'}; 
 int i; 
 for (i = 0;i < 7;i++) 
 { 
  if(c == ch[i]) 
   return 1; 
 } 
 return 0; 
}  //�ж��Ƿ�Ϊ�ַ�// 
 
char OperatorPriority(char top,char c){ 
 char ch; 
 if (top == '(' && c == ')' ||top == '\n' && c == '\n') 
  ch = '='; 
 else  
  if(top=='+' || top=='-')     //ջ��Ԫ��Ϊ��+����-����ʱ��// 
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
   if(top=='*' || top=='/')    /*ջ��Ԫ��Ϊ��*����/����ʱ��*/ 
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
    if(top=='(')             /*ջ��Ԫ��Ϊ��(����ʱ��*/ 
     switch(c) 
    {  
     case '+': 
     case '-': 
     case '*': 
     case '/':  
     case '(': ch = '<'; break;  
     case '\n':   printf("���窫������!------(��ܰ��ʾ������1)\n"); 
exit(0); 
    } 
    else 
     if(top==')')     /*ջ��Ԫ��Ϊ��)����ʱ��*/ 
      switch(c) 
     { 
      case '+': 
      case '-': 
      case '*': 
      case '/':  
      case '\n': ch = '>'; break;  
      case '(': printf("���������!-------(��ܰ��ʾ������2)\n"); 
exit(0); 
     } 
     else  
      if(top=='\n')              /*ջ��Ԫ��Ϊ��#����ʱ��*/
	      switch(c) 
      { 
       case '+': 
       case '-': 
       case '*': 
       case '/':  
       case '(': ch = '<'; break;  
       case ')':   printf("���窬������!-------(��ܰ����3)\n"); exit(0); 
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
    printf(" ��һ�����窫������!"); 
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
 printf("��ʼ��������\n"); 
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
