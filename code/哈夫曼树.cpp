#include<btreint.h> 
int count=0;
//���ݵĸ�����
bitre data[50];//�洢����
void delete_min()//�����СԪ�ء�
{����for(int i=1;i<=count-2;i++)
������data[i]=data[i+2];������������}
int tree_insert(bitre t)//�����µĽڵ�; 
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
get_long(bitre t)//���huffman���Ĵ�Ȩ·������; 
{��if(t!=NULL)
{��if(t->rchild!=NULL&&t->lchild!=NULL)
{��visite_bnode(t,1);
��num=num+t->data;
��get_long(t->lchild);
��get_long(t->rchild);
}��}��}
void main()
{ 
cout<<endl<<endl<<endl<<endl;
cout<<" * Construct Huffman Tree *"<<endl;
cout<<" * Name: XuHua *"<<endl;
cout<<" * Number: 20042297 *"<<endl;
bitre a,b,t; //�������; 
cout<<"please put in the data and in increased way and -9999 over "<<endl;
for(int i=1;i<=50;i++)//��������;
{��int adj;
data[i]=(bitre)malloc(sizeof(struct bnode));//���ݴ洢; 
if(i==1){data[0]->data=0;}
cin>>adj;
if(adj==-9999){cout<<"put in over "<<endl;break;}//������־; 
data[i]->data=adj;count++;
}//����Ԫ�أ�
//���ݵĴ洢;
for(int y=1;y<=count;y++)//����洢������; 
for(int x=count;x>y;x--)
if(data[x]->data<data[x-1]->data)
{
int shu=data[x]->data;
data[x]->data=data[x-1]->data;
data[x-1]->data=shu;
} 
for(int j=1;j<=count;j++)
{data[j]->lchild=NULL;data[j]->rchild=NULL;}//huffman���������; 
while(count>1)
{��a=data[1];b=data[2];//�õ���С�������ڵ�; 
��t=(bitre)malloc(sizeof(struct bnode));
��t->lchild=a;
��t->rchild=b;
��t->data=a->data+b->data;
��delete_min();
��count=count-2;
��tree_insert(t);
��display_bitre("tree",t);//��ʾ��ʱ��huffman��; 
��Wait();��}
get_long(t);
cout<<"WL="<<num<<endl;//�����Ȩ·������; 
Wait();��
}

