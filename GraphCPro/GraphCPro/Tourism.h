#pragma once
#include<iostream>
#include<string.h>
#include"Graph.h"

using namespace std;

class CTourism
{
private:
	CGraph MyGraph;  //CGraph对象，存储景区景点图
public:
	void CreateGraph();  //从文件中读取景区星系构建图
	void GetSpotInfo();  //得到景区信息
	
	void TravelPath();   //得到便遍历结果
	
	void SearchShortPath(); //搜索最短路径
	
	void DesignPath();   //查询铺设路线

};


