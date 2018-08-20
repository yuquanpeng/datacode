#include <iostream> 
using namespace std;
#define MAXV 50 
#define INF 32767 
typedef int InfoType;
//�ڽӾ���洢���� 
typedef struct
{
	int no;
	InfoType info;
} VertexType;
typedef struct
{
	int edges[MAXV][MAXV];
	int n, e;
	VertexType vexs[MAXV];
} MGraph;
//�ҿ�˹�����㷨 
void Ppath(int path[], int i, int v)
{
	int k;
	k = path[i];
	if (k == v) return;
	Ppath(path, k, v);
	cout << k;
}
int biaoji1 = 0, biaoji2 = 0;
void Dispath(int dist[], int path[], int s[], int n, int v)
{
	int i;
	for (i = 0; i<n; i++)
	{
		if (i == v) continue;
		if (s[i] == 1)
		{
			cout << "��" << v << "��" << i << "�����·��Ϊ��" << dist[i] << " ";
			cout << v;
			Ppath(path, i, v);
			cout << i << endl;
			if (biaoji1 != 5)
			{
				biaoji2 += dist[i]; biaoji1++;
			}
			else
			{
				cout << "��Ϊ��" << " " << biaoji2;
				biaoji1 = 0; biaoji2 = 0;
			}
		}
		else
			cout << "��" << v << "��" << i << "�����ڵ�·��" << endl;
	}
}
void Dijkstra(MGraph g, int v)
{
	int dist[MAXV], path[MAXV];
	int s[MAXV];
	int mindis, i, j, u;
	for (i = 0; i<g.n; i++)
	{
		dist[i] = g.edges[v][i];
		s[i] = 0;
		if (g.edges[v][i]<INF) path[i] = v;
		else path[i] = -1;
	}
	s[v] = 1; path[v] = 0;
	for (i = 0; i<g.n; i++)
	{
		mindis = INF;
		for (j = 0; j<g.n; j++)
		{
			if (s[j] == 0 && dist[j]<mindis)
			{
				u = j;
				mindis = dist[j];
			}
		}
		s[u] = 1;
		for (j = 0; j<g.n; j++)
		{
			if (s[j] == 0)
			{
				if (g.edges[u][j]<INF&&dist[u] + g.edges[u][j]<dist[j])
				{
					dist[j] = dist[u] + g.edges[u][j];
					path[j] = u;
				}
			}
		}
	}
	Dispath(dist, path, s, g.n, v);
}
//���������㷨 
void Ppath1(int path[][MAXV], int i, int j)
{
	int k;
	k = path[i][j];
	if (k == -1) return;
	Ppath1(path, i, k);
	cout << k;
	Ppath1(path, k, j);
}
void Dispath1(int A[][MAXV], int path[][MAXV], int n)
{
	int i, j;
	for (i = 0; i<n; i++)
	{
		for (j = 0; j<n; j++)
		{
			if (i == j) continue;
			if (A[i][j] == INF)
			{
				if (i != j)
					cout << "��" << i << "��" << j << "������·��" << endl;
			}
			else
			{
				cout << "��" << i << "��" << j << "�����·������Ϊ:" << A[i][j] << " ";
				cout << i;
				Ppath1(path, i, j);
				cout << j << endl;
			}
		}
	}
}
void Floyd(MGraph g)
{
	int A[MAXV][MAXV], path[MAXV][MAXV];
	int i, j, k;
	for (i = 0; i<g.n; i++)
	{
		for (j = 0; j<g.n; j++)
		{
			A[i][j] = g.edges[i][j];
			path[i][j] = -1;
		}
	}
	for (k = 0; k<g.n; k++)
	{
		for (i = 0; i<g.n; i++)
		{
			for (j = 0; j<g.n; j++)
			{
				if (A[i][j]>A[i][k] + A[k][j])
				{
					A[i][j] = A[i][k] + A[k][j];
					path[i][j] = k;
				}
			}
		}
	}
	Dispath1(A, path, g.n);
}

//������ 
int main()
{
	int i, j, n;
	MGraph g;
	cout << "�������Ȩ����ͼ�Ķ��������";//6
	cin >> n;
	while (n != EOF/*cin>>n,n!=EOF*/)
	{
		cout << "�������Ȩ����ͼ���ڽӾ���" << endl;
		/*
		0 5 32767 7 32767 32767
		32767 0 4 32767 32767 32767
		8 32767 0 32767 32767 9
		32767 32767 5 0 32767 6
		32767 32767 32767 5 0 32767
		3 32767 32767 32767 1 0
		*/

		for (i = 0; i<n; i++)
		{
			for (j = 0; j<n; j++)
			{
				//scanf("%d",&g.edges[i][j]); 
				cin >> g.edges[i][j];
			}
		}
		g.n = n;
		cout << "���õҿ�˹�����㷨�õ������·��Ϊ��" << endl;
		for (i = 0; i<n; i++) Dijkstra(g, i);
		cout << endl;
		cout << "���ø��������㷨�õ������·��Ϊ��" << endl;
		Floyd(g);
		cout << endl;
		cout << "�������Ȩ����ͼ�Ķ��������";
	}
	return 0;
}