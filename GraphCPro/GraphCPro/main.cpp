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
		cout << endl<<"=====������Ϣ����ϵͳ=====" << endl;
		cout << "1.������������ͼ" << endl;
		cout << "2.��ѯ������Ϣ" << endl;
		cout << "3.���ξ��㵼��" << endl;
		cout << "4.�������·��" << endl;
		cout << "5.�����·�滮" << endl;
		cout << "0.�˳�" << endl;
		cout << "�����������ţ�";
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