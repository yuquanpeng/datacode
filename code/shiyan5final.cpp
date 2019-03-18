#include<iostream>
#include<stdio.h>
#define N 6  //Ҷ����Ŀ
#define M (2*N-1)    //�������
#define MAXVAL 10000.0
#define MAXSIZE 100   //��������������λ��
using namespace std;

typedef struct
{
 	char ch;
 	float weight;
 	int lchild,rchild,parent;
}Hufmtree;

typedef struct
{
 	char bits[N];   //λ��
 	int start;      //������λ���е���ʼλ��
	 char ch;        //�ַ�
}Codetype;

void CHuffman(Hufmtree tree[])//������������
{
 	int i,j,p1,p2;//p1,p2�ֱ��סÿ�κϲ�ʱȨֵ��С�ʹ�С�������������±�
 	float small1,small2,f;
 	char c;
 	for(i=0;i<M;i++)    //��ʼ��
 	{
  		tree[i].parent=0;
  		tree[i].lchild=-1;
  		tree[i].rchild=-1;
  		tree[i].weight=0.0;
 	}
 	cout<<"���ζ���ǰ"<<N<<"�������ַ���Ȩֵ(�ո����)\n";
	 for(i=0;i<N;i++)  //����ǰn�������ַ���Ȩֵ
	 {
		  cout<<"�����"<<(i+1)<<"���ַ� Ȩֵ:";
		  cin>>c>>f;
		  getchar();
		  tree[i].ch = c;
		  tree[i].weight = f;
	 }
	 for(i = N;i < M;i++)      //����n-1�κϲ�������n-1���½��
	 {
		  p1 = 0 ;p2 = 0;
		  small1 = MAXVAL;small2 = MAXVAL;   //maxval��float���͵����ֵ
		  for(j=0;j<i;j++)    //ѡ������Ȩֵ��С�ĸ����
		   if(tree[j].parent==0)
		    if(tree[j].weight<small1)
		    {
		     small2=small1;  //�ı���СȨ����СȨ����Ӧ��λ��
		     small1=tree[j].weight;
		     p2=p1;
		     p1=j;
		    }
		    else if(tree[j].weight<small2)
		     {
		      small2=tree[j].weight;  //�ı��СȨ��λ��
		      p2=j;
		     }
		  tree[p1].parent=i;
		  tree[p2].parent=i;
		  tree[i].lchild=p1;  //��СȨ��������½�������
		  tree[i].rchild=p2;  //��СȨ��������½����Һ���
		  tree[i].weight=tree[p1].weight+tree[p2].weight;
	 }
}

void HuffmanCode(Codetype code[],Hufmtree tree[])//���ݹ��������������������
//codetype code[]Ϊ����Ĺ���������
//hufmtree tree[]Ϊ��֪�Ĺ�������
{
	 int i,c,p;
	 Codetype cd;   //�������
	 for(i=0;i<N;i++)
		 {
		  cd.start=N;
		  cd.ch=tree[i].ch;
		  c=i;       //��Ҷ���������ϻ���
		  p=tree[i].parent;   //tree[p]��tree[i]��˫��
		  while(p!=0)
		  {
			   cd.start--;
			   if(tree[p].lchild==c)
			    cd.bits[cd.start]='0';   //tree[i]�������������ɴ���'0'
			   else
			    cd.bits[cd.start]='1';   //tree[i]�������������ɴ���'1'
			   c=p;
			   p=tree[p].parent;
		  }
		  code[i]=cd;    //��i+1���ַ��ı������code[i]
		 }
}

void decode(Hufmtree tree[])//�������룬���ݹ�����������
{
	 int i,j=0;
	 char b[MAXSIZE];
	 char endflag='2';    //������־ȡ2
	 i=M-1;             //�Ӹ���㿪ʼ��������
	 cout<<"���뷢�͵ı���(��'2'Ϊ������־)��";
	 gets(b);
	 cout<<"�������ַ�Ϊ->";
	 while(b[j]!='2')
	 {
		  if(b[j]=='0')
		   i=tree[i].lchild;   //��������
		  else
		   i=tree[i].rchild;   //�����Һ���
		  if(tree[i].lchild==-1)     //tree[i]��Ҷ���
		  {
		   printf("%c",tree[i].ch);
		   i=M-1;      //�ص������
		  }
		  j++;
	 }
	 cout<<endl;
	 if(tree[i].lchild!=-1&&b[j]!='2')   //���꣬����δ��Ҷ�ӽ��
	  	cout<<"Error"<<endl;
}
 
int  main()
{
 	cout<<"----����������----\n";
 	cout<<"��ǰ�ɱ���"<<N<<"���ַ�\n";
 	Hufmtree tree[M];
 	Codetype code[N];
 	int i,j;//ѭ������
 	CHuffman(tree);//������������
 	HuffmanCode(code,tree);//���ݹ��������������������
	cout<<"�����ÿ���ַ��Ĺ���������\n";
 	for(i=0;i<N;i++)
 	{
 	 printf("%c: ",code[i].ch);
  	for(j=code[i].start;j<N;j++)
  	 printf("%c ",code[i].bits[j]);
  	printf("\n");
 	}
 	cout<<"����������������\n";
 	decode(tree);//�������룬���ݹ�����������
 	return 0;
}

