#include"HuffmanTree.h"   
#include<string.h>   
#include<stdlib.h>   
  

int main()
{
	cout << "哈夫曼码的编/译码系统!\n";
	cout << "1 初始化\n";
	cout << "2 编码\n";
	cout << "3 译码\n";
	cout << "4 输出代码文件\n";
	cout << "6 退出\n";
	HuffmanTree huftree;         //定义哈夫曼树对象   
	int weight;
	int Choose;
	while (1)
	{
		cout << "请输出序号：";
		cin >> Choose;
		switch (Choose)
		{
		case 1:
			cout << "请输入编码长度：";
			cin >> weight;
			huftree.Initialization(weight);      //初始化哈夫曼树   
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