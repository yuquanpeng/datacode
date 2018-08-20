#include<iostream>
#include<stdio.h>
#include<string>
#include<fstream>
using namespace std;
int *w;
typedef struct
{
	unsigned int weight;
	unsigned int parent,lchild,rchild;
}HTNode,*HuffmanTree;
typedef char **HuffmanCode;

void HuffmanCoding(HuffmanTree &HT,HuffmanCode &HC,int *w,int n);
void Select(HuffmanTree &HT,int i,int &s1,int &s2);
int min(HuffmanTree &HT,int i);
int second(HuffmanTree &HT,int s1,int i);

HuffmanTree HT;
HuffmanCode HC;
int main()
{
	int n=52;
	w= new int[52];
	for(int i=0;i<52;i++) w[i]=0;
	char c;
	string s;
	ifstream fin;
	ofstream fout;
	fin.open("test.txt");
	fout.open("test1.txt");
	while(fin.get(c))
	{
		if('A'<=c&&c<='Z')
		{
			w[c-'A']++;
		}
		else if('a'<=c&&c<='z')
		{
			w[c-'a'+26]++;
		}
		else continue;
	}
	HuffmanCoding(HT,HC,w,n);
	for(int l=0;l<n;l++)
	{
		char *p=HC[l];
		fout<<p<<endl;
		if(l<26)
		cout<<(char)('A'+l)<<" 的编码为 :"<<p<<endl;
		else cout<<(char)('a'+l-26)<<" 的编码为 :"<<p<<endl;
	}
	cout<<" 请输入需要解码的序列 :"<<endl;
	cin>>s;
	int  length  = s.length(); 
	for(int temp=0;temp<length;)
	{
		int i = 2*n-2;
		while(HT[i].lchild!=-1&&temp<length)
		{
			if(s[temp]=='0'&&HT[i].lchild!=-1) i=HT[i].lchild;
			else if(s[temp]=='1'&&HT[i].lchild!=-1) i=HT[i].rchild;
			else
			{
				cout<<"error!"<<endl;
				return -1;
			}
			temp++;
			if(temp>=length&&HT[i].lchild!=-1)
			{
				cout<<" 序列有不属于编码内字符组或字符不足！ ！！"<<endl;
				return -1;
			}
			if(i>=0&&i<26)
			{
				cout<<(char)('A'+i);
			}
			else if(i<52) cout<<(char)('a'+i-26);
			else continue;
		}
	}
	fin.close();
	fout.close();
	return 0;
}
void HuffmanCoding(HuffmanTree &HT,HuffmanCode &HC,int *w,int n)
{
	int s1,s2;
	int m;
	int i;
	HuffmanTree p;
	if(n<=1) return;
	m=2*n-1;
	HT=(HuffmanTree)malloc(m*sizeof(HTNode));
	for(i=0,p=HT;i<n;++i,++p)
	{
		p->weight=w[i];
		p->lchild=-1;
		p->parent=-1;
		p->rchild=-1;
	}
	for(;i<m;++i,++p)
	{
		p->weight=0;
		p->lchild=-1;
		p->parent=-1;
		p->rchild=-1;
	}
	for(i=n;i<m;++i)
	{
		Select(HT,i-1,s1,s2);
		HT[s1].parent=i;
		HT[s2].parent=i;
		HT[i].lchild=s1;
		HT[i].rchild=s2;
		HT[i].weight=HT[s1].weight+HT[s2].weight;
	}
	HC=(HuffmanCode)malloc(n*sizeof(char *));
	char *cd;
	cd=(char*)malloc(n*sizeof(char));
	cd[n-1]='\0';
	for(i=0;i<n;++i)
	{
		int start=n-1;
		for(int c=i,f=HT[i].parent;f!=-1;c=f,f=HT[f].parent)
		{
			if(HT[f].lchild==c) cd[--start] = '0';
			else cd[--start]='1';
		}
		HC[i]=(char *)malloc((n-start)*sizeof(char));
		strcpy(HC[i],&cd[start]);
	}
	free(cd);
}
void Select(HuffmanTree &HT,int i,int &s1,int &s2)
{
	s1=min(HT,i);
	s2=second(HT,s1,i);
}
int min(HuffmanTree &HT,int i)
{
	int s1=0;
	while(HT[s1].parent!=-1)
	{
		s1++;
	}
	for(int j=0;j<=i;j++)
	{
		if(HT[j].weight<HT[s1].weight&&HT[j].parent==-1)
		s1=j;
	}
	return s1;
}
int second(HuffmanTree &HT,int s1,int i)
{
	int s2=0;
	while(HT[s2].parent!=-1||s2==s1)
	{
		s2++;
	}
	for(int j=0;j<=i;j++)
	{
		if(HT[j].weight<HT[s2].weight&&HT[j].parent==-1&&j!=s1)
		s2=j;
	}
	return s2;
}
