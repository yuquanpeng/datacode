#pragma once
#include<iostream>
#include<string>

struct Edge
{
	int vex1; //�ߵĵ�һ���ڵ�
	int vex2; //�ߵĵڶ����ڵ�
	int weight; //Ȩֵ
};
struct Vex
{
	int num;   //�������
	char name[20];//��������
	char desc[1024];//��������
};

/*
typedef struct Path
{
	int path[20];//����·��
	Path *next;//������һ��·��
}*PathList;
*/

class CGraph
{
public:
	int AdjMatrix[20][20];   //�ڽӾ���
	Vex AllVexs[20];         //������Ϣ����
	int VexNum;              //��ǰͼ�Ķ������
public:
	void init();      //��ʼ��ͼ
	bool InsertVex(Vex);  //���붥��
	bool InsertEdge(Edge); //�����
	Vex GetVex(int);     //�õ�������Ϣ  
	int GetEdge(Vex);    //��ѯ�ߵ���Ϣ
	
	void CGraph::DFS(int num, bool if_visit[], int &deepth, int path[20], int &count);         //�����������������
	void DFSTraverse(int); //�õ��������
	
	int BuildShortPath(int startVex, int endVex, int path[20]);  //�������·��
	
	int BuildMinTree();   //������С������

};


