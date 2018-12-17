#include<iostream>
#include<string>
#include"Graph.h"
#include"Tourism.h"

using namespace std;

int main()
{
	int n=1;
	while (n != 0)
	{
		CTourism a_ctourism;
		cout << endl<<"=====景区信息管理系统=====" << endl;
		cout << "1.创建景区景点图" << endl;
		cout << "2.查询景点信息" << endl;
		cout << "3.旅游景点导航" << endl;
		cout << "4.搜索最短路径" << endl;
		cout << "5.铺设电路规划" << endl;
		cout << "0.退出" << endl;
		cout << "请输入操作编号：";
		cin >> n;
		switch (n)
		{
		case 1:a_ctourism.CreateGraph(); break;
		case 2:a_ctourism.GetSpotInfo(); break;
		case 3:a_ctourism.TravelPath(); break;
		case 4:a_ctourism.SearchShortPath(); break;
		case 5:a_ctourism.DesignPath(); break;
		case 0:exit(0); break;
		default:
			break;
		}
	}


	return 0;
}