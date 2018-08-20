#include<iostream> 
#include<fstream> 
#include<string> 
using namespace std;
struct HuffmanNode        //���������������� 
{
	int weight;              //��Ž���Ȩֵ������ֻ���Ǵ���ȨֵΪ��������� 
	int parent;              //��¼��㸸��λ�ã�-1��ʾΪ����㣬�����ʾΪ�Ǹ���� 
	int lchild, rchild;       //�ֱ��Ÿý������Һ��ӵ����ڵ�Ԫ�ı�� 
};
class HuffmanTree		  //�������������� 
{
private:
	HuffmanNode *Node;      //���������н��Ĵ洢�ṹ 
	char *Info;             //����������ַ���Ϣ 
	int LeafNum;            //���е�Ҷ�ӽ������ 
public:
	HuffmanTree();          //���캯�� 
	~HuffmanTree();         //�������� 
	void Initialization(int WeightNum);   //��ʼ������������WeightNum��Ȩֵ����һ�ù������� 
	void Encoder();         //���뺯�������ù���õĹ����������ַ����б��� 
	void Decoder();         //���뺯�����Զ����ƴ��������� 
	void Print();           //ӡ�ļ����������ѱ���õı����ļ���ʾ����Ļ 
}; 
