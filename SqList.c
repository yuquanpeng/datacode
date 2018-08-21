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
        
void Del_x_2(SqList &L,ELemType x){
	//将不等于x的元素前移kge位置
   int k = 0,i = 0;
   while(i<L.length){
   		if(L.data[i] == x)
   			k++;
   		else
   			L.data[i-k] = L.data[i];
    	i++; 
   }
   L.length -= k;
}
        
bool Del_s_t2(SqList &L,ElemType s,ElemType t){
	//算法思想，先寻找大于等于s的第一个元素 然后寻找值大于t的第一个元素
	//将这段元素删除 只需将后面的元素前移动即可
	int i,j;
   if(s>=t || L.length == 0)
    	return false;
   for(i=0;i<L.length && L.data[i]<s;i++);
   if(i>=L.length)
       return false;
   for(j=i;j<L.length && L.data[j]<=t;j++);
	for(;j<L.length;i++,j++)
   		L.data[i] = L.data[j];
	L.length = i+1;
	return true;
}
bool Del_s_t(SqList &L,ElemType s,ElemType t){
	//从前向后扫描顺序表，k记录s和t之间的元素个数
   //对于当前扫描的元素。若其值不再st之间 则前移k个位置；否则执行k++
   int i,k=0;
   if(L.length == 0||s>=t)
       return false;
   for(i=0;i<L.lenth;i++){
       if(L.data[i]>=s && L.data[i]<=t)
           k++;
   		else
   			L.data[i-k] = L.data[i];
       }
   L.length -= k;
   return true;
    
}
bool Delete_Same(SqList &L){
    //初始将第一个元素看作非重复的有序表，之后依次判断后面的元素是否与前面的有序表的最后一个元素相同，
	//如果相同则继续向后判断 or 插入到前面有序表的最后，直到判断到表尾为止
    if(L.length==0)
        return false;
    int i,j;//i存储第一个不相等的元素 j工作指针
    for(i=0,j=1;j<L.length;j++)
    	if(L.data[i]!=L.data[j])
    		L.data[++i] = L.data[j];
    L.length = i+1;
    return true;
}
bool MergeABtoC(SqList A,SqList B,SqList &C){
    //合并AB to C
	if(A.length+B.length>C.MaxSize)
       return false;
    int i=0,j=0,k=0;
    while(i<A.length&&j<B.length){
   		if(A.data[i]>B.data[j])
    		C.data[k++] = A.data[i];
		else
    		C.data[k++] = B.data[j];
   	}
    while(i<A.length)
    	C.data[k++] = A.data[i++];
    while(j<B.length)
    	C.data[k++] = B.data[j++];
    C.length = k+1;
    return true;
}
void Reverse(SqList &L,int left,int right,int arraySize){
    //逆转
	if(left>=right||right>=arraySize)
   		return ;
   	int mid = (left + right)/2;
   	for(int i=0;i<mid;i++){
   		ElemType temp = L.data[left+i];
    	L.data[left+i] = L.data[right-i];
       L.data[right-i] = temp;
    }    
}
void ExChange(SqList &L,int m,int n,int arraySize){
   //原地逆转总的，然后分别逆转
	Reverse(L,0,m+n-1,arraySize);
  	Reverse(L,0,n-1,arraySize);
   	Reverse(L,n,m+n-1,arraySize);
}
void SearchExchangeInsert(SqList &L,Elemtype x){
	int low =0,high=L.length-1,mid;
   	while(low<high){
   		mid = (low+high)/2;
       if(L.data[mid] == x)
       	break;
    	else if(L.data[mid]<x) low = mid+1;
       else high=mid-1; 
   }
   //下面两个if只会执行一个
	if(L.data[mid] == x&&mid!=L.length-1){
		//若最后一个元素与x相等 则不存在与其后继交换的操作
    	Elemtype t = L.data[mid];
    	L.data[mid] = L.data[mid+1];
    	L.data[mid+1] = t;
	}
   if(low>high){
   		for(int i=L.length-1;i>high;i--)
       	L.data[i+1] = L.data[i];
       L.data[i+1] = x;
   }
}
void ShiftLeftReverse(SqList &L,int from,int to){
	int i;
	for(i=0;i<(from+to)/2;i++){
   		ElemType temp = L.data[from+i];
    	L.data[from+i] = L.data[to-i];
    	L.data[to-i] = temp;
   }
}
void ShiftLeftP(SqList &L,int p){
	ShiftLeftReverse(L,0,p-1);
   	ShiftLeftReverse(L,p,L.length-1);
   	ShiftLeftReverse(L,0,L.length-1);

}
int main(){
 SqList list;
 InitSqList(&list);



	return 0;


}