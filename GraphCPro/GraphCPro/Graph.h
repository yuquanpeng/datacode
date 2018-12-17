#pragma once
#include<iostream>
#include<string>

struct Edge
{
	int vex1; //边的第一个节点
	int vex2; //边的第二个节点
	int weight; //权值
};
struct Vex
{
	int num;   //景区编号
	char name[20];//景区名字
	char desc[1024];//景区描述
};

/*
typedef struct Path
{
	int path[20];//保存路径
	Path *next;//保存下一条路径
}*PathList;
*/

class CGraph
{
public:
	int AdjMatrix[20][20];   //邻接矩阵
	Vex AllVexs[20];         //顶点信息数组
	int VexNum;              //当前图的顶点个数
public:
	void init();      //初始化图
	bool InsertVex(Vex);  //插入顶点
	bool InsertEdge(Edge); //插入边
	Vex GetVex(int);     //得到顶点信息  
	int GetEdge(Vex);    //查询边的信息
	
	void CGraph::DFS(int num, bool if_visit[], int &deepth, int path[20], int &count);         //深度优先搜索遍历数
	void DFSTraverse(int); //得到遍历结果
	
	int BuildShortPath(int startVex, int endVex, int path[20]);  //搜索最短路径
	
	int BuildMinTree();   //构建最小生成树

};


