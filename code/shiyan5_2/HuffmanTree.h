#include<iostream> 
#include<fstream> 
#include<string> 
using namespace std;
struct HuffmanNode        //定义哈夫曼树各结点 
{
	int weight;              //存放结点的权值，假设只考虑处理权值为整数的情况 
	int parent;              //记录结点父亲位置，-1表示为根结点，否则表示为非根结点 
	int lchild, rchild;       //分别存放该结点的左、右孩子的所在单元的编号 
};
class HuffmanTree		  //建立哈夫曼树类 
{
private:
	HuffmanNode *Node;      //哈夫曼树中结点的存储结构 
	char *Info;             //用来保存各字符信息 
	int LeafNum;            //树中的叶子结点总数 
public:
	HuffmanTree();          //构造函数 
	~HuffmanTree();         //析构函数 
	void Initialization(int WeightNum);   //初始化函数：根据WeightNum个权值建立一棵哈夫曼树 
	void Encoder();         //编码函数：利用构造好的哈夫曼树对字符进行编码 
	void Decoder();         //译码函数：对二进制串进行译码 
	void Print();           //印文件函数：把已保存好的编码文件显示在屏幕 
}; 
