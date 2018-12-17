#include<iostream>
#include<string>
#include"Graph.h"
#include"Tourism.h"
#include<stack>
using namespace std;

void CGraph::init()    //��ʼ��ͼ
{
	memset(AdjMatrix, 0, sizeof(AdjMatrix));
	memset(AllVexs, 0, sizeof(AllVexs));
	VexNum = 0;
}

bool CGraph::InsertVex(Vex a_vex)  //��ͼ�в��붥��a_vex
{
	if (VexNum >= 20)
	{
		cout << "������Ŀ������" << endl;
		return false;
	}

	AllVexs[VexNum] = a_vex;   //���붥��a_vex
	VexNum++;
	return true;
}

bool CGraph::InsertEdge(Edge a_edge)   //��ͼ�в����a_edge
{
	if (a_edge.vex1 < 0 || a_edge.vex1 >= 20 || a_edge.vex2 < 0 || a_edge.vex1 >= 20) //Ҫ����ı�����Ӧ�Ķ����ų�����Ч��Χ�������ʧ��
		return false;
	AdjMatrix[a_edge.vex1][a_edge.vex2] = a_edge.weight;
	AdjMatrix[a_edge.vex2][a_edge.vex1] = a_edge.weight;
	return true;
}

Vex CGraph::GetVex(int n)   //��ñ��Ϊn�Ķ������Ϣ
{
	return AllVexs[n];
}

int CGraph::GetEdge(Vex a_vex)   //ȡ�������붥��a_vex�����ıߵĸ���
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


void CGraph::DFS(int num,bool if_visit[],int &deepth,int path[20],int &count)      //�����������������
{
	/*
	num����ʾ��ʼ�Ķ�����
	if_visit[]����ʾĳ�������Ƿ񱻷���
	deepth����ʾ���������
	path���洢·��
	count��·���ĸ���
	*/

	if_visit[num] = true;    //���Ϊ�ѷ���
	path[deepth++] = num;    //����·��

	if (deepth == VexNum)    //��������ȵ��ھ���ĸ������Ѿ��������о��㣬��ӡ·��
	{
		count++;
		cout << "·��" <<count<< ": " ;   //���·��
		int t = path[0];
		cout << AllVexs[t].name;
		for (int j = 1; j < deepth; j++)
		{
			t = path[j];
			cout << " -> " << AllVexs[t].name;
		}
		cout << endl;
	}
	else     //������Ȳ�����û�б������о���
	{
		for (int i = 0; i < VexNum; i++)   //Ѱ�����ڽӽڵ�
		{
			if ((AdjMatrix[i][num] != 0) && (!if_visit[i]))   
			{
				DFS(i, if_visit, deepth, path, count);    //�ݹ�

				if_visit[i] = false;   //������һ��
				deepth--;
			} 
		}
	}
}

void CGraph::DFSTraverse(int num)   //�õ����б������,vexnum��ʾ��ʼ�Ķ�����
{
	int deepth = 0;  //��ʾ���������
	bool if_visit[20];//��ʾĳ�������Ƿ񱻷���
	int path[20];  //����·��
	int count = 1;  //����·������

	//��ʼ��
	memset(if_visit, false, sizeof(if_visit));
	memset(path, 0, sizeof(path));

	DFS(num, if_visit, deepth, path, count);

}

int CGraph::BuildShortPath(int startVex,int endVex,int path[20])
{
	int path1[20]={0};
	bool if_visit[20];  //��¼����ʼ���㵽ĳ��������·���Ƿ��Ѿ����
	int dis[20];  //��¼����㵽ĳ����������·��
	int min = 32768;
	int count = 1;//��¼·��ʱ·���ĳ��ȼ���
	memset(if_visit, false, sizeof(if_visit));  //��ʼ��
	memset(dis, 0, sizeof(dis));

	
	int temp_adj[20][20];   //����������֮��û��ֱ���·�����޸������Ϊ�����
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

	if_visit[startVex] = true;   //��㱻���
	//path[0] = startVex;  //·������ʼ��ΪstartVex
	for (int i = 1; i < VexNum; i++)   //�����VexNum-1������
	{
		min = 32768;
		int temp = 0;  //��ʱ���涥��ı��

		for (int j = 0; j < VexNum; j++)   //Ѱ��δ����չ��Ȩֵ��С�Ķ���
		{
			if ((if_visit[j] == false) && (dis[j] < min))
			{
				min = dis[j];
				temp = j;
			}
		}
		if_visit[temp] = true;   //����ʼ������Ķ���temp����s����

		for (int k = 0; k < VexNum; k++)   //����dis�����ֵ��·����ֵ
		{
			if ((if_visit[k] == false) && ( (min + AdjMatrix[temp][k]) < dis[k] ) &&(AdjMatrix[temp][k]>0))
			{
				dis[k] = min + AdjMatrix[temp][k];
				//if(k==endVex)
				path[k] = temp;
			}
		}
	}
	//ѹջ��ջ���
	stack<int> path2;
	int lastVex, temp = 0, index = 0;
	for (lastVex = endVex; lastVex != path[lastVex]; lastVex = path[lastVex])
		index++;
	lastVex = endVex;//���� ��ջ��ʼ��
	int nVex_temp = endVex;
	temp = index + 1;//��ֹ����
					 //����·����Ϣ
	while (temp > 0)
	{
		//·����Ϣ������aPath��
		path2.push(nVex_temp);
		nVex_temp = path[lastVex];//ȡ��һ����ջ��ֵ
		lastVex--;
		temp--;
	}
	//������·��
	cout << "���·��Ϊ��";
	while (!path2.empty())
	{
		//cout << path.top() << " ";
		cout << AllVexs[path2.top()].name << "->";
		path2.pop();
	}



	cout << "·�����Ϊ��" << count << endl;


	return dis[endVex];
}

int CGraph::BuildMinTree()
{
	return 0;
}






