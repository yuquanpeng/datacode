#pragma once
#include<iostream>
#include<string.h>
#include"Graph.h"

using namespace std;

class CTourism
{
private:
	CGraph MyGraph;  //CGraph���󣬴洢��������ͼ
public:
	void CreateGraph();  //���ļ��ж�ȡ������ϵ����ͼ
	void GetSpotInfo();  //�õ�������Ϣ
	
	void TravelPath();   //�õ���������
	
	void SearchShortPath(); //�������·��
	
	void DesignPath();   //��ѯ����·��

};


