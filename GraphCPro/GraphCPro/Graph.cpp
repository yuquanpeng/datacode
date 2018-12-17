#include<iostream>
#include<string>
#include"Graph.h"
#include"Tourism.h"
#include<stack>
using namespace std;

void CGraph::init()    //初始化图
{
	memset(AdjMatrix, 0, sizeof(AdjMatrix));
	memset(AllVexs, 0, sizeof(AllVexs));
	VexNum = 0;
}

bool CGraph::InsertVex(Vex a_vex)  //在图中插入顶点a_vex
{
	if (VexNum >= 20)
	{
		cout << "景区数目已满！" << endl;
		return false;
	}

	AllVexs[VexNum] = a_vex;   //插入顶点a_vex
	VexNum++;
	return true;
}

bool CGraph::InsertEdge(Edge a_edge)   //在图中插入边a_edge
{
	if (a_edge.vex1 < 0 || a_edge.vex1 >= 20 || a_edge.vex2 < 0 || a_edge.vex1 >= 20) //要插入的边所对应的顶点编号超过有效范围，则插入失败
		return false;
	AdjMatrix[a_edge.vex1][a_edge.vex2] = a_edge.weight;
	AdjMatrix[a_edge.vex2][a_edge.vex1] = a_edge.weight;
	return true;
}

Vex CGraph::GetVex(int n)   //获得编号为n的顶点的信息
{
	return AllVexs[n];
}

int CGraph::GetEdge(Vex a_vex)   //取得所有与顶点a_vex相连的边的个数
{
	int n = a_vex.num;
	int count = 0;
	for (int i = 0; i < VexNum; i++)
	{
		if (AdjMatrix[n][i] != 0)
		{
			cout << a_vex.name << "->" << AllVexs[i].name;
			cout << "   " << AdjMatrix[n][i] << "m" << endl;;
			count++;
		}	
	}
	return count;
}


void CGraph::DFS(int num,bool if_visit[],int &deepth,int path[20],int &count)      //深度优先搜索遍历树
{
	/*
	num：表示开始的顶点编号
	if_visit[]：表示某个顶点是否被访问
	deepth：表示遍历的深度
	path：存储路径
	count：路径的个数
	*/

	if_visit[num] = true;    //标记为已访问
	path[deepth++] = num;    //更新路径

	if (deepth == VexNum)    //搜索的深度等于景点的个数，已经遍历所有景点，打印路径
	{
		count++;
		cout << "路线" <<count<< ": " ;   //输出路径
		int t = path[0];
		cout << AllVexs[t].name;
		for (int j = 1; j < deepth; j++)
		{
			t = path[j];
			cout << " -> " << AllVexs[t].name;
		}
		cout << endl;
	}
	else     //搜索深度不够，没有遍历所有景点
	{
		for (int i = 0; i < VexNum; i++)   //寻找其邻接节点
		{
			if ((AdjMatrix[i][num] != 0) && (!if_visit[i]))   
			{
				DFS(i, if_visit, deepth, path, count);    //递归

				if_visit[i] = false;   //返回上一层
				deepth--;
			} 
		}
	}
}

void CGraph::DFSTraverse(int num)   //得到所有遍历结果,vexnum表示起始的顶点编号
{
	int deepth = 0;  //表示遍历的深度
	bool if_visit[20];//表示某个顶点是否被访问
	int path[20];  //保存路径
	int count = 1;  //保存路径个数

	//初始化
	memset(if_visit, false, sizeof(if_visit));
	memset(path, 0, sizeof(path));

	DFS(num, if_visit, deepth, path, count);

}

int CGraph::BuildShortPath(int startVex,int endVex,int path[20])
{
	int path1[20]={0};
	bool if_visit[20];  //记录从起始顶点到某顶点的最短路径是否已经求得
	int dis[20];  //记录从起点到某个顶点的最短路径
	int min = 32768;
	int count = 1;//记录路径时路径的长度计数
	memset(if_visit, false, sizeof(if_visit));  //初始化
	memset(dis, 0, sizeof(dis));

	
	int temp_adj[20][20];   //若两个景点之间没有直达的路，则修改其距离为无穷大
	for (int i = 0; i < VexNum; i++)
	{
		for (int j = 0; j < VexNum; j++)
		{
			if ((AdjMatrix[i][j] == 0) && (i != j))
				temp_adj[i][j] = 32768;
			else
			{
				temp_adj[i][j] = AdjMatrix[i][j];
				path[i] = startVex;
			}
				
		}
		path[startVex] = startVex;
	}

	for (int i = 0; i < VexNum; i++)
		dis[i] = temp_adj[startVex][i];

	if_visit[startVex] = true;   //起点被标记
	//path[0] = startVex;  //路径的起始点为startVex
	for (int i = 1; i < VexNum; i++)   //其余的VexNum-1个顶点
	{
		min = 32768;
		int temp = 0;  //临时保存顶点的编号

		for (int j = 0; j < VexNum; j++)   //寻找未被扩展的权值最小的顶点
		{
			if ((if_visit[j] == false) && (dis[j] < min))
			{
				min = dis[j];
				temp = j;
			}
		}
		if_visit[temp] = true;   //离起始点最近的顶点temp加入s集合

		for (int k = 0; k < VexNum; k++)   //更新dis数组的值和路径的值
		{
			if ((if_visit[k] == false) && ( (min + AdjMatrix[temp][k]) < dis[k] ) &&(AdjMatrix[temp][k]>0))
			{
				dis[k] = min + AdjMatrix[temp][k];
				//if(k==endVex)
				path[k] = temp;
			}
		}
	}
	//压栈出栈输出
	stack<int> path2;
	int lastVex, temp = 0, index = 0;
	for (lastVex = endVex; lastVex != path[lastVex]; lastVex = path[lastVex])
		index++;
	lastVex = endVex;//重置 进栈开始点
	int nVex_temp = endVex;
	temp = index + 1;//终止条件
					 //保存路径信息
	while (temp > 0)
	{
		//路径信息保存在aPath中
		path2.push(nVex_temp);
		nVex_temp = path[lastVex];//取下一个进栈的值
		lastVex--;
		temp--;
	}
	//输出最短路径
	cout << "最短路径为：";
	while (!path2.empty())
	{
		//cout << path.top() << " ";
		cout << AllVexs[path2.top()].name << "->";
		path2.pop();
	}



	cout << "路径深度为：" << count << endl;


	return dis[endVex];
}

int CGraph::BuildMinTree()
{
	return 0;
}






