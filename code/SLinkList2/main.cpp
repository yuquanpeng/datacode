#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEAIBLE -1
#define OVERFLOW -2
#define MAXSIZE 100
typedef int ElemType;
typedef int status;


typedef struct component {
	ElemType data;
	int next;
}SLinkList[MAXSIZE];

void InitSpace_SL(SLinkList &space)
{
	for (int i = 0; i<MAXSIZE - 1; i++)
	{
		space[i].next = i + 1;
	}
	space[MAXSIZE - 1].next = 0;
}//InitSpace_SL

 // put the first free node into the chain
status Malloc_SL(SLinkList &space)
{
	int i; // i is the first available node
	i = space[0].next;
	space[0].next = space[i].next;
	return i;
}//Malloc_SL 

 // recycle the deleted node 
 // and set it as the head of the free node chain
status FreeSpace_SL(SLinkList &space, int i)
{
	space[i].next = space[0].next;
	space[0].next = i;
	return OK;
}//FreeSpace_SL 

void Difference(SLinkList &space, int &head)
{
	int m, n, j, end, index, prev, i;
	ElemType e;
	InitSpace_SL(space);
	head = 1;
	index = head;
	printf("please input number of set A and B, seperated by space:\n ");
	scanf_s("%d %d", &m, &n);
	for (i = 0; i<m; i++)
	{
		//	printf("Please input the %dth number of set A:\n",i+1);
		j = Malloc_SL(space);
		scanf_s("%d", &space[j].data);
		space[index].next = j;
		index = j;
	}
	end = index;
	space[end].next = 0;
	for (i = 0; i<n; i++)
	{
		//	printf("Please input the %dth number of set B\n",i+1);
		scanf_s("%d", &e);
		if (head == 0) { // empty chain
			j = Malloc_SL(space);
			head = j;
			space[j].next = 0;
			end = j;
			continue;
		}
		index = head;
		while (space[index].data != e && space[index].next != 0)
		{
			prev = index;
			index = space[index].next;
		}
		if (space[index].data != e) // not found
		{
			end = index;
			j = Malloc_SL(space);
			space[j].data = e;
			space[j].next = space[end].next;
			space[end].next = j;
			end = j;
		}
		else  // found it
		{
			// is it the only node?
			if (head == end) {
				head = 0;
				FreeSpace_SL(space, index);
				continue;
			}
			// is it the head
			else if (index == head) {
				head = space[head].next;
				FreeSpace_SL(space, index);
				continue;
			}
			space[prev].next = space[index].next;
			FreeSpace_SL(space, index);
			if (index == end)
				end = prev;
		}
	}
}//Difference




int main()
{
	int head;
	SLinkList space;
	InitSpace_SL(space);
	Difference(space, head);
	printf("\nlet's print out the result:\n");
	if (head == 0) {
		printf("Oops, empety set!");
		return 0;
	}
	int index = head;
	while (space[index].next != 0) {
		printf("%d ", space[index].data);
		index = space[index].next;
	}
	printf("%d\n", space[index].data);
}