#include <iostream> 
using namespace std;
int INFTY = 32767;
template<class T>
class Graph
{
public:
	virtual void Insert(int u, int v, T& w) = 0;
	virtual void Remove(int u, int v) = 0;
	virtual bool Exist(int u, int v) = 0;
	virtual int Vertices()const { return n; }
protected:
	int n, e;

};
template <class T>
class MGraph :public Graph<T>//邻接矩阵存储图 
{
public:
	MGraph();
	~MGraph();
	void Build_Graph();
	void Insert(int u, int v, T& w);
	void Remove(int u, int v);
	bool Exist(int u, int v);
	void Floyd(T**&d, int**&path);
	int num;
protected:
	T**a;
	T noEdge;
};
template <class T>
void MGraph<T>::Build_Graph()//建图 
{
	cout << "请输入顶点的个数：";
	int C_num;
	cin >> C_num;
	num = n = C_num; e = 0; noEdge = INFTY;
	a = new T*[n];
	for (int k = 0; k<n; k++) {
		a[k] = new T[n];
		for (int j = 0; j<n; j++)a[k][j] = noEdge;
		a[k][k] = 0;
	}
	cout << "建立村庄编号为1--" << C_num << "的图" << endl;
	for (int i = 0; i != C_num; i++)
		for (int j = i + 1; j != C_num; j++)
		{
			int w;
			cout << "请输入村庄" << i + 1 << "与村庄" << j + 1 << "之间的权值：";
			cin >> w;
			Insert(i, j, w); //向图中添加权值为W的边 
			cout << "村庄"<<i << "到" << "村庄"<<j << "的距离：" << a[i][j] << endl;
		}

}

template <class T>
MGraph<T>::MGraph()
{
	Build_Graph();
}

template <class T>
MGraph<T>::~MGraph()
{
	for (int i = 0; i<n; i++)delete[]a[i];
	delete[]a;
}

template <class T>
bool MGraph<T>::Exist(int u, int v)
{
	if (u<0 || v<0 || u>n - 1 || v>n - 1 || u == v || a[u][v] == noEdge) return false;
	return true;
}
template <class T>
void MGraph<T>::Insert(int u, int v, T &w)
{
	a[u][v] = w; a[v][u] = w; e++;
}
template <class T>
void MGraph<T>::Remove(int u, int v)
{
	a[u][v] = noEdge; e--;
}

template <class T>
void MGraph<T>::Floyd(T**&d, int**&path)//所有顶点之间的最短路径 
{
	int i, j, k;
	d = new T*[n]; path = new int*[n];
	for (i = 0; i<n; i++) {
		d[i] = new T[n]; path[i] = new int[n];
		for (j = 0; j<n; j++) {
			d[i][j] = a[i][j];
			if (i != j&& a[i][j]<INFTY)path[i][j] = i;
			else path[i][j] = -1;
		}
	}
	for (k = 0; k<n; k++)
		for (i = 0; i<n; i++)
			for (j = 0; j<n; j++)
				if (d[i][k] + d[k][j]<a[i][j]) {
					d[i][j] = d[i][k] + d[k][j];
					path[i][j] = path[k][j];
				}
}
int main()
{
	MGraph<int> Hospital;
	int **d, **path;
	int i, j, n;
	n = Hospital.num;
	Hospital.Floyd(d, path);
	int *sum = new int[n];
	cout << endl;
	cout << "邻接矩阵：" << endl;
	for (i = 0; i != n; i++)//输出矩阵 
	{
		sum[i] = 0;
		for (j = 0; j != n; j++)
		{
			sum[i] += d[i][j];
			cout << d[i][j] << "\t";
		}
		cout << endl;
	}
	
	int min = 0;
	for (i = 0; i != n; i++)
	{
		cout << i + 1 << "村庄：" << sum[i] << endl;
		if (sum[min]>sum[i])//判断最短路径 
			min = i;
	}
	cout << "医院应在编号为" << min + 1 << "的村庄" << endl;
	for (i = 0; i<n; i++)
	{
		delete[]d[i];
		delete[]path[i];
	}
	delete[]d;
	delete[]path;
	return 0;
}