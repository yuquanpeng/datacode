#include"HuffmanTree.h"   
#include<string.h>   
#include<stdlib.h>   
  

int main()
{
	cout << "��������ı�/����ϵͳ!\n";
	cout << "1 ��ʼ��\n";
	cout << "2 ����\n";
	cout << "3 ����\n";
	cout << "4 ��������ļ�\n";
	cout << "6 �˳�\n";
	HuffmanTree huftree;         //���������������   
	int weight;
	int Choose;
	while (1)
	{
		cout << "�������ţ�";
		cin >> Choose;
		switch (Choose)
		{
		case 1:
			cout << "��������볤�ȣ�";
			cin >> weight;
			huftree.Initialization(weight);      //��ʼ����������   
			break;
		case 2:
			huftree.Encoder();
			break;
		case 3:
			huftree.Decoder();
			break;
		case 4:
			huftree.Print();
			break;

		case 6:
			return 0;
		}
	}
}