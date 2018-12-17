#include<iostream>
#include<string>
#include<fstream>
#include"Tourism.h"
#include"Graph.h"


using namespace std;

void CTourism::CreateGraph()
{
	MyGraph.init();//初始化

	ifstream fvex("d:/Vex.txt");
	ifstream fedge("d:/Edge.txt");

	Edge temp_edge;
	Vex temp_vex;


	//设置顶点
	int n;  //从Vex.txt文件中获取的顶点的个数
	fvex >> n;
	for (int i = 0; i < n; i++)    //每次读入一个顶点，并将其插入到图中
	{
		fvex >> temp_vex.num;
		fvex >> temp_vex.name;
		fvex >> temp_vex.desc;
		MyGraph.InsertVex(temp_vex);
	}

	//设置边  
	while (fedge.good())     // 从Edge.txt文件中获取边的信息，并将其插入到图中
	{
		fedge >> temp_edge.vex1;
		fedge >> temp_edge.vex2;
		fedge >> temp_edge.weight;
		MyGraph.InsertEdge(temp_edge);
	}

	//打印过程
	cout <<endl<< "=====创建景区景点图=====" << endl;
	cout << "顶点数目：" << n << endl;
	cout << "-----顶点-----" << endl;
	for (int i = 0; i < MyGraph.VexNum; i++)
		cout << MyGraph.AllVexs[i].num << "-" << MyGraph.AllVexs[i].name << endl;
	cout << "-----边-----" << endl;
	for (int i = 0; i < n; i++)
		for (int j = i; j < MyGraph.VexNum; j++)
			if (MyGraph.AdjMatrix[i][j] != 0)
				cout << "(V" << i << ",V" << j << ") " << MyGraph.AdjMatrix[i][j] << endl;
	system("pause");
}

void CTourism::GetSpotInfo()
{
	int num;
	Vex temp_vex;
	cout << endl<<"=====查询景点信息=====" << endl;

	//输出所有景区的编号和名称
	for (int i = 0; i < MyGraph.VexNum; i++)     
		cout << MyGraph.AllVexs[i].num << "-" << MyGraph.AllVexs[i].name << endl;

	cout << "请输入想要查询的景点编号：" ;
	cin >> num;
	temp_vex=MyGraph.GetVex(num);

	//输出景区的相关信息
	cout << endl << temp_vex.name << endl;
	cout << temp_vex.desc << endl;

	//输出景区周边可以去的景区以及距离
	cout << endl << "-----周边景区-----" << endl;
	MyGraph.GetEdge(temp_vex);

}


void CTourism::TravelPath()
{
	int n;
	cout <<endl<< "=====旅游景点导航=====" << endl;

	//输出所有景区的编号和名称
	for (int i = 0; i < MyGraph.VexNum; i++)
		cout << MyGraph.AllVexs[i].num << "-" << MyGraph.AllVexs[i].name << endl;

	cout << "请输入起始景点编号：";
	cin >> n;
	cout << "导航路线为：" << endl;

	MyGraph.DFSTraverse(n);



}

void CTourism::SearchShortPath()
{
	int startVex, endVex;
	int path[20];  //存储路径的数组
	int distance = 0;  //存储最短距离

	cout << "====== 搜索最短路径 =====" << endl;

	//输出所有景区的编号和名称
	for (int i = 0; i < MyGraph.VexNum; i++)
		cout << MyGraph.AllVexs[i].num << "-" << MyGraph.AllVexs[i].name << endl;

	cout << "请输入起点的编号：";
	cin >> startVex;
	cout << "请输入终点的编号：";
	cin >> endVex;

	memset(path, -1, sizeof(path));//初始化
	
	
	cout << "最短路线为：";

	distance = MyGraph.BuildShortPath( startVex, endVex, path);  //求最短路径

	
	int a;
//	cout << MyGraph.AllVexs[startVex].name;
//	for (int i = 1; path[i] >= 0; i++)
//	{
//		a = path[i];
//		cout << " -> " << MyGraph.AllVexs[a].name;
//	}
	cout << endl;

	cout << "最短距离为：" << distance << endl;
}

void CTourism::DesignPath()
{

}



