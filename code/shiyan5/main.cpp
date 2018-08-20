#include<stdlib.h>
#include<iostream>
#include<string>
#include<fstream>
#define PATH_1 "D:\\text_1.dat"
#define PATH_2 "D:\\text_2.dat"
//#define weightNum 12
using namespace std;
int LeafNum;

struct HuffmanNode
{
	int weight;
	int parent, lchild, rchild;
};
HuffmanNode *Node;
char *Info;

void Init()
{
	int i, j, pos1, pos2, max1, max2, weightNum;     // 
	cout << "�������ַ��ĸ�����";
	cin >> weightNum;
	Node = new HuffmanNode[2 * weightNum - 1];  //WeightNumȨֵ��Ӧ�Ĺ��������еĽ������Ϊ2*WeightNum-1��   
	Info = new char[2 * weightNum - 1];
	for (i = 0; i<weightNum; i++)
	{
		cout << "�������" << i + 1 << "���ַ�ֵ:";
		getchar();           //�����ַ�'\t'��'\n'   
		Info[i] = getchar();   //����һ���ַ�,��Ҫ�ǿ�������ո������������ʽ��   
		getchar();
		cout << "��������ַ���Ȩֵ(���ֵĴ���):";
		cin >> Node[i].weight;       //����Ȩֵ   
		Node[i].parent = -1;      //Ϊ�����   
		Node[i].lchild = -1;      //������   
		Node[i].rchild = -1;      //���Һ���   
	}

	for (i = weightNum; i<2 * weightNum - 1; i++) //��ʾ����WeightNum-1�κϲ�   
	{
		pos1 = -1;
		pos2 = -1;          //�ֱ�������ŵ�ǰ��Сֵ�ʹ�Сֵ�����ڵ�Ԫ���    
		max1 = 32767;      //32767Ϊ�����������ֵ    
		max2 = 32767;      //�ֱ�������ŵ�ǰ�ҵ�����Сֵ�ʹ�Сֵ     

		for (j = 0; j<i; j++)      //�ڸ��ڵ���ѡ��Ȩֵ��С������   
			if (Node[j].parent == -1)         //�Ƿ�Ϊ�����   
				if (Node[j].weight<max1)     //�Ƿ����СֵҪС   
				{
					max2 = max1;            //ԭ��Сֵ��Ϊ��Сֵ   
					max1 = Node[j].weight;      //�����Сֵ   
					pos2 = pos1;            //�޸Ĵ�Сֵ���ڵ�Ԫ���   
					pos1 = j;               //�޸���Сֵ���ڵ�Ԫ���   
				}
				else if (Node[j].weight<max2) //��ԭ��Сֵ�󵫱�ԭ��СֵҪС      
				{
					max2 = Node[j].weight;     //��Ŵ�Сֵ   
					pos2 = j;                  //�޸Ĵ�Сֵ���ڵĵ�Ԫ���   
				}
		//for   
		Node[pos1].parent = i;       //�޸ĸ���λ��   
		Node[pos2].parent = i;
		Node[i].lchild = pos1;       //�޸Ķ���λ��   
		Node[i].rchild = pos2;
		Node[i].parent = -1;             //��ʾ�½��Ӧ���Ǹ����   
		Node[i].weight = Node[pos1].weight + Node[pos2].weight;
	} //for   
	LeafNum = weightNum;

	ofstream fop;   //�Զ����Ʒ�ʽ��hfmTree.dat�ļ���������������ʱ����ԭ�ļ�   
	fop.open(PATH_1, ios::out | ios::binary | ios::trunc);
	if (fop.fail())                     //�ļ���ʧ��   
		cout << "�ļ���ʧ�ܣ�\n";
	fop.write((char*)&weightNum, sizeof(weightNum));  //д��WeightNum   
	for (i = 0; i<weightNum; i++)         //�Ѹ��ַ���Ϣд���ļ�   
	{
		fop.write((char*)&Info[i], sizeof(Info[i]));
		flush(cout);
	}
	for (i = 0; i<2 * weightNum - 1; i++)        //�Ѹ��ڵ�����д���ļ�   
	{
		fop.write((char*)&Node[i], sizeof(Node[i]));
		flush(cout);
	}
	fop.close();            //�ر��ļ�   
	cout << "���������ѹ������" << endl;
}

void PrintTree()
{
	if (Node == NULL)         //δ������������   
	{
		cout << "������\n";
		return;
	}
	ofstream fop(PATH_1);
	cout << "���λ��(Ȩֵ)  " << "����  " << "����  " << "����" << "�Һ���('^'��ʾҶ��)\n";
	fop << "���λ��(Ȩֵ)  " << "����  " << "����  " << "����" << "�Һ���('^'��ʾҶ��)\n";
	int i;
	for (i = (2 * LeafNum - 2); i>LeafNum - 1; i--)        //�����������   
	{
		cout << i << "(" << Node[i].weight << ")" << "\t--1--\t"
			<< Node[i].lchild << "(" << Node[Node[i].lchild].weight << ")" << "\t--0--\t"
			<< Node[i].rchild << "(" << Node[Node[i].rchild].weight << ")" << endl;
		fop << i << "(" << Node[i].weight << ")" << "\t--1--\t"
			<< Node[i].lchild << "(" << Node[Node[i].lchild].weight << ")" << "\t--0--\t"
			<< Node[i].rchild << "(" << Node[Node[i].rchild].weight << ")" << endl;
	}
	for (; i >= 0; i--)
	{
		cout << i << ":" << Node[i].weight << "(" << Info[i] << ")\t--- ^ \n";
		fop << i << ":" << Node[i].weight << "(" << Info[i] << ")\t--- ^ \n";
	}
}

void HuffmanCoding()
{
	if (Node == NULL)        //�������������ڴ棬���ļ�hfmTree�ж���   
	{
		ifstream fip;        //�Զ����Ʒ�ʽ��hfmTree.dat�ļ�   
		fip.open(PATH_1, ios::binary | ios::in);
		if (fip.fail())       //�ļ���ʧ��   
		{
			cout << "�ļ���ʧ�ܣ�\n";
			return;             //����������   
		}
		fip.read((char*)&LeafNum, sizeof(LeafNum));  //��ȡҶ����   
		Info = new char[LeafNum];
		Node = new HuffmanNode[2 * LeafNum - 1];
		for (int i = 0; i<LeafNum; i++)                  //��ȡ�ַ���Ϣ   
			fip.read((char*)&Info[i], sizeof(Info[i]));
		for (int i = 0; i<2 * LeafNum - 1; i++)              //��ȡ�����Ϣ   
			fip.read((char*)&Node[i], sizeof(Node[i]));
	}

	char *Tree;          //���ڴ洢���������   
	int i = 0, num;
	string tree;         //����������������ݣ�����string���������������ⳤ�ȣ�   
						 //��������������������룬��ת����Tree��   
	cin.ignore();
	cout << "��������Ҫ���������(���������ⳤ������ʱ�밴2�»س�):\n";
	getline(cin, tree, '\n');         //�������ⳤ�ַ�����   
									  //getline�Իس�('\n')��Ϊ����������һ�ΰ��س���ʾ�ַ����������ڶ��ΰ��س��ſ�ʼ�����   
	while (tree[i] != '\0')
		i++;
	num = i;                     //����tree����   
	i = 0;
	Tree = new char[num + 1];
	while (tree[i] != '\0')       //��tree�е��ַ�ת�浽Tree��   
	{
		Tree[i] = tree[i];
		i++;
	}
	Tree[i] = '\0';          //������־��   

	ofstream fop(PATH_2, ios::trunc);      //�洢�����Ĵ���,������ԭ�ļ�   
	i = 0;
	int k = 0;
	char *code;
	code = new char[LeafNum];        //Ϊ�����������������ΪLeafNum�Ĵ洢�ռ�   
									 //��Ϊ���ȳ���������ı���һ�����ᳬ��Ҫ�������ַ�����   
	while (Tree[k] != '\0')           //��ÿһ���ַ�����   
	{
		int j, start = 0;
		for (i = 0; i<LeafNum; i++)
			if (Info[i] == Tree[k])            //������������ڵ�Ԫ�ı��   
				break;
		j = i;
		while (Node[j].parent != -1)        //���j������   
		{
			j = Node[j].parent;               //�ǽ��j��˫�׽��   
			if (Node[j].lchild == i)           //���������������ɴ���0   
				code[start++] = '0';
			else                            //���������������ɴ���1   
				code[start++] = '1'; \
				i = j;
		}
		code[start] = '\0';                //�ô�������   


		for (i = 0; i<start / 2; i++)           //�Զ��������н�������   
		{
			j = code[i];
			code[i] = code[start - i - 1];
			code[start - i - 1] = j;
		}
		i = 0;
		while (code[i] != '\0')             //�洢����   
		{
			fop << code[i];
			i++;
		}
		k++;
	}
	fop.close();
	cout << "�ѱ��룡�Ҵ浽�ļ�CodeFile.dat�У�\n\n";
}


void HuffmanTran()
{
	int i = 0, k = 0;
	int j = LeafNum * 2 - 1 - 1;      //��ʾ�Ӹ���㿪ʼ��������   
	char* BitStr;

	ifstream fip1(PATH_2);          //�����ѽ��õĹ����������ļ�CodeFile�еĴ����������   
	if (fip1.fail())           //�ļ���ʧ�ܣ���δ����   
	{
		cout << "���ȱ��룡\n";
		return;
	}
	cout << "������,ԭ����Ϊ:";
	char ch;
	while (fip1.get(ch))
	{
		k++;                     //����CodeFile�д��볤��   
	}
	fip1.close();

	BitStr = new char[k + 1];
	ifstream fip2(PATH_2);
	k = 0;
	while (fip2.get(ch))
	{
		BitStr[k] = ch;          //��ȡ�ļ�����   
		k++;
	}
	fip2.close();
	BitStr[k] = '\0';         //������־��   
	if (Node == NULL)          //��δ����������   
	{
		cout << "���ȱ���!\n";
		return;
	}
	ofstream fop("TextFile.dat");         //���ַ���ʽ�ı����ļ�д���ļ�CodePrin��   
	while (BitStr[i] != '\0')
	{
		if (BitStr[i] == '0')
			j = Node[j].lchild;        //������   
		else
			j = Node[j].rchild;        //������   
		if (Node[j].rchild == -1)    //����Ҷ�ӽ��   
		{
			cout << Info[j];           //���Ҷ�ӽ���Ӧ���ַ�   
			j = LeafNum * 2 - 1 - 1;         //��ʾ���´Ӹ���㿪ʼ��������   
			fop << Info[j];            //�����ļ�   
		}//if��   
		i++;
	}//while   
	fop.close();

	cout << "\n����ɹ����Ѵ浽�ļ�TextFile.dat�У�\n\n";
}
void Print()
{
	char ch;
	int i = 1;
	ifstream fip(PATH_1);           //��ȡ�ļ�   
	ofstream fop(PATH_2);           //�洢�ļ�   
	if (fip.fail())
	{
		cout << "û���ļ������ȱ��룡\n";

		return;
	}
	while (fip.get(ch))
	{
		cout << ch;            //��ȡ�ļ�����   
		fop << ch;             //�浽�ļ���   
		if (i == 50)            //ÿ�����50���ַ�   
		{
			cout << endl;
			i = 0;
		}
		i++;
	}
	cout << endl;
	fip.close();          //�ر�CodeFile.dat�ļ�   
	fop.close();          //�ر�CodePrin.dat�ļ�   
}
int main()
{
	Init();
	PrintTree();
	HuffmanCoding();
	HuffmanTran();
	Print();
	return 0;
}

