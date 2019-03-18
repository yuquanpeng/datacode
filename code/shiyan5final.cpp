#include<iostream>
#include<stdio.h>
#define N 6  //叶子数目
#define M (2*N-1)    //结点总数
#define MAXVAL 10000.0
#define MAXSIZE 100   //哈夫曼编码的最大位数
using namespace std;

typedef struct
{
 	char ch;
 	float weight;
 	int lchild,rchild,parent;
}Hufmtree;

typedef struct
{
 	char bits[N];   //位串
 	int start;      //编码在位串中的起始位置
	 char ch;        //字符
}Codetype;

void CHuffman(Hufmtree tree[])//建立哈夫曼树
{
 	int i,j,p1,p2;//p1,p2分别记住每次合并时权值最小和次小的两个根结点的下标
 	float small1,small2,f;
 	char c;
 	for(i=0;i<M;i++)    //初始化
 	{
  		tree[i].parent=0;
  		tree[i].lchild=-1;
  		tree[i].rchild=-1;
  		tree[i].weight=0.0;
 	}
 	cout<<"依次读入前"<<N<<"个结点的字符及权值(空格隔开)\n";
	 for(i=0;i<N;i++)  //读入前n个结点的字符及权值
	 {
		  cout<<"输入第"<<(i+1)<<"个字符 权值:";
		  cin>>c>>f;
		  getchar();
		  tree[i].ch = c;
		  tree[i].weight = f;
	 }
	 for(i = N;i < M;i++)      //进行n-1次合并，产生n-1个新结点
	 {
		  p1 = 0 ;p2 = 0;
		  small1 = MAXVAL;small2 = MAXVAL;   //maxval是float类型的最大值
		  for(j=0;j<i;j++)    //选出两个权值最小的根结点
		   if(tree[j].parent==0)
		    if(tree[j].weight<small1)
		    {
		     small2=small1;  //改变最小权、次小权及对应的位置
		     small1=tree[j].weight;
		     p2=p1;
		     p1=j;
		    }
		    else if(tree[j].weight<small2)
		     {
		      small2=tree[j].weight;  //改变次小权及位置
		      p2=j;
		     }
		  tree[p1].parent=i;
		  tree[p2].parent=i;
		  tree[i].lchild=p1;  //最小权根结点是新结点的左孩子
		  tree[i].rchild=p2;  //次小权根结点是新结点的右孩子
		  tree[i].weight=tree[p1].weight+tree[p2].weight;
	 }
}

void HuffmanCode(Codetype code[],Hufmtree tree[])//根据哈夫曼树求出哈夫曼编码
//codetype code[]为求出的哈夫曼编码
//hufmtree tree[]为已知的哈夫曼树
{
	 int i,c,p;
	 Codetype cd;   //缓冲变量
	 for(i=0;i<N;i++)
		 {
		  cd.start=N;
		  cd.ch=tree[i].ch;
		  c=i;       //从叶结点出发向上回溯
		  p=tree[i].parent;   //tree[p]是tree[i]的双亲
		  while(p!=0)
		  {
			   cd.start--;
			   if(tree[p].lchild==c)
			    cd.bits[cd.start]='0';   //tree[i]是左子树，生成代码'0'
			   else
			    cd.bits[cd.start]='1';   //tree[i]是右子树，生成代码'1'
			   c=p;
			   p=tree[p].parent;
		  }
		  code[i]=cd;    //第i+1个字符的编码存入code[i]
		 }
}

void decode(Hufmtree tree[])//依次输入，根据哈夫曼树译码
{
	 int i,j=0;
	 char b[MAXSIZE];
	 char endflag='2';    //结束标志取2
	 i=M-1;             //从根结点开始往下搜索
	 cout<<"输入发送的编码(以'2'为结束标志)：";
	 gets(b);
	 cout<<"译码后的字符为->";
	 while(b[j]!='2')
	 {
		  if(b[j]=='0')
		   i=tree[i].lchild;   //走向左孩子
		  else
		   i=tree[i].rchild;   //走向右孩子
		  if(tree[i].lchild==-1)     //tree[i]是叶结点
		  {
		   printf("%c",tree[i].ch);
		   i=M-1;      //回到根结点
		  }
		  j++;
	 }
	 cout<<endl;
	 if(tree[i].lchild!=-1&&b[j]!='2')   //读完，但尚未到叶子结点
	  	cout<<"Error"<<endl;
}
 
int  main()
{
 	cout<<"----哈夫曼编码----\n";
 	cout<<"当前可编码"<<N<<"个字符\n";
 	Hufmtree tree[M];
 	Codetype code[N];
 	int i,j;//循环变量
 	CHuffman(tree);//建立哈夫曼树
 	HuffmanCode(code,tree);//根据哈夫曼树求出哈夫曼编码
	cout<<"请输出每个字符的哈夫曼编码\n";
 	for(i=0;i<N;i++)
 	{
 	 printf("%c: ",code[i].ch);
  	for(j=code[i].start;j<N;j++)
  	 printf("%c ",code[i].bits[j]);
  	printf("\n");
 	}
 	cout<<"请输入代码进行译码\n";
 	decode(tree);//依次输入，根据哈夫曼树译码
 	return 0;
}

