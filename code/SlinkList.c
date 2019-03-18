#include<stdio.h> 
#define Maxsize 100
typedef int elemtype,status;
typedef struct
{
	int cur;
	elemtype data;
}component,SLinkList[Maxsize];/*SLinkList是一个结构体数组*/
void Initspace_SL(SLinkList &space)/*将一维数组space中各分量链成一个备用链表 */
{
	int i;
	for(i=0;i<Maxsize-1;i++)
		space[i].cur=i+1;
	space[Maxsize-1].cur=0;
}
int LocateElem(SLinkList &space,int e)/在静态的单链线性表中查找第一个值为e的元素*/
{
	int i;
	i=space[0].cur;
	while(i&&space[i].data!=e)
		i=space[i].cur;
	return i;
}
int Malloc_SL(SLinkList &space)/*若备用空间链表非空，则返回分配的结点下标*/
{
	int i;
	i=space[0].cur;
	if(space[0].cur)
		space[0].cur=space[i].cur;
	return(i);
}
status Insert_SLinkList(SLinkList &space,int i,elemtype e)/*在静态单链表中第i个位置之前插入一个元素e*/
{
	int j=1,m;
	while(j<i-1)
		j=space[j].cur;
	m=Malloc_SL(space);
	space[m].data=e;
	space[m].cur=space[j].cur;
	space[j].cur=m;
	return 1;
}
void free(SLinkList &space,int k)/*将下标为k的空闲结点回收到备用链表*/
{
	space[k].cur=space[0].cur;
	space[0].cur=k;
}
status Delet_SL(SLinkList &space,int i,elemtype e)/*删除静态单链表中第i个元素并用e返回其值*/
{
	int j=1,k=Maxsize-1;
	for(j=1;j<i;j++)
	k=space[k].cur;
	j=space[k].cur;
	space[k].cur=space[j].cur;
	e=space[j].data;
	free(space,j);
	return e;
}
void main()/*还有求链表长度，以及求链表前驱后继的函数以后有空再写*/
{
	SLinkList La;
	int length,i,e;
	printf("请输入链表的长度:\n");
	scanf("%d",&length);
	Initspace_SL(La);
	printf("请输入链表的元素:\n");
	for(i=0;i<length;i++)
		scanf("%d",&La[i].data);
	printf("请输入要删除元素的位置:\n");
	scanf("%d",&i);
	e=Delet_SL(La,i,e);
	printf("要删除的元素的值是:%d\n",e);
	printf("请输入要插入元素的位置:\n");
	scanf("%d",&i);
	printf("要插入的元素的值是:\n");
	scanf("%d",&e);
	Insert_SLinkList(La,i,e);
	for(i=0;i<length;i++)
		printf("%d ",La[i].data);

