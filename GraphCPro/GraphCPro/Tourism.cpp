#include<iostream>
#include<string>
#include<fstream>
#include"Tourism.h"
#include"Graph.h"


using namespace std;

void CTourism::CreateGraph()
{
	MyGraph.init();//��ʼ��

	ifstream fvex("d:/Vex.txt");
	ifstream fedge("d:/Edge.txt");

	Edge temp_edge;
	Vex temp_vex;


	//���ö���
	int n;  //��Vex.txt�ļ��л�ȡ�Ķ���ĸ���
	fvex >> n;
	for (int i = 0; i < n; i++)    //ÿ�ζ���һ�����㣬��������뵽ͼ��
	{
		fvex >> temp_vex.num;
		fvex >> temp_vex.name;
		fvex >> temp_vex.desc;
		MyGraph.InsertVex(temp_vex);
	}

	//���ñ�  
	while (fedge.good())     // ��Edge.txt�ļ��л�ȡ�ߵ���Ϣ����������뵽ͼ��
	{
		fedge >> temp_edge.vex1;
		fedge >> temp_edge.vex2;
		fedge >> temp_edge.weight;
		MyGraph.InsertEdge(temp_edge);
	}

	//��ӡ����
	cout <<endl<< "=====������������ͼ=====" << endl;
	cout << "������Ŀ��" << n << endl;
	cout << "-----����-----" << endl;
	for (int i = 0; i < MyGraph.VexNum; i++)
		cout << MyGraph.AllVexs[i].num << "-" << MyGraph.AllVexs[i].name << endl;
	cout << "-----��-----" << endl;
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
	cout << endl<<"=====��ѯ������Ϣ=====" << endl;

	//������о����ı�ź�����
	for (int i = 0; i < MyGraph.VexNum; i++)     
		cout << MyGraph.AllVexs[i].num << "-" << MyGraph.AllVexs[i].name << endl;

	cout << "��������Ҫ��ѯ�ľ����ţ�" ;
	cin >> num;
	temp_vex=MyGraph.GetVex(num);

	//��������������Ϣ
	cout << endl << temp_vex.name << endl;
	cout << temp_vex.desc << endl;

	//��������ܱ߿���ȥ�ľ����Լ�����
	cout << endl << "-----�ܱ߾���-----" << endl;
	MyGraph.GetEdge(temp_vex);

}


void CTourism::TravelPath()
{
	int n;
	cout <<endl<< "=====���ξ��㵼��=====" << endl;

	//������о����ı�ź�����
	for (int i = 0; i < MyGraph.VexNum; i++)
		cout << MyGraph.AllVexs[i].num << "-" << MyGraph.AllVexs[i].name << endl;

	cout << "��������ʼ�����ţ�";
	cin >> n;
	cout << "����·��Ϊ��" << endl;

	MyGraph.DFSTraverse(n);



}

void CTourism::SearchShortPath()
{
	int startVex, endVex;
	int path[20];  //�洢·��������
	int distance = 0;  //�洢��̾���

	cout << "====== �������·�� =====" << endl;

	//������о����ı�ź�����
	for (int i = 0; i < MyGraph.VexNum; i++)
		cout << MyGraph.AllVexs[i].num << "-" << MyGraph.AllVexs[i].name << endl;

	cout << "���������ı�ţ�";
	cin >> startVex;
	cout << "�������յ�ı�ţ�";
	cin >> endVex;

	memset(path, -1, sizeof(path));//��ʼ��
	
	
	cout << "���·��Ϊ��";

	distance = MyGraph.BuildShortPath( startVex, endVex, path);  //�����·��

	
	int a;
//	cout << MyGraph.AllVexs[startVex].name;
//	for (int i = 1; path[i] >= 0; i++)
//	{
//		a = path[i];
//		cout << " -> " << MyGraph.AllVexs[a].name;
//	}
	cout << endl;

	cout << "��̾���Ϊ��" << distance << endl;
}

void CTourism::DesignPath()
{

}



