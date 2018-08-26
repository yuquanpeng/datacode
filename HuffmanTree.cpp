#include<btreint.h> 
int count=0;
//数据的个数；
bitre data[50];//存储数组
void delete_min()//获得最小元素、
{　　for(int i=1;i<=count-2;i++)
　　　data[i]=data[i+2];　　　　　　}
int tree_insert(bitre t)//插入新的节点; 
{ if(t->data>=data[count]->data){data[++count]=t;return 0;}
else{int m;
for(int j=1;j<=count;j++)
if(data[j]->data>=t->data){m=j;break;}
for(int k=count;k>=m;k--)
data[k+1]=data[k];
data[m]=t;


count++;}
}
int num=0;
get_long(bitre t)//求解huffman树的带权路径长度; 
{　if(t!=NULL)
{　if(t->rchild!=NULL&&t->lchild!=NULL)
{　visite_bnode(t,1);
　num=num+t->data;
　get_long(t->lchild);
　get_long(t->rchild);
}　}　}
void main()
{ 
cout<<endl<<endl<<endl<<endl;
cout<<" * Construct Huffman Tree *"<<endl;
cout<<" * Name: XuHua *"<<endl;
cout<<" * Number: 20042297 *"<<endl;
bitre a,b,t; //定义变量; 
cout<<"please put in the data and in increased way and -9999 over "<<endl;
for(int i=1;i<=50;i++)//输入数据;
{　int adj;
data[i]=(bitre)malloc(sizeof(struct bnode));//数据存储; 
if(i==1){data[0]->data=0;}
cin>>adj;
if(adj==-9999){cout<<"put in over "<<endl;break;}//结束标志; 
data[i]->data=adj;count++;
}//数据元素，
//数据的存储;
for(int y=1;y<=count;y++)//整理存储的数据; 
for(int x=count;x>y;x--)
if(data[x]->data<data[x-1]->data)
{
int shu=data[x]->data;
data[x]->data=data[x-1]->data;
data[x-1]->data=shu;
} 
for(int j=1;j<=count;j++)
{data[j]->lchild=NULL;data[j]->rchild=NULL;}//huffman树构造过程; 
while(count>1)
{　a=data[1];b=data[2];//得到最小的两个节点; 
　t=(bitre)malloc(sizeof(struct bnode));
　t->lchild=a;
　t->rchild=b;
　t->data=a->data+b->data;
　delete_min();
　count=count-2;
　tree_insert(t);
　display_bitre("tree",t);//显示此时的huffman树; 
　Wait();　}
get_long(t);
cout<<"WL="<<num<<endl;//输出带权路径长度; 
Wait();　
}

