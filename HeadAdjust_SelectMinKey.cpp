#include<iostream>
#include<time.h>
using namespace std;

#define LIST_INIT_SIZE 100 //线性表存储空间的初始分配量
#define LISTINCREMENT 10//分配增量
#define random(x) (rand()%x)//随机数

int compareNum[2];//用来记录比较的次数
int changeNum[2];//用来比较交换的次数 

typedef struct
{
	int *elem; //存储空间基址 存储数据的类型
	int length; //当前长度
	int listsize;   //当前分配的存储容量
}SqList;



void InitList_Sq(SqList &L)
{
	//构造一个空的线性表
	L.elem = (int *)malloc(LIST_INIT_SIZE * sizeof(int));
	if (!L.elem)
	{
		cout << "链表创建失败/n";
		exit(1);
	}
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
}

void InsertList_Sq(SqList &L, int i, int e)
{
	int *newbase = NULL;
	int *p, *q;
	if (i<1 || i>L.length+1)
	{
		cout << "插入点i值超标 错误" << endl;
		exit(1);
	}
	if (L.length >= L.listsize)
	{
		newbase = (int*)realloc(L.elem, (L.listsize + LISTINCREMENT)*sizeof(int));

		if (!newbase)
		{
			cout << "新增空间分配错误!!/n";
			exit(1);
		}
		L.elem = newbase;//新基址
		L.listsize = L.listsize + LISTINCREMENT;//增加存储容量
	}
	q = &(L.elem[i - 1]);//插入位置
	for (p = &(L.elem[L.length - 1]); p >= q; p--)//元素右移动
	{
		*(p + 1) = *p;
	}
	*q = e;//插入e
	++L.length;//表增长1

}

void PrintSqList(SqList &L,int num)
{
	int i;
	if (L.length == 0)
	{
		cout << "错误 空表\n";
		return;
	}
	for (i = 0; i < num; i++)
		cout << L.elem[i]<<", ";
	cout << endl;
}
/*********************简单排序算法***********************/
int SelectMinKey(SqList &L, int i)
{
	int k = 0;
	compareNum[0] += L.length - i;
	for (k = i; i < L.length; i++)
	{
		compareNum[0]++;//记录的是i与length的比较
		compareNum[0]++;//下面的选择语句中的比较
		if (L.elem[i] > L.elem[k])
		{
			k = i; changeNum[0]++;
		}
	}
	return k;
}

void SelectSort(SqList &L)
{
	int j = 0;
	int temp = 0;
	//对顺序表进行简单排序
	for (int i = 0; i < L.length;++i)
	{
		compareNum[0]++;//记录的是i与length的比较
		j = SelectMinKey(L, i);
		compareNum[0]++;
		if (i != j)
		{
			temp = L.elem[i];
			L.elem[i] = L.elem[j];
			L.elem[j] = temp;
			changeNum[0] += 3;//交换+3
		}
	}
}
/********************堆排序算法*********************/
void HeadAdjust(SqList &H, int s, int m)
{
	int rc = H.elem[s];
	for (int j = 2 * s; j <= m; j *= 2)
	{
		compareNum[1]++;//for循环的判断
		if (j < m && (compareNum[1]++) && (H.elem[j] < H.elem[j + 1])) 
			++j;
		if (rc < H.elem[j]) 
		{ compareNum[1]++; break; }
		H.elem[s] = H.elem[j]; s = j;
		changeNum[1]++;
	}
	H.elem[s] = rc;
	changeNum[1]++;
}
void HeadSort(SqList &H)
{
	int temp;//中间变量用于保存数值，
	for (int i = H.length / 2; i>0; --i) {
		compareNum[1]++;
		HeadAdjust(H, i, H.length);//后续的调整
	}
	for (int i = H.length; i>1; --i) {
		compareNum[1]++;
		temp = H.elem[1]; H.elem[1] = H.elem[i]; H.elem[i] = temp;//最后的一次记录相互交换
		changeNum[1] += 3;
		HeadAdjust(H, 1, i - 1);//第一次的调整
	}
}
int main()
{
	int na = 10;
	int nb = 10000;
	int m = 10;
	SqList La, Lb, La1,Lb1;
	InitList_Sq(La);
	InitList_Sq(Lb);
	InitList_Sq(La1);
	InitList_Sq(Lb1);

	for (int i = 1; i <= na; i++)
	{
		int temp;
		cout << "请输入第" << i <<"个值=";
		cin >> temp;
		InsertList_Sq(La, i, temp);
		InsertList_Sq(La1, i, temp);
	}

	srand((int)time(0));
	//随机产生一万个20000以内的数
	for (int i = 1; i < nb; i++)
	{
		int temp = random(20000);
		InsertList_Sq(Lb, i, temp);
		InsertList_Sq(Lb1, i, temp);
	}

	//简单选择排序
	//PrintSqList(La, m);
	SelectSort(La);
	cout << "简单选择排序 对第一组比较了" << compareNum[0] << "次" << endl;
	cout << "简单选择排序 对第一组交换了" << changeNum[0] << "次" << endl;
	PrintSqList(La, m);
	cout << endl;

	//PrintSqList(Lb, m);
	SelectSort(Lb);
	cout << "简单选择排序 对第二组比较了" << compareNum[0] << "次" << endl;
	cout << "简单选择排序 对第二组交换了" << changeNum[0] << "次" << endl;
	PrintSqList(Lb, m);
	cout << endl;

	//堆排序
	//PrintSqList(La1, m);
	HeadSort(La1);
	cout << "堆排序 对第一组比较了" << compareNum[1] << "次" << endl;
	cout << "堆排序 对第一组交换了" << changeNum[1] << "次" << endl;
	PrintSqList(La, m);
	cout << endl;

	//PrintSqList(Lb1, m);
	HeadSort(Lb1);
	cout << "堆排序 对第二组比较了" << compareNum[1] << "次" << endl;
	cout << "堆排序 对第二组交换了" << changeNum[1] << "次" << endl;
	PrintSqList(Lb, m);
	cout << endl;

	return 0;
}