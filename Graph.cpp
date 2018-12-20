#include<iostream>
#include"Graph.h"
#include<stack>
using namespace std;
Graph graph;
void Init()
{
	graph.vNum = 0;
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
			graph.adjMat[i][j] = 0;
}

int InsertVex(Vex sVex)
{
	if (graph.vNum == MAXNUM)
		return 0;//顶点已满
	graph.vexs[graph.vNum++] = sVex;
	//int num = 0;
	//sGraph.m_aVexs[num++] = sVex;
	return 1;
}

int InsertEdge(Edge sEdge)
{
	if (sEdge.vex1 < 0 || sEdge.vex1 >= graph.vNum || sEdge.vex2 < 0 || sEdge.vex2 >= graph.vNum)
		return 0;//下标越界
	graph.adjMat[sEdge.vex1][sEdge.vex2] = sEdge.weight;
	graph.adjMat[sEdge.vex2][sEdge.vex1] = sEdge.weight;
	return 1;
}

Vex GetVex(int v)
{
	return graph.vexs[v];
}

int FindEdge(int nVex, Edge aEdge[])
{
	int k = 0;
	for (int i = 0; i < graph.vNum; i++)
	{
		//得到边信息
		if (graph.adjMat[nVex][i] != 0)
		{
			aEdge[k].vex1 = nVex;
			aEdge[k].vex2 = i;
			aEdge[k].weight = graph.adjMat[nVex][i];
			k++;
		}
	}
	return k;
}

int GetVexNum()
{
	return graph.vNum;
	//return 0;
}

int SetVexNum(int num)
{
	graph.vNum = num;
	return 0;
}
void DFS(int nVex, bool bVisted[], int &nIndex, aPath &pList){
	bVisted[nVex] = true;//改为已访问
	pList.vex[nIndex++] = nVex;//访问顶点nVex
	if (nIndex == graph.vNum)
		printPath(&pList);//打印路径
	else{
		for (int i = 0; i < graph.vNum; i++){
			//点间存在路径且点未被访问过
			if (graph.adjMat[i][nVex] != 0 && !bVisted[i]){
				//递归调用DFS
				DFS(i, bVisted, nIndex, pList);
				bVisted[i] = false;
				nIndex--;
			}
		}
	}
}
void DFSTraverse(int nVex, aPath &pList)
{
	int nIndex = 0;
	bool aVisted[MAXNUM] = { false };
	DFS(nVex, aVisted, nIndex, pList);
}
int printPath(aPath * pList)
{
	//cout << "get one" << endl;
	for (int i = 0; i < graph.vNum; i++)
		cout << graph.vexs[pList->vex[i]].name << "->";
	cout << endl;
	return 0;
}

int FindShortPath(int start, int end){
	int path[MAXNUM] = {0};//路径信息
	int dist[MAXNUM];//开始顶点到i点的距离
	bool *visited = (bool*)malloc(sizeof(bool)*graph.vNum);

	for (int i = 0; i< graph.vNum; i++) { //初始化
		if (graph.adjMat[start][i]>0 && i != start){
			dist[i] = graph.adjMat[start][i];
			path[i] = start;     //path记录最短路径上从v0到i的前一个顶点 
		}
		else{
			dist[i] = 32767;    //若i不与v0直接相邻，则权值置为无穷大 
			path[i] = -1;
		}
		visited[i] = false;
		path[start] = start;
		dist[start] = 0;
	}
	visited[start] = true;
	for (int i = 1; i<graph.vNum; i++) { //循环扩展n-1次
		int mindist = 32767;
		int u;
		for (int j = 0; j<graph.vNum; j++){ //寻找未被扩展的权值最小的顶点 
			if (visited[j] == false && dist[j]<mindist){
				mindist = dist[j];//nVexStart&i无连接
				u = j;
			}
		}
		visited[u] = true;
		for (int j = 0; j<graph.vNum; j++)   { //更新dist数组的值和路径的值
			if (visited[j] == false && graph.adjMat[u][j]>0 && 
				mindist + graph.adjMat[u][j]<dist[j])
			{
				//在通过新加入的u点路径找到离v0点更短的路径 
				dist[j] = mindist + graph.adjMat[u][j];
				path[j] = u;
			}
		}
	}
	stack<int> paths;
	int lastVex, temp = 0, index = 0;
	for (lastVex = end; lastVex != path[lastVex]; lastVex = path[lastVex])
		index++;
	lastVex = end;//重置 进栈开始点
	int nVex_temp = end;
	temp = index+1;//终止条件
	//保存路径信息
	while (temp > 0){
		//路径信息保存在aPath中
		paths.push(nVex_temp);
		nVex_temp = path[lastVex];//取下一个进栈的值
		lastVex--;
		temp--;
	}
	//输出最短路径
	cout << "最短路径为：";
	while (!paths.empty()){
		//cout << path.top() << " ";
		cout << graph.vexs[paths.top()].name<<"->";
		paths.pop();
	}
	cout << endl;
	return dist[end];
}
int FindMintree(Edge aPath[],int &pathNum){
	int sumCost = 0;
	int lowCost[MAXNUM];//以i为终点的边的最小权值
	bool visted[MAXNUM];//已获得最短距离的点
	int prev[MAXNUM] = {0};//prev[i] 表示顶点i的前驱顶点
	//初始化数组 并默认起始顶点为0
	for (int i = 1; i < graph.vNum; i++){
		if (graph.adjMat[0][i] != 0)
			lowCost[i] = graph.adjMat[0][i];
		else
			lowCost[i] = 32767;
		visted[i] = false;
	}
	for (int j = 0; j < graph.vNum - 1; j++){
		int minCost = 32767;
		int nowVex = 0;
		for (int i = 0; i < graph.vNum; i++){//for循环得到离结点最近的顶点j
			//i还未被遍历 且在可选路径中最短
			if (!visted[i] && lowCost[i] < minCost){
				minCost = lowCost[i];
				nowVex = i;
			}
		}
		if (nowVex != 0){//当前判断顶点不能是起始点0
			visted[nowVex] = true;//当前顶点访问成功  访问标识置为true
			sumCost += lowCost[nowVex];//计算路径长度之和
			pathNum++;//用于确定最后打印信息时的个数
			for (int i = 0; i < graph.vNum; i++){
				//有边可找且比当前最短路径短
				if (!visted[i] && graph.adjMat[nowVex][i] < lowCost[i] && graph.adjMat[i][nowVex] != 0){
					//此时nowVex加入visted 需要更新lowcost
					lowCost[i] = graph.adjMat[nowVex][i];
					prev[i] = nowVex;//存储上一个点 
				}
			}
			//保存边的信息到aPath
			aPath[j].vex1 = prev[nowVex];
			aPath[j].vex2 = nowVex;
			aPath[j].weight = lowCost[nowVex];
		}

	}
	return sumCost;
}
