#include<math.h>
#include<stdio.h> 
#define MAXSIZE 50
/* ���������㷨��������*/
typedef int KeyType;

#define MAXNUM 100
typedef struct{
	KeyType key;
}RedType;
RedType R[MAXNUM];//����ṹ������
typedef struct{
	RedType r[MAXSIZE+1];//r[0]���á����������ڱ���Ԫ
	int length;
}Sqlist;//˳��������
Sqlist L,L0,L1,L2,L3,L4,L5,L6,L7;	
typedef Sqlist HeadType;

#define RADIX 10//�ؼ��ֵĻ���
#define MAX 8//�ؼ������������ֵ
#define MAX_SPACE 10000
typedef int KeysType;
typedef struct
{
	KeysType keys[MAX];//�ؼ���
		int next;
}SLCell;//��̬����Ľڵ�����
typedef struct    
{  
    SLCell rl[MAX_SPACE];  //��̬����Ŀ����ÿռ�
    int keynum;  //��¼��ǰ�Ĺؼ��ָ���
    int recnum;  //��̬����ĵ�ǰ����
}SLList;//��̬���������

typedef int ArrType[RADIX];
int compare[8];//������¼�ȽϵĴ���
int change[8];//�����ȽϽ����Ĵ��� 
void shuRu(Sqlist &L){//����¼��˳���
	int i=1,n;
	printf("����������������ݸ��� : \n");
	scanf("%d",&n);
	printf("�����ε������������ֵ\n");
	L.length = n;
	for(;i<=L.length;i++){
		scanf("%d",&L.r[i]);
	}
}
void shuChu(Sqlist &L){//���˳����е�Ԫ��
	int i=1;
	printf("��˳��洢�е�����Ԫ��Ϊ��");
	for(;i<L.length;i++){
		printf("%d ",L.r[i]);
	}
	printf("%d\n\n",L.r[i]);
}
//==========================================��ѡ������======================
int SelectMinKey(Sqlist &L,int i){//��L.r[i��length]���ҵ���Сֵ�ļ�¼
	int k;
	compare[0] += L.length-i;
	for(k=i;i<=L.length;i++){
		compare[0]++;//��¼����i��length�ıȽ�
		compare[0]++;//�����ѡ������еıȽ�
		if(L.r[i].key<L.r[k].key){k=i;change[0]++;}
	}
	return k;
}

void SelectSort(Sqlist &L){//˳���ļ�ѡ���������
	int i,j,temp;
	for(i=1;i<L.length;++i){
		compare[0]++;//��¼����i��length�ıȽ�
		j = SelectMinKey(L,i);
		compare[0]++;
		if(i!=j){
		temp=L.r[i].key;L.r[i].key=L.r[j].key;L.r[j].key=temp;
		change[0]+=3;//����������3
		}
	}
}
//======================================ֱ�Ӳ�������=================================

void inserSort(Sqlist &L){//ֱ�Ӳ�������
	int j;
	for(int i = 2 ; i<=L.length; ++i) {
		compare[1]++;//i��length
		compare[1]++;//��¼��������ѡ�����ıȽ�
		if(L.r[i].key<L.r[i-1].key){	
			L.r[0] = L.r[i];//����Ϊ������
			L.r[i] = L.r[i-1];
			change[1]+=2;//�����ڵĸ�ֵ���Լ�λ�õĺ��ƣ����������Լӣ�
			for(j = i-2;j>0;j--){
				compare[1]++;//forѭ���еıȽ�
				compare[1]++;//��¼��������������Ҫ���еıȽ�
				if(L.r[0].key>=L.r[j].key) break;	
				L.r[j+1] = L.r[j];//��¼����	
				change[1]++;//λ�ú��ƣ�����������1
			}
			L.r[j+1] = L.r[0];//���뵽��ȷλ��
			change[1]++;
		}
	}
}
//========================================ð������=============================

void BubbleSort(Sqlist &L){//ð������
	int i,j,temp;
	for(i=1;i<=L.length;i++){
		compare[2]++;//��¼�����forѭ��
		for(j=1;j<=L.length-i;j++){
			compare[2]++;//�����forѭ���ıȽ�
			compare[2]++;//����ѡ��ıȽ�
			if(L.r[j].key>L.r[j+1].key){
				temp = L.r[j].key;
				L.r[j].key=L.r[j+1].key;
				L.r[j+1].key = temp;
				change[2]+=3;
			}
		}
	}
}

//========================================ϣ������===================================

void ShellInsert(Sqlist &L, int dk){//������dk��һ��ϣ����������
	//ǰ���¼������ʽdk��r[0]��Ϊ����һ���ݴ浥Ԫ���������ڱ�����j<=0ʱ�򣬱�ʾ����λ���ҵ�
	int i,j;
	for(i = dk+1; i<=L.length; ++i){
		compare[3]++;//�����forѭ�������Ƚ�
		compare[3]++;//�����ѡ��Ƚ�
		if(L.r[i].key<L.r[i-dk].key){
			L.r[0] = L.r[i];//�ݴ���L.r[0]
			change[3]++;
			for(j=i-dk; j>0; j-=dk)
			{compare[3]++;//forѭ��
				compare[3]++;//����ıȽ�
				if(L.r[0].key>L.r[j].key) break;
				L.r[j+dk] = L.r[j];//��¼���ƣ����Ҳ���λ��
				change[3]++;
			}
			L.r[j+dk] = L.r[0];//����
			change[3]++;
		}
	}
}

void ShellSort(Sqlist &L){//���������ж������L��ϣ������
	int k;
	int dlta[] = {5,3,2,1};
	int t = 4;
	for(k=0;k<t;++k){
		compare[3]++;//forѭ��
		ShellInsert(L,dlta[k]);
	}
}
//=========================��������===================================
int Partition(Sqlist &L,int low ,int high){
	//����˳���L���ֱ��r[low   hingh]�ļ�¼���������¼��λ�����������ڵ�λ�ã���ʱ����֮ǰ�ļ�¼����������
	KeyType pivotkey;
	L.r[0] = L.r[low];
	pivotkey = L.r[low].key;
	change[4]++;
	while(low<high){
		compare[4]++;//��¼���������whileѭ���������ж�
		compare[4]++;//��¼�����ѭ�����ӵ���ֹ
		while(low<high&&L.r[high].key>=pivotkey) {--high;compare[4]++;}
		L.r[low] = L.r[high];change[4]++;
		compare[4]++;//��¼�����ѭ�����ӵ���ֹ
		while(low<high&&L.r[low].key<=pivotkey) {++low;compare[4]++;}
		L.r[high] = L.r[low];change[4]++;
	}
	L.r[low] = L.r[0];
	change[4]++;
	return low;
}

void Qsort(Sqlist &L,int low, int high){//��˳���L�е�����������������
	int pivotloc;
	if(low<high){
		pivotloc = Partition(L,low,high);
		Qsort(L,low,pivotloc-1);
		Qsort(L,pivotloc+1,high);
	}
}
void QuickSort(Sqlist &L){//��˳�������������
	Qsort(L,1,L.length);
}
//======================������===========================================

void HeadAdjust(HeadType &H , int s, int m ){
	RedType rc;
	int j;
	rc = H.r[s];
	for(j = 2*s; j<=m; j*=2){
		compare[5]++;//forѭ���ĵ����ж�
		if(j<m&&(compare[5]++)&&(H.r[j].key < H.r[j+1].key)) ++j;
		if(rc.key > H.r[j].key ) {compare[5]++;break;}
		H.r[s] = H.r[j]; s = j;
		change[5]++;
	}
	H.r[s] = rc;
	change[5]++;
}//����
void HeadSort(HeadType &H){//��˳�����ж�����
	RedType temp;//�м�������ڱ�����ֵ��
	for(int i = H.length/2 ; i>0; --i){
		compare[5]++;
		HeadAdjust(H,i,H.length);//�����ĵ���
	}
	for(int i=H.length;i>1;--i){
		compare[5]++;
		temp=H.r[1]; H.r[1]=H.r[i]; H.r[i]=temp;//����һ�μ�¼�໥����
		change[5]+=3;
		HeadAdjust(H,1,i-1);//��һ�εĵ���
	}
}

//==============================�鲢����=================================
void Merge(RedType SR[],RedType TR[],int i,int m,int n){
	int j,k;
	for(j=m+1,k=i;i<=m&&j<=n;k++){
		compare[6]+=2;//forѭ���е����������ж�
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
		compare[6]++;//�������ж�
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
//===============================��������==========================
void CreatSLList(SLList &LK,Sqlist &L){
	int i,j;
    for(i=1;i<=L.length;i++){
		compare[7]++;
		R[i].key=L.r[i].key;
	}
	LK.recnum = L.length;
	LK.keynum = 3;//����Ϊ��λ���ıȽ�
	for(i=1;i<=LK.recnum;i++)  //�����������ְ�����λ���ĸ�ʽ���в�֡���λ��ʮλ����λ
    { 
		compare[7]++;
        j=LK.keynum-1;
		change[7]+=3;//���������ʽ��
		LK.rl[i].keys[j--]=R[i].key/100;//��ȡ�������λ�ģ���ʾ���е��ǰ�λ�ϵ�����		
		LK.rl[i].keys[j--]=(R[i].key%100)/10;//��ȡ����ʮλ�ϵ�����
		LK.rl[i].keys[j]=R[i].key%10;//��ȡ���Ǹ�λ�ϵ���ֵ 
    } 
	for(i=0;i<LK.recnum;++i){ //�����е������������������������ɶ�ά������
        LK.rl[i].next=i+1;
	}
	 LK.rl[LK.recnum].next=0;//����ѭ��
	 change[7]++;
}
void Distribute(SLCell (&r)[MAX_SPACE],int i,ArrType &f,ArrType &e) {//��i�˷���
	int j,p;	
	for(j=0;j<RADIX;j++) {compare[7]++;f[j] =0;}//���ӱ��ʼ��Ϊ�ձ�
	for(p=r[0].next; p; p=r[p].next){
		j = r[p].keys[i];
		change[7]++;

		if(!f[j]) {f[j]=p;change[7]++;}
		else {r[e[j]].next = p;change[7]++;}
		e[j] =p;change[7]++;
	}
}
void Collect(SLCell (&r)[MAX_SPACE],int i,ArrType f,ArrType e) //�������� 
{  
    int j,t;  
    for(j=0;!f[j];j++);//�ҵ�һ���ǿյ��ӱ�
	r[0].next=f[j];//r[0]��nextָ���һ���ǿ��ӱ�ĵ�һ�����
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
	L.rl[L.recnum].next = 0;//��L����Ϊһ����̬������
	change[7]++;
	for(int i=0;i<L.keynum;++i){//�������λ����һ�ζԸ����ؼ��ֽ��з�����ռ�
		compare[7]++;
		Distribute(L.rl,i,f,e);//��i�˷���
		Collect(L.rl,i,f,e);//��i�˵��ռ�
	}
}
void print(SLList &L){
	int i;
	printf("����Ľ��Ϊ��");
	for(i=L.rl[0].next;i;i=L.rl[i].next) //�ܵĴ�������ѭ�� 
    {   compare[7]++;
        for(int j=L.keynum-1;j>=0;j--) //�������һ������
		{compare[7]++;
            printf("%d",L.rl[i].keys[j]); 
		}
        printf(" ");  
    }  
    printf("\n");  
}  
//===============================�����Ʋ���=============================
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
//=====================���˵�=======================================
void Menu(){
	printf("\t===================��ӭʹ���������ܱȽ����=====================\t\n\n");
	printf("\t��ѡ����Ҫ���еĲ���:\t\n\n");
	printf("\t1:  ������ȫ����������ٽ�������\t\n");
	printf("\t2�� ��������һЩ������ʵ���������\t\n");
	printf("\t3�� ��������һ����������������ٽ�������\t\n");
	printf("\t0:  �˳�����\t\n");
	printf("\tΪ�˲��Ե��������У���ѡ����ȷ��������ʽ\t\n");
}
//========================����Ƚϴ����ͽ��������ı��=================
void Table(){
	printf("\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\t\n");
	printf("\t=�㷨����====================�Ƚϴ���================��������=====\t\n");
	printf("\t1��ѡ������             \t%d\t                    %d            \t\n",compare[0],change[0]);
	printf("\t2ֱ�Ӳ�������             \t%d\t                    %d            \t\n",compare[1],change[1]);
	printf("\t3  ð������               \t%d\t                    %d            \t\n",compare[2],change[2]);
	printf("\t4  ϣ������               \t%d\t                    %d            \t\n",compare[3],change[3]);
	printf("\t5����ѡ������             \t%d\t                    %d            \t\n",compare[4],change[4]);
	printf("\t6  �� �� ��               \t%d\t                    %d            \t\n",compare[5],change[5]);
	printf("\t7  �鲢����               \t%d\t                    %d            \t\n",compare[6],change[6]);
	printf("\t8  ��������               \t%d\t                    %d            \t\n",compare[7],change[7]);
	printf("\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\t\n");
}

//=====================================����ϵͳ��������������===============
void Random(Sqlist &L){
	SLList LK;
	for(int i =0;i<8;i++){
		compare[i]=0;
		change[i]=0;
	}
	a:printf("�����������������������ݸ��� : ");
	scanf("%d",&L.length);
	if(L.length>50){
		printf("�뽫����ĸ���������50֮�ڣ�����������!\n");
		goto a;
	}
	for(int i=1;i<=L.length;i++) {
		L.r[i].key =1+(int )(1000.0*rand()/(RAND_MAX+1.0));//�������1000���ڵ�����
	}
	printf("����֮ǰ��������ɵ�%d������:\n",L.length);
	for(int i=1;i<=L.length;i++) printf("%d  ",L.r[i].key);
	Copy(L);
	printf("\n����ִ�е��Ǹ���������������\n");
	SelectSort(L0);//��ѡ������
	printf("����֮���Ԫ�أ�\n");
	shuChu(L0);
	inserSort(L1);//ֱ�Ӳ�������
	BubbleSort(L2);//ð������
	ShellSort(L3);//ϣ������
	QuickSort(L4);//����ѡ������
	HeadSort(L5);//������
	MergeSort(L6);//�鲢����	
	CreatSLList(LK,L7);//���ھ�̬��������Ҫ���е������⴦��
	RadixSort(LK);//��������Ĳ���
//	print(LK);//�������Ե��ǻ����������ȷ��
	Table();
}
//=====================�����û����е�����һЩ��ֵ=================================
void Yonghu(Sqlist &L){
	SLList LK;
	for(int i =0;i<8;i++){
		compare[i]=0;
		change[i]=0;
	}
	shuRu(L);
	printf("�������%d��������\n",L.length);
	for(int i=1;i<=L.length;i++) 
		printf("%d  ",L.r[i].key);
	printf("\n");
	Copy(L);
	SelectSort(L0);//��ѡ������
	shuChu(L0);
	inserSort(L1);//ֱ�Ӳ�������
	BubbleSort(L2);//ð������
	ShellSort(L3);//ϣ������
	QuickSort(L4);//����ѡ������
	HeadSort(L5);//������
	MergeSort(L6);//�鲢����	
	CreatSLList(LK,L7);//���ھ�̬��������Ҫ���е������⴦��
	RadixSort(LK);//��������Ĳ���
//	print(LK);//�������Ե��ǻ����������ȷ��
	Table();
}
//=================����ϵͳ��������������=================================
void Nixu(Sqlist &L){
	SLList LK;
	Sqlist la;//�����ݴ��������
	int i;
	for(i =0;i<8;i++){
		compare[i]=0;
		change[i]=0;
	}
	a:printf("���������������������ܸ���n : ");
	scanf("%d",&L.length);
	if(L.length>50){
		printf("�뽫����ĸ���������50֮�ڣ�����������!\n");
		goto a;		
	}
	for(i=1;i<=L.length;i++) {
		L.r[i].key =1+(int )(1000.0*rand()/(RAND_MAX+1.0));//�������1000���ڵ�����
	}
	inserSort(L);//ֱ�Ӳ�������ʹ���������������
	la.length=L.length;
	i=la.length;
	for(int k=1;i>=1;i--){//�����ŵ����ݱ�����L�У���ʹ����˳��ݼ�
		la.r[k].key = L.r[i].key;
		k++;
	}
	printf("�����%d��������ǣ�\n",la.length);
	shuChu(la);
	Copy(la);
	SelectSort(L0);//��ѡ������
	shuChu(L0);
	inserSort(L1);//ֱ�Ӳ�������
	BubbleSort(L2);//ð������
	ShellSort(L3);//ϣ������
	QuickSort(L4);//����ѡ������
	HeadSort(L5);//������
	MergeSort(L6);//�鲢����	
	CreatSLList(LK,L7);//���ھ�̬��������Ҫ���е������⴦��
	RadixSort(LK);//��������Ĳ���
//	print(LK);//�������Ե��ǻ����������ȷ��
	Table();
}
//======================================���������ڲ��Ե�===================
int main(){
	int choose;

	for(;;){
			Menu();
			printf("\t��ѡ��");
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
