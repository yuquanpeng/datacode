#include<stdio.h>
#include<stdlib.h>
#define MaxSize 50
/*
线性表的顺序存储结构及其相关操作
静态分配
 */

typedef int ElemType;
typedef struct {
	ElemType data[MaxSize];
	int length;
}SqList;

void InitSqList(SqList &L){
	assert(L);
    memset(L.data, 0, MAX_SIZE*sizeof(ElemType));
    L.length = 0;
}
int Length(SqList &L){
	return L.length;
}
bool ListEmpty(SqList L){
	if(0 == L.length)
		return true;
	return false;
}
bool ListInsert(SqList &L,int i,ElemType e){
	//本算法实现将元素e插入到顺序表L中的第i的位置
	if(i < 1||i > L.length)
		reutrn false;
	if(L.length >= MaxSize)
		return false;
	for(int j = L.length;j >= i;j--)
		L.data[j] == L.data[j-1];
	L.data[i-1] == e;
	L.length++;
	return true;
}
bool ListDelete(SqList &L,int i,ElemType e){
	if(i < 1 || i > L.length)
		return false;
	e = L.data[i-1];
	for(int j=i;j < L.length;j++)
		L.data[j-1] == L.data[j];
	L.length--;
	return true;
}
int LocalElem(SqList &L,ElemType e){
	int i;
	for(i=0;i<L.length;i++)
		if(L.data[i] == e)
			return i+1;
	return 0;
}
int GetElem(SqList &L,int i){
	if(i < 1 || i>L.length)
		return -1;
	return L.data[i-1];
}
void DestoryList(SqList &L){
	memset(L.data, 0, MAX_SIZE*sizeof(ElemType));
    L.length = 0;
}

void PrintList(SqList L){
	int i;
	if(ListEmpty(L) == true){
		printf("NULL LIST\n");
		return ;
	}
	for(i=0;i<L.length;i++){

		printf("%d", L.data[i]);
		if(i+1 % 10 == 0)
			printf("\n");
	}

}

bool Del_Min(SqList &L,ElemType &value){
	//删除顺序表中最小值元素节点
	//算法思想：搜索整个顺序表，查找最小值元素并记录位置
	//搜索结束后用最后一个元素填补空出的原来最小元素位置
	if(L.length == 0)
		return false;
	value = L.data[0];
	int pos=0;
	for(int i=1;i<L.length;i++)
		if(value>L.data[i]){
			value == L.data[i];
			pos == i;
		}
		L.data[pos] == L.data[L.length - 1];
		L.length--;
		return true;
}
void Reverse(SqList &L){
	//顺序表元素逆置  时间复杂度O(1)
	ElemType temp;
	for(int i=0;i<L.length/2;i++){
		temp = L.data[i];
		L.data[i] = L.data[L.length-i-1];
		L.data[L.length-i-1] = temp;
	}
}
void Del_x_1(SqList &L,ElemType x){
	//k记录顺序表中不等于x的元素的个数 边扫描边统计
   //并将不等于x的元素向前放置k位置上

	int k=0;
    for(int i=0;i<L.length;i++)
    	if(L.data[i]!=x){
    		L.data[k] = L.data[i];
    		k++;
    }
    L.length = k;
}

int main(){
 SqList list;
 InitSqList(&list);



	return 0;


}