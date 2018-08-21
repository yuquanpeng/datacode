#include<stdio.h>
#define MAXSIZE 5
/*静态链表
*/
typedef int ElemType;

typedef struct
{
	ElemType data;
	int cur;
}component, SLinkList[MAXSIZE];

int LocateElem_SL(SLinkList *S, ElemType elem);
void InitSpace_SL(SLinkList *space);
int Malloc_SL(SLinkList *space);
void Free_SL(SLinkList *space, int k);
void Difference_SL(SLinkList *space, int *S);

void main()
{
	int s;
	SLinkList space;
	InitSpace_SL(&space);
	Difference_SL(&space, &s);
}

/*int LocateElem_SL(SLinkList *S, ElemType elem)
{
	int i = S[0].cur;//I指示表中的第一个节点
	while (i && S[i].data != elem)//在表中顺联查找
		i = S[i].cur;
	return i;
}*/

void InitSpace_SL(SLinkList *space)
{
	//将一位数组space中各分量链接成一个被用链表 space[0].cur 位头指针
	for (int i = 0; i<MAXSIZE - 1; i++) 
	{
		space[i]->cur = i + 1;
		//space[i]->data = 0;
	}
	space[MAXSIZE - 1]->cur = 0;
}

int Malloc_SL(SLinkList *space)
{
	//返回分配的元素的下标
	int i = space[0]->cur;
	if (space[0]->cur) space[0]->cur = space[i]->cur;
	return i;
}
void Free_SL(SLinkList *space, int k)
{
	//将下标为k的节点回收到备用链表
	space[k]->cur = space[0]->cur;
	space[0]->cur = k;
}
void Difference_SL(SLinkList *space, int *S)
{
	InitSpace_SL(space);//初始化备用空间
	*S = Malloc_SL(space);//生成S的头结点
	int r = S;//r指向S的当前最后结点
	printf("请输入集合A和集合B的元素个数:\n");
	int m, n;
	scanf_s("%d %d", &m, &n);
	for (int j = 1; j <= m; j++)
	{
		int i = Malloc_SL(space);//分配节点
		scanf_s("%d", &space[i]->data);//输入A的元素的值
		space[r]->cur = i;  
		r = i;//插入到表尾
	}
	space[r]->cur = 0;  //A尾点的cur置0
	for (int j = 1; j <= n; j++) //依次输入B的元素  若不在当前表中则插入 否则删除
	{
		int b;
		scanf_s("%d", &b);
		int p = S; int k = space[*S]->cur;//将k指向集合A中的第一个节点
		while (k != space[r]->cur&&space[k]->data != b) //在当前表中查找
		{
			p = k; k = space[k]->cur;
		}
		if (k == space[r]->cur) //当前表中不存在钙元素  插入在r所指结点之后
		{
			int i = Malloc_SL(space);
			space[i]->data = b;
			space[i]->cur = space[r]->cur;
			space[r]->cur = i;//当表中不存在该元素，插入r所指节点后，且r的位置不变
		}
		else//钙元素已在表中 删除
		{
			space[p]->cur = space[k]->cur;
			Free_SL(space, k);
			if (r == k) 
				r = p;//r始终指向A的最后
		}
	}
}