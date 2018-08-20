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
	cout << "请输入字符的个数：";
	cin >> weightNum;
	Node = new HuffmanNode[2 * weightNum - 1];  //WeightNum权值对应的哈夫曼树中的结点总数为2*WeightNum-1个   
	Info = new char[2 * weightNum - 1];
	for (i = 0; i<weightNum; i++)
	{
		cout << "请输入第" << i + 1 << "个字符值:";
		getchar();           //丢弃字符'\t'与'\n'   
		Info[i] = getchar();   //输入一个字符,主要是考虑输入空格而采用这种形式的   
		getchar();
		cout << "请输入该字符的权值(出现的次数):";
		cin >> Node[i].weight;       //输入权值   
		Node[i].parent = -1;      //为根结点   
		Node[i].lchild = -1;      //无左孩子   
		Node[i].rchild = -1;      //无右孩子   
	}

	for (i = weightNum; i<2 * weightNum - 1; i++) //表示需做WeightNum-1次合并   
	{
		pos1 = -1;
		pos2 = -1;          //分别用来存放当前最小值和次小值的所在单元编号    
		max1 = 32767;      //32767为整型数的最大值    
		max2 = 32767;      //分别用来存放当前找到的最小值和次小值     

		for (j = 0; j<i; j++)      //在跟节点中选出权值最小的两个   
			if (Node[j].parent == -1)         //是否为根结点   
				if (Node[j].weight<max1)     //是否比最小值要小   
				{
					max2 = max1;            //原最小值变为次小值   
					max1 = Node[j].weight;      //存放最小值   
					pos2 = pos1;            //修改次小值所在单元编号   
					pos1 = j;               //修改最小值所在单元编号   
				}
				else if (Node[j].weight<max2) //比原最小值大但比原次小值要小      
				{
					max2 = Node[j].weight;     //存放次小值   
					pos2 = j;                  //修改次小值所在的单元编号   
				}
		//for   
		Node[pos1].parent = i;       //修改父亲位置   
		Node[pos2].parent = i;
		Node[i].lchild = pos1;       //修改儿子位置   
		Node[i].rchild = pos2;
		Node[i].parent = -1;             //表示新结点应该是根结点   
		Node[i].weight = Node[pos1].weight + Node[pos2].weight;
	} //for   
	LeafNum = weightNum;

	ofstream fop;   //以二进制方式打开hfmTree.dat文件，并当重新运行时覆盖原文件   
	fop.open(PATH_1, ios::out | ios::binary | ios::trunc);
	if (fop.fail())                     //文件打开失败   
		cout << "文件打开失败！\n";
	fop.write((char*)&weightNum, sizeof(weightNum));  //写入WeightNum   
	for (i = 0; i<weightNum; i++)         //把各字符信息写入文件   
	{
		fop.write((char*)&Info[i], sizeof(Info[i]));
		flush(cout);
	}
	for (i = 0; i<2 * weightNum - 1; i++)        //把个节点内容写入文件   
	{
		fop.write((char*)&Node[i], sizeof(Node[i]));
		flush(cout);
	}
	fop.close();            //关闭文件   
	cout << "哈夫曼树已构造完成" << endl;
}

void PrintTree()
{
	if (Node == NULL)         //未建立哈夫曼树   
	{
		cout << "出错了\n";
		return;
	}
	ofstream fop(PATH_1);
	cout << "结点位置(权值)  " << "编码  " << "左孩子  " << "编码" << "右孩子('^'表示叶子)\n";
	fop << "结点位置(权值)  " << "编码  " << "左孩子  " << "编码" << "右孩子('^'表示叶子)\n";
	int i;
	for (i = (2 * LeafNum - 2); i>LeafNum - 1; i--)        //输出哈夫曼树   
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
	if (Node == NULL)        //哈夫曼树不在内存，从文件hfmTree中读入   
	{
		ifstream fip;        //以二进制方式打开hfmTree.dat文件   
		fip.open(PATH_1, ios::binary | ios::in);
		if (fip.fail())       //文件打开失败   
		{
			cout << "文件打开失败！\n";
			return;             //结束本函数   
		}
		fip.read((char*)&LeafNum, sizeof(LeafNum));  //读取叶子数   
		Info = new char[LeafNum];
		Node = new HuffmanNode[2 * LeafNum - 1];
		for (int i = 0; i<LeafNum; i++)                  //读取字符信息   
			fip.read((char*)&Info[i], sizeof(Info[i]));
		for (int i = 0; i<2 * LeafNum - 1; i++)              //读取结点信息   
			fip.read((char*)&Node[i], sizeof(Node[i]));
	}

	char *Tree;          //用于存储需编码内容   
	int i = 0, num;
	string tree;         //用于输入需编码内容，由于string类对象可以输入任意长度，   
						 //所以先利用这个对象输入，再转存在Tree中   
	cin.ignore();
	cout << "请输入需要编码的内容(可输入任意长，结束时请按2下回车):\n";
	getline(cin, tree, '\n');         //输入任意长字符串，   
									  //getline以回车('\n')作为结束符，第一次按回车表示字符串结束，第二次按回车才开始输出。   
	while (tree[i] != '\0')
		i++;
	num = i;                     //计算tree长度   
	i = 0;
	Tree = new char[num + 1];
	while (tree[i] != '\0')       //将tree中的字符转存到Tree中   
	{
		Tree[i] = tree[i];
		i++;
	}
	Tree[i] = '\0';          //结束标志符   

	ofstream fop(PATH_2, ios::trunc);      //存储编码后的代码,并覆盖原文件   
	i = 0;
	int k = 0;
	char *code;
	code = new char[LeafNum];        //为所产生编码分配容量为LeafNum的存储空间   
									 //因为不等长编码中最长的编码一定不会超过要求编码的字符个数   
	while (Tree[k] != '\0')           //对每一个字符编码   
	{
		int j, start = 0;
		for (i = 0; i<LeafNum; i++)
			if (Info[i] == Tree[k])            //求出该文字所在单元的编号   
				break;
		j = i;
		while (Node[j].parent != -1)        //结点j非树根   
		{
			j = Node[j].parent;               //非结点j的双亲结点   
			if (Node[j].lchild == i)           //是左子树，则生成代码0   
				code[start++] = '0';
			else                            //是右子树，则生成代码1   
				code[start++] = '1'; \
				i = j;
		}
		code[start] = '\0';                //置串结束符   


		for (i = 0; i<start / 2; i++)           //对二进制序列进行逆置   
		{
			j = code[i];
			code[i] = code[start - i - 1];
			code[start - i - 1] = j;
		}
		i = 0;
		while (code[i] != '\0')             //存储代码   
		{
			fop << code[i];
			i++;
		}
		k++;
	}
	fop.close();
	cout << "已编码！且存到文件CodeFile.dat中！\n\n";
}


void HuffmanTran()
{
	int i = 0, k = 0;
	int j = LeafNum * 2 - 1 - 1;      //表示从根结点开始往下搜索   
	char* BitStr;

	ifstream fip1(PATH_2);          //利用已建好的哈夫曼树将文件CodeFile中的代码进行译码   
	if (fip1.fail())           //文件打开失败，还未编码   
	{
		cout << "请先编码！\n";
		return;
	}
	cout << "经译码,原内容为:";
	char ch;
	while (fip1.get(ch))
	{
		k++;                     //计算CodeFile中代码长度   
	}
	fip1.close();

	BitStr = new char[k + 1];
	ifstream fip2(PATH_2);
	k = 0;
	while (fip2.get(ch))
	{
		BitStr[k] = ch;          //读取文件内容   
		k++;
	}
	fip2.close();
	BitStr[k] = '\0';         //结束标志符   
	if (Node == NULL)          //还未建哈夫曼树   
	{
		cout << "请先编码!\n";
		return;
	}
	ofstream fop("TextFile.dat");         //将字符形式的编码文件写入文件CodePrin中   
	while (BitStr[i] != '\0')
	{
		if (BitStr[i] == '0')
			j = Node[j].lchild;        //往左走   
		else
			j = Node[j].rchild;        //往右走   
		if (Node[j].rchild == -1)    //到达叶子结点   
		{
			cout << Info[j];           //输出叶子结点对应的字符   
			j = LeafNum * 2 - 1 - 1;         //表示重新从根结点开始往下搜索   
			fop << Info[j];            //存入文件   
		}//if、   
		i++;
	}//while   
	fop.close();

	cout << "\n译码成功且已存到文件TextFile.dat中！\n\n";
}
void Print()
{
	char ch;
	int i = 1;
	ifstream fip(PATH_1);           //读取文件   
	ofstream fop(PATH_2);           //存储文件   
	if (fip.fail())
	{
		cout << "没有文件，请先编码！\n";

		return;
	}
	while (fip.get(ch))
	{
		cout << ch;            //读取文件内容   
		fop << ch;             //存到文件中   
		if (i == 50)            //每行输出50个字符   
		{
			cout << endl;
			i = 0;
		}
		i++;
	}
	cout << endl;
	fip.close();          //关闭CodeFile.dat文件   
	fop.close();          //关闭CodePrin.dat文件   
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

