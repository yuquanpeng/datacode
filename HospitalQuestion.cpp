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
/*用邻接矩阵创建图G*/
 int CreateUDN(MGraph &G)
{
	cout<<"请输入村庄数：";
	cin>>G.n;
	cout<<"请输入村庄之间道路数：";
	cin>>G.m;
	int i,j,k;
	for(i=0;i<G.n;i++)
	{
		for(j=0;j<G.n;j++)//初始化邻接矩阵
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
	cout<<"村庄依次用数字0到"<<G.n-1<<"代替。\n";
	cout<<"村庄a "<<"村庄b "<<"距离\n";
	for(k=0;k<G.m;k++)
	{
		cin>>i;
		cin>>j;
		cin>>G.w[i][j];
		G.w[j][i]=G.w[i][j];
	}
	return 1;
}
 /*求图G中顶点s到其他顶点的最短路径中的最大值并返回*/
int PPaths(MGraph G,int s)
{
	int i,j,k,v;
	int d[MAX]={0};//存放顶点s到其他顶点的最短路径
	int p[MAX]={0};//判断村庄是否属于集合V的辅助数组
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
		for(i=0;i<G.n;i++)//从未求得最短路径的顶点（不在集合V）中选择路径长度最小的终点v：即求得s到v的最短路径
		{
			if(p[i]==0&&d[i]<min)
			{
				min=d[i];
				v=i;
			}
		}
		p[v]=1;//将顶点v加入集合V
		for(j=0;j<G.n;j++)//修改最短路径：计算v的邻接点的最短路径，若(s,…,v)+(v,j)<(s,…,j)，则以(s,…,v,j)代替
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
	cout<<"图的邻接矩阵为：\n";
	for(int i=0;i<G.n;i++)
	{
		for(int j=0;j<G.n;j++)
		{
			if(G.w[i][j]==INFINITY)
			{
				cout<<"∞\t";
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
	for(int i=0;i<G.n;i++)//求图G中各顶点到其他顶点的最短路径中的最大值的最小值
	{
		if(min>=PPaths(G,i))
		{
			min=PPaths(G,i);
			locate=i;
		}
	}
	cout<<"医院应建在村庄";
	cout<<locate;
	cout<<"\n";
	return 0;
}

