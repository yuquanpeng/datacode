#include"HuffmanTree.h"   
#include<string>  
 
using namespace std;
 
//  ���캯��     
HuffmanTree::HuffmanTree()
{
	Node = NULL;          //��������ʼ��Ϊ��    
	Info = NULL;          //���ַ������ʼ��Ϊ��   
	LeafNum = 0;          //��Ҷ������ʼ��Ϊ0   
} 
// ��������   
HuffmanTree::~HuffmanTree()
{
	delete[] Node;         //�ͷŽ��ռ�   
	delete[] Info;         //�ͷ��ַ��洢�ռ�   
} 
//  ��ʼ������   
//  �������ܣ����ն˶����ַ�����Сn���Լ�n���ַ���n��Ȩֵ,   
//            ������������,������������ļ�hfmTree��.   
//  ����������int WeightNum��ʾ�������   
//  ��������ֵ����    
void HuffmanTree::Initialization(int WeightNum)        //��ʼ��   
{
	int i, j, pos1, pos2, max1, max2;     //   

	Node = new HuffmanNode[2 * WeightNum - 1];  //WeightNumȨֵ��Ӧ�Ĺ��������еĽ������Ϊ2*WeightNum-1��   
	Info = new char[2 * WeightNum - 1];
	for (i = 0; i<WeightNum; i++)
	{
		cout << "�������" << i + 1 << "���ַ�ֵ";
		getchar();           //�����ַ�'\t'��'\n'   
		Info[i] = getchar();   //����һ���ַ�,��Ҫ�ǿ�������ո������������ʽ��   
		getchar();
		cout << "��������ַ���Ȩֵ��Ƶ��";
		cin >> Node[i].weight;       //����Ȩֵ   
		Node[i].parent = -1;      //Ϊ�����   
		Node[i].lchild = -1;      //������   
		Node[i].rchild = -1;      //���Һ���   
	}

	for (i = WeightNum; i<2 * WeightNum - 1; i++) //��ʾ����WeightNum-1�κϲ�   
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
				else
					if (Node[j].weight<max2)     //��ԭ��Сֵ�󵫱�ԭ��СֵҪС   
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
	LeafNum = WeightNum;


	char ch;
	cout << "�Ƿ�Ҫ�滻ԭ���ļ�(Y/N):";
	cin >> ch;
	if (ch == 'y' || ch == 'Y')
	{
		ofstream fop;   //�Զ����Ʒ�ʽ��hfmTree.dat�ļ���������������ʱ����ԭ�ļ�   
		fop.open("hfmTree.dat", ios::out | ios::binary | ios::trunc);
		if (fop.fail())                     //�ļ���ʧ��   
			cout << "�ļ���ʧ�ܣ�\n";
		fop.write((char*)&WeightNum, sizeof(WeightNum));  //д��WeightNum   
		for (i = 0; i<WeightNum; i++)         //�Ѹ��ַ���Ϣд���ļ�   
		{
			fop.write((char*)&Info[i], sizeof(Info[i]));
			flush(cout);
		}
		for (i = 0; i<2 * WeightNum - 1; i++)        //�Ѹ��ڵ�����д���ļ�   
		{
			fop.write((char*)&Node[i], sizeof(Node[i]));
			flush(cout);
		}
		fop.close();            //�ر��ļ�   
	}
	cout << "���������ѹ�����ɡ�\n";
} 
  
 //  ���뺯��   
 //  �������ܣ������ѽ����õĹ����������粻���ڴ棬����ļ�hfmTree�ж��룩��   
 //            ���ļ�ToBeTran�е����Ľ��б���,Ȼ�󽫽�������(����)���ļ�CodeFile��.   
 //  ������������   
 //  ��������ֵ����   
void HuffmanTree::Encoder()
{
	if (Node == NULL)        //�������������ڴ棬���ļ�hfmTree�ж���   
	{
		ifstream fip;        //�Զ����Ʒ�ʽ��hfmTree.dat�ļ�   
		fip.open("hfmTree.dat", ios::binary | ios::in);
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

	ofstream fop("CodeFile.dat", ios::trunc);      //�洢�����Ĵ���,������ԭ�ļ�   
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
}  //Encode   

   //  ���뺯��   
   //  �������ܣ������ѽ��õĹ�������,�Դ��䵽���CodeFile�е����ݴ����������,   
   //            �������������ļ�TextFile��.   
   //  ������������   
   //  ��������ֵ����   
void HuffmanTree::Decoder()
{
	int i = 0, k = 0;
	int j = LeafNum * 2 - 1 - 1;      //��ʾ�Ӹ���㿪ʼ��������   
	char* BitStr;

	ifstream fip1("CodeFile.dat");          //�����ѽ��õĹ����������ļ�CodeFile�еĴ����������   
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
	ifstream fip2("CodeFile.dat");
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
   
 //  ӡ�ļ����뺯��   
 //  �������ܣ����ļ�CodeFile�Խ��ո�ʽ��ʾ���ն��ϣ�   
 //            ÿ��50�����롣ͬʱ�����ַ���ʽ�ı����ļ�д���ļ�CodePrin�С�   
 //  ������������   
 //  ��������ֵ����   
void HuffmanTree::Print()
{
	char ch;
	int i = 1;
	ifstream fip("CodeFile.dat");           //��ȡ�ļ�   
	ofstream fop("CodePrin.dat");           //�洢�ļ�   
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