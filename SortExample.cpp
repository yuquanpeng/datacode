#include<math.h>
#include<stdio.h> 
#define MAXSIZE 50
/* 各种排序算法测试例子*/
typedef int KeyType;

#define MAXNUM 100
typedef struct{
	KeyType key;
}RedType;
RedType R[MAXNUM];//定义结构体数组
typedef struct{
	RedType r[MAXSIZE+1];//r[0]闲置、或者用作哨兵单元
	int length;
}Sqlist;//顺序表的类型
Sqlist L,L0,L1,L2,L3,L4,L5,L6,L7;	
typedef Sqlist HeadType;

#define RADIX 10//关键字的基数
#define MAX 8//关键字项数的最大值
#define MAX_SPACE 10000
typedef int KeysType;
typedef struct
{
	KeysType keys[MAX];//关键字
		int next;
}SLCell;//静态链表的节点类型
typedef struct    
{  
    SLCell rl[MAX_SPACE];  //静态链表的可利用空间
    int keynum;  //记录当前的关键字个数
    int recnum;  //静态链表的当前长度
}SLList;//静态链表的类型

typedef int ArrType[RADIX];
int compare[8];//用来记录比较的次数
int change[8];//用来比较交换的次数 
void shuRu(Sqlist &L){//数据录入顺序表
	int i=1,n;
	printf("请输入你输入的数据个数 : \n");
	scanf("%d",&n);
	printf("请依次的输入各个数据值\n");
	L.length = n;
	for(;i<=L.length;i++){
		scanf("%d",&L.r[i]);
	}
}
void shuChu(Sqlist &L){//输出顺序表中的元素
	int i=1;
	printf("该顺序存储中的数据元素为：");
	for(;i<L.length;i++){
		printf("%d ",L.r[i]);
	}
	printf("%d\n\n",L.r[i]);
}
//==========================================简单选择排序======================
int SelectMinKey(Sqlist &L,int i){//在L.r[i到length]中找到最小值的记录
	int k;
	compare[0] += L.length-i;
	for(k=i;i<=L.length;i++){
		compare[0]++;//记录的是i与length的比较
		compare[0]++;//下面的选择语句中的比较
		if(L.r[i].key<L.r[k].key){k=i;change[0]++;}
	}
	return k;
}

void SelectSort(Sqlist &L){//顺序表的简单选择排序操作
	int i,j,temp;
	for(i=1;i<L.length;++i){
		compare[0]++;//记录的是i与length的比较
		j = SelectMinKey(L,i);
		compare[0]++;
		if(i!=j){
		temp=L.r[i].key;L.r[i].key=L.r[j].key;L.r[j].key=temp;
		change[0]+=3;//交换次数加3
		}
	}
}
//======================================直接插入排序=================================

void inserSort(Sqlist &L){//直接插入排序
	int j;
	for(int i = 2 ; i<=L.length; ++i) {
		compare[1]++;//i与length
		compare[1]++;//记录的是下面选择语句的比较
		if(L.r[i].key<L.r[i-1].key){	
			L.r[0] = L.r[i];//复制为监视哨
			L.r[i] = L.r[i-1];
			change[1]+=2;//监视哨的赋值，以及位置的后移，交换次数自加；
			for(j = i-2;j>0;j--){
				compare[1]++;//for循环中的比较
				compare[1]++;//记录的是下面括号中要进行的比较
				if(L.r[0].key>=L.r[j].key) break;	
				L.r[j+1] = L.r[j];//记录后移	
				change[1]++;//位置后移，交换次数加1
			}
			L.r[j+1] = L.r[0];//插入到正确位置
			change[1]++;
		}
	}
}
//========================================冒泡排序=============================

void BubbleSort(Sqlist &L){//冒泡排序
	int i,j,temp;
	for(i=1;i<=L.length;i++){
		compare[2]++;//记录上面的for循环
		for(j=1;j<=L.length-i;j++){
			compare[2]++;//上面的for循环的比较
			compare[2]++;//下面选择的比较
			if(L.r[j].key>L.r[j+1].key){
				temp = L.r[j].key;
				L.r[j].key=L.r[j+1].key;
				L.r[j+1].key = temp;
				change[2]+=3;
			}
		}
	}
}

//========================================希尔排序===================================

void ShellInsert(Sqlist &L, int dk){//以增量dk做一次希尔插入排序
	//前后记录的增量式dk，r[0]作为的是一个暂存单元，而不是哨兵，当j<=0时候，表示插入位置找到
	int i,j;
	for(i = dk+1; i<=L.length; ++i){
		compare[3]++;//上面的for循环条件比较
		compare[3]++;//下面的选择比较
		if(L.r[i].key<L.r[i-dk].key){
			L.r[0] = L.r[i];//暂存在L.r[0]
			change[3]++;
			for(j=i-dk; j>0; j-=dk)
			{compare[3]++;//for循环
				compare[3]++;//下面的比较
				if(L.r[0].key>L.r[j].key) break;
				L.r[j+dk] = L.r[j];//记录后移，查找插入位置
				change[3]++;
			}
			L.r[j+dk] = L.r[0];//插入
			change[3]++;
		}
	}
}

void ShellSort(Sqlist &L){//按增量序列对书序表L做希尔排序
	int k;
	int dlta[] = {5,3,2,1};
	int t = 4;
	for(k=0;k<t;++k){
		compare[3]++;//for循环
		ShellInsert(L,dlta[k]);
	}
}
//=========================快速排序===================================
int Partition(Sqlist &L,int low ,int high){
	//交换顺序表L中字表的r[low   hingh]的记录，是枢轴记录到位，并返回所在的位置，此时在它之前的记录均不大于它
	KeyType pivotkey;
	L.r[0] = L.r[low];
	pivotkey = L.r[low].key;
	change[4]++;
	while(low<high){
		compare[4]++;//记录的是上面的while循环的条件判断
		compare[4]++;//记录下面的循环增加的终止
		while(low<high&&L.r[high].key>=pivotkey) {--high;compare[4]++;}
		L.r[low] = L.r[high];change[4]++;
		compare[4]++;//记录下面的循环增加的终止
		while(low<high&&L.r[low].key<=pivotkey) {++low;compare[4]++;}
		L.r[high] = L.r[low];change[4]++;
	}
	L.r[low] = L.r[0];
	change[4]++;
	return low;
}

void Qsort(Sqlist &L,int low, int high){//对顺序表L中的子序列做快速排序
	int pivotloc;
	if(low<high){
		pivotloc = Partition(L,low,high);
		Qsort(L,low,pivotloc-1);
		Qsort(L,pivotloc+1,high);
	}
}
void QuickSort(Sqlist &L){//对顺序表做快速排序
	Qsort(L,1,L.length);
}
//======================堆排序===========================================

void HeadAdjust(HeadType &H , int s, int m ){
	RedType rc;
	int j;
	rc = H.r[s];
	for(j = 2*s; j<=m; j*=2){
		compare[5]++;//for循环的调教判断
		if(j<m&&(compare[5]++)&&(H.r[j].key < H.r[j+1].key)) ++j;
		if(rc.key > H.r[j].key ) {compare[5]++;break;}
		H.r[s] = H.r[j]; s = j;
		change[5]++;
	}
	H.r[s] = rc;
	change[5]++;
}//插入
void HeadSort(HeadType &H){//对顺序表进行堆排序
	RedType temp;//中间变量用于保存数值，
	for(int i = H.length/2 ; i>0; --i){
		compare[5]++;
		HeadAdjust(H,i,H.length);//后续的调整
	}
	for(int i=H.length;i>1;--i){
		compare[5]++;
		temp=H.r[1]; H.r[1]=H.r[i]; H.r[i]=temp;//最后的一次记录相互交换
		change[5]+=3;
		HeadAdjust(H,1,i-1);//第一次的调整
	}
}

//==============================归并排序=================================
void Merge(RedType SR[],RedType TR[],int i,int m,int n){
	int j,k;
	for(j=m+1,k=i;i<=m&&j<=n;k++){
		compare[6]+=2;//for循环中的两个条件判断
		if(SR[i].key<SR[j].key) {change[6]++;TR[k] = SR[i++];}
		else {change[6]++;TR[k] =SR[j++];}
	}
	while(i<=m) {
		compare[6]++;
		TR[k++] = SR[i++];
		change[6]++;
	}
	while(j<=n) {
		compare[6]++;
		TR[k++] = SR[j++];
		change[6]++;
	}
}
void MSort(RedType SR[],RedType TR1[],int s,int t){
	int m;
	RedType TR2[MAXSIZE+1];
	if(s==t) {
		compare[6]++;//条件的判断
		TR1[s]=SR[s];
		change[6]++;
	}
	else{
		compare[6]++;
		m=(s+t)/2;
		MSort(SR,TR2,s,m);
		MSort(SR,TR2,m+1,t);
		Merge(TR2,TR1,s,m,t);
	}
}
void MergeSort(Sqlist &L){
	MSort(L.r,L.r,1,L.length);
}
//===============================基数排序==========================
void CreatSLList(SLList &LK,Sqlist &L){
	int i,j;
    for(i=1;i<=L.length;i++){
		compare[7]++;
		R[i].key=L.r[i].key;
	}
	LK.recnum = L.length;
	LK.keynum = 3;//设置为三位数的比较
	for(i=1;i<=LK.recnum;i++)  //将给定的数字按照三位数的格式进行拆分。百位、十位、个位
    { 
		compare[7]++;
        j=LK.keynum-1;
		change[7]+=3;//下面的三个式子
		LK.rl[i].keys[j--]=R[i].key/100;//获取的是最高位的，本示例中的是百位上的数字		
		LK.rl[i].keys[j--]=(R[i].key%100)/10;//获取的是十位上的数字
		LK.rl[i].keys[j]=R[i].key%10;//获取的是个位上的数值 
    } 
	for(i=0;i<LK.recnum;++i){ //将所有的链表用链表连接起来，构成二维的链表
        LK.rl[i].next=i+1;
	}
	 LK.rl[LK.recnum].next=0;//链表循环
	 change[7]++;
}
void Distribute(SLCell (&r)[MAX_SPACE],int i,ArrType &f,ArrType &e) {//第i趟分配
	int j,p;	
	for(j=0;j<RADIX;j++) {compare[7]++;f[j] =0;}//各子表初始化为空表
	for(p=r[0].next; p; p=r[p].next){
		j = r[p].keys[i];
		change[7]++;

		if(!f[j]) {f[j]=p;change[7]++;}
		else {r[e[j]].next = p;change[7]++;}
		e[j] =p;change[7]++;
	}
}
void Collect(SLCell (&r)[MAX_SPACE],int i,ArrType f,ArrType e) //基数排序 
{  
    int j,t;  
    for(j=0;!f[j];j++);//找第一个非空的子表
	r[0].next=f[j];//r[0]的next指向第一个非空子表的第一个结点
    t=e[j];change[7]+=2;
    while (j<RADIX-1)   
    { 
		compare[7]++;
        for(j++;j<RADIX-1&&!f[j];j++);
		{  compare[7]++;
            if (f[j]){  
               r[t].next=f[j];  
               t=e[j];
			   change[7]+=2;
			} 
		}
	}
    r[t].next=0; 
	change[7]++;
} 
void RadixSort(SLList &L){
	ArrType f,e; 
	for(int i=0;i<L.recnum;++i) {compare[7]++;L.rl[i].next = i+1;change[7]++;}
	L.rl[L.recnum].next = 0;//将L改造为一个静态的链表
	change[7]++;
	for(int i=0;i<L.keynum;++i){//按照最低位优先一次对各个关键字进行分配和收集
		compare[7]++;
		Distribute(L.rl,i,f,e);//第i趟分配
		Collect(L.rl,i,f,e);//第i趟的收集
	}
}
void print(SLList &L){
	int i;
	printf("排序的结果为：");
	for(i=L.rl[0].next;i;i=L.rl[i].next) //总的大的链表的循环 
    {   compare[7]++;
        for(int j=L.keynum-1;j>=0;j--) //控制输出一个数据
		{compare[7]++;
            printf("%d",L.rl[i].keys[j]); 
		}
        printf(" ");  
    }  
    printf("\n");  
}  
//===============================链表复制操作=============================
void Copy(Sqlist &L){
	L0.length=L.length;L1.length=L.length;L2.length=L.length;
	L3.length=L.length;L4.length=L.length;
	L5.length=L.length;L6.length=L.length;
	L7.length=L.length;	
	for(int i=1;i<=L1.length;i++){
		L1.r[i].key=L.r[i].key;L2.r[i].key=L.r[i].key;
		L3.r[i].key=L.r[i].key;L4.r[i].key=L.r[i].key;
		L5.r[i].key=L.r[i].key;L6.r[i].key=L.r[i].key;
		L7.r[i].key=L.r[i].key;L0.r[i].key=L.r[i].key;
	}
}
//=====================主菜单=======================================
void Menu(){
	printf("\t===================欢迎使用排序性能比较软件=====================\t\n\n");
	printf("\t请选择你要进行的操作:\t\n\n");
	printf("\t1:  产生完全随机的数据再进行排序\t\n");
	printf("\t2： 自行输入一些数据再实现排序操作\t\n");
	printf("\t3： 产生的是一组随机的逆序数据再进行排序\t\n");
	printf("\t0:  退出程序\t\n");
	printf("\t为了测试的正常进行，请选择正确的输入形式\t\n");
}
//========================输出比较次数和交换次数的表格=================
void Table(){
	printf("\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\t\n");
	printf("\t=算法名称====================比较次数================交换次数=====\t\n");
	printf("\t1简单选择排序             \t%d\t                    %d            \t\n",compare[0],change[0]);
	printf("\t2直接插入排序             \t%d\t                    %d            \t\n",compare[1],change[1]);
	printf("\t3  冒泡排序               \t%d\t                    %d            \t\n",compare[2],change[2]);
	printf("\t4  希尔排序               \t%d\t                    %d            \t\n",compare[3],change[3]);
	printf("\t5快速选择排序             \t%d\t                    %d            \t\n",compare[4],change[4]);
	printf("\t6  堆 排 序               \t%d\t                    %d            \t\n",compare[5],change[5]);
	printf("\t7  归并排序               \t%d\t                    %d            \t\n",compare[6],change[6]);
	printf("\t8  基数排序               \t%d\t                    %d            \t\n",compare[7],change[7]);
	printf("\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\t\n");
}

//=====================================用于系统产生随机数的情况===============
void Random(Sqlist &L){
	SLList LK;
	for(int i =0;i<8;i++){
		compare[i]=0;
		change[i]=0;
	}
	a:printf("请输入你产生的随机数的数据个数 : ");
	scanf("%d",&L.length);
	if(L.length>50){
		printf("请将输入的个数限制在50之内，请重新输入!\n");
		goto a;
	}
	for(int i=1;i<=L.length;i++) {
		L.r[i].key =1+(int )(1000.0*rand()/(RAND_MAX+1.0));//随机生成1000以内的整数
	}
	printf("排序之前的随机生成的%d个数是:\n",L.length);
	for(int i=1;i<=L.length;i++) printf("%d  ",L.r[i].key);
	Copy(L);
	printf("\n下面执行的是各个排序的运行情况\n");
	SelectSort(L0);//简单选择排序
	printf("排序之后的元素：\n");
	shuChu(L0);
	inserSort(L1);//直接插入排序
	BubbleSort(L2);//冒泡排序
	ShellSort(L3);//希尔排序
	QuickSort(L4);//快速选择排序
	HeadSort(L5);//堆排序
	MergeSort(L6);//归并排序	
	CreatSLList(LK,L7);//对于静态的链表需要进行的是特殊处理
	RadixSort(LK);//基数排序的操作
//	print(LK);//用来测试的是基数排序的正确性
	Table();
}
//=====================用于用户自行的输入一些数值=================================
void Yonghu(Sqlist &L){
	SLList LK;
	for(int i =0;i<8;i++){
		compare[i]=0;
		change[i]=0;
	}
	shuRu(L);
	printf("您输入的%d个数据是\n",L.length);
	for(int i=1;i<=L.length;i++) 
		printf("%d  ",L.r[i].key);
	printf("\n");
	Copy(L);
	SelectSort(L0);//简单选择排序
	shuChu(L0);
	inserSort(L1);//直接插入排序
	BubbleSort(L2);//冒泡排序
	ShellSort(L3);//希尔排序
	QuickSort(L4);//快速选择排序
	HeadSort(L5);//堆排序
	MergeSort(L6);//归并排序	
	CreatSLList(LK,L7);//对于静态的链表需要进行的是特殊处理
	RadixSort(LK);//基数排序的操作
//	print(LK);//用来测试的是基数排序的正确性
	Table();
}
//=================用于系统产生随机数的情况=================================
void Nixu(Sqlist &L){
	SLList LK;
	Sqlist la;//用于暂存随机数，
	int i;
	for(i =0;i<8;i++){
		compare[i]=0;
		change[i]=0;
	}
	a:printf("请输入你产生的随机数的总个数n : ");
	scanf("%d",&L.length);
	if(L.length>50){
		printf("请将输入的个数限制在50之内，请重新输入!\n");
		goto a;		
	}
	for(i=1;i<=L.length;i++) {
		L.r[i].key =1+(int )(1000.0*rand()/(RAND_MAX+1.0));//随机生成1000以内的整数
	}
	inserSort(L);//直接插入排序使得随机数递增有序
	la.length=L.length;
	i=la.length;
	for(int k=1;i>=1;i--){//将待排的数据保存在L中，并使得其顺序递减
		la.r[k].key = L.r[i].key;
		k++;
	}
	printf("逆序的%d个随机数是：\n",la.length);
	shuChu(la);
	Copy(la);
	SelectSort(L0);//简单选择排序
	shuChu(L0);
	inserSort(L1);//直接插入排序
	BubbleSort(L2);//冒泡排序
	ShellSort(L3);//希尔排序
	QuickSort(L4);//快速选择排序
	HeadSort(L5);//堆排序
	MergeSort(L6);//归并排序	
	CreatSLList(LK,L7);//对于静态的链表需要进行的是特殊处理
	RadixSort(LK);//基数排序的操作
//	print(LK);//用来测试的是基数排序的正确性
	Table();
}
//======================================主函数用于测试的===================
int main(){
	int choose;

	for(;;){
			Menu();
			printf("\t请选择：");
			scanf("%d",&choose);
			switch(choose){
				case 1:Random(L);break;
				case 2:Yonghu(L);break;
				case 3:Nixu(L);break;
				case 0:return 0 ;
			}//switch
		}//for
	return 0;
}
