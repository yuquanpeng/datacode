/*设 tag 法的循环队列入队*/
int EnQueue1(SqQueue ,ElemType x){
	if(Q.front == Q.rear && Q.tag==1)
		return 0;
	Q.data[Q.rear] = x;
	Q.rear = (Q.rear+1)%MaxSize;
	Q.tag = 1;
	return 1;
}
/*设 tag 法 循环队列的出队算法*/
int DeQueue(SqQueue &Q,ElemType &x){
	if(Q.front == Q.rear && Q.tag==0)
		return 0;
	x = Q.data[Q.front];
	Q.front = (Q.front+1) % MaxSize;
	Q.tag = 0;
	return 1;
}

/*利用两个栈 模拟一个队列*/
//入队算法
int EnQueue(Stack &S1,Stack &S2,ElemType e){
	if(!StackOverflow(S1)){
		Push(S1,e);
		return 1;
	}
	if(StackOverflow(S1)&&!StackEmpty(S2)){
		printf("队列满\n");
		return 0;
	}
	if(StackOverflow(S1)&&StackEmpty(S2)){
		while(!StackEmpty(S2)){
			Pop(S1,x);
			Push(S2,x);
		}
	}
	Push(S1,e);
	return 1;
}
//出队算法
void DeQueue(Stack &S1,Stack &S2,ElemType &x){
	if(!StackEmpty(S2)){
		Pop(S2,x);
	}else if(StackEmpty(S1)){
		printf("null\n");
	}else{
		while(!StackEmpty(S1)){
			Pop(S1,x);
			Push(S2,x);
		}
		Pop(S2,x);
	}
}
////////////////
void Train_Arrange(char *train){
	char *p = train,*q=train,c;
	Stack s;
	InitStack(s);
	while(*p){
		if(*p == 'H')
			Push(s,*p);
		else
			*(q++) = *p;
		p++
	}
	while(!StackEmpty(s)){
		Pop(s,c);
		*(q++) = c;
	}
}

////////
