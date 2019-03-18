#include<iostream>
#include<climits>
#include<stdio.h>
using namespace std;

#define INFINITY 32767
const int MAX=20;
struct MGraph
{
	int n;
	int m;
	int w[MAX][MAX];
};
/*���ڽӾ��󴴽�ͼG*/
 int CreateUDN(MGraph &G)
{
	cout<<"�������ׯ����";
	cin>>G.n;
	cout<<"�������ׯ֮���·����";
	cin>>G.m;
	int i,j,k;
	for(i=0;i<G.n;i++)
	{
		for(j=0;j<G.n;j++)//��ʼ���ڽӾ���
		{
			if(j!=i)
			{
				G.w[i][j]=INFINITY;
			}
			else
			{
				G.w[i][j]=0;
			}

		}
	}
	cout<<"��ׯ����������0��"<<G.n-1<<"���档\n";
	cout<<"��ׯa "<<"��ׯb "<<"����\n";
	for(k=0;k<G.m;k++)
	{
		cin>>i;
		cin>>j;
		cin>>G.w[i][j];
		G.w[j][i]=G.w[i][j];
	}
	return 1;
}
 /*��ͼG�ж���s��������������·���е����ֵ������*/
int PPaths(MGraph G,int s)
{
	int i,j,k,v;
	int d[MAX]={0};//��Ŷ���s��������������·��
	int p[MAX]={0};//�жϴ�ׯ�Ƿ����ڼ���V�ĸ�������
	p[s]=1;
	int min;
	int max=0;
	for(i=0;i<G.n;i++)
	{
		d[i]=G.w[s][i];
	}
	for(k=0;k<G.n-1;k++)
	{
		min=INFINITY;
		for(i=0;i<G.n;i++)//��δ������·���Ķ��㣨���ڼ���V����ѡ��·��������С���յ�v�������s��v�����·��
		{
			if(p[i]==0&&d[i]<min)
			{
				min=d[i];
				v=i;
			}
		}
		p[v]=1;//������v���뼯��V
		for(j=0;j<G.n;j++)//�޸����·��������v���ڽӵ�����·������(s,��,v)+(v,j)<(s,��,j)������(s,��,v,j)����
		{
			if(p[j]==0&&d[j]>d[v]+G.w[v][j])
			{
				d[j]=d[v]+G.w[v][j];
			}
		}
	}
	for(i=0;i<G.n;i++)
	{
		 if(max<d[i])max=d[i];
	}
	return max;
}

int main()
{
	MGraph G;
	CreateUDN(G);
	cout<<"ͼ���ڽӾ���Ϊ��\n";
	for(int i=0;i<G.n;i++)
	{
		for(int j=0;j<G.n;j++)
		{
			if(G.w[i][j]==INFINITY)
			{
				cout<<"��\t";
			}
			else
			{
				cout<<G.w[i][j]<<"\t";
			}
		}
		cout<<endl;
	}
	int min=INFINITY;
	int locate;
	for(int i=0;i<G.n;i++)//��ͼG�и����㵽������������·���е����ֵ����Сֵ
	{
		if(min>=PPaths(G,i))
		{
			min=PPaths(G,i);
			locate=i;
		}
	}
	cout<<"ҽԺӦ���ڴ�ׯ";
	cout<<locate;
	cout<<"\n";
	return 0;
}

