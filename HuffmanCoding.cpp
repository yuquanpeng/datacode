#include <stdio.h>
#include <string.h>
#define n 100// 叶子结点数
#define m 2*n-1//赫夫曼树种的结点总数



typedef struct {
	char ch;
	char bits[9];//存放编码位串
	int len;//编码长度
}CodeNode;
typedef CodeNode HuffmanCode[n + 1];
typedef struct {
	int weight;//权值
	int lchild, rchild, parent;//左右孩子及双亲指针
}HTNode;//树中的结点类型
typedef HTNode HuffmanTree[m + 1];//0号单元不可用
int num;//字母类型的个数
void select(HuffmanTree T, int k, int *s1, int *s2)
{//在HT[1……k]中选择parent为0且权值最小的两个根结点，其序号分别为S1和S2
	int i, j;
	int min1 = 100;
	for (i = 1; i <= k; i++)//查找s1
		if (T[i].weight<min1 && T[i].parent == 0)
		{
			j = i; min1 = T[i].weight;
		}
	*s1 = j;
	min1 = 32767;
	for (i = 1; i <= k; i++)//查找s2,不和s1相同
		if (T[i].weight<min1 && T[i].parent == 0 && i != (*s1))
		{
			j = i;
			min1 = T[i].weight;
		}
	*s2 = j;
}

int jsq(char *s, int cnt[], char str[])
{
	//统计各字符串中各种字母的个数以及字符的种类
	char *p;
	int i, j, k;
	int temp[27];
	for (i = 1; i <= 26; i++)
		temp[i] = 0;
	for (p = s; *p != '\0'; p++)
	{//统计各种字符个数
		if (*p >= 'A' && *p <= 'Z') {
			k = *p - 64;
			temp[k]++;
		}
	}
	j = 0;
	for (i = 1, j = 0; i <= 26; i++)//统计有多少种字符
		if (temp[i] != 0) {
			j++;
			str[j] = i + 64;//将对应的数组送到数组中
			cnt[j] = temp[i];//存入对应数组的权值
		}
	return j;
}


void ChuffmanTree(HuffmanTree HT, HuffmanCode HC, int cnt[], char str[])
{//构造赫夫曼树HT
	int i, s1, s2;
	for (i = 1; i <= 2 * num - 1; i++)//初始化HT，左右孩子，双亲，权值都为0
	{
		HT[i].lchild = 0; HT[i].rchild = 0;
		HT[i].parent = 0; HT[i].weight = 0;
	}
	for (i = 1; i <= num; i++)//输入num个叶节点的权值
		HT[i].weight = cnt[i];
	for (i = num + 1; i <= 2 * num - 1; i++)//从numd后面开始新建结点存放新生成的父节点
	{
		select(HT, i - 1, &s1, &s2);//在HT[1……i-1]中选择parent为0且权值最小的两个根结点，其序号分别为s1和s2
		HT[s1].parent = i; HT[s2].parent = i;//将s1和s2的parent赋值
		HT[i].lchild = s1; HT[i].rchild = s2;//新结点的左右孩子
		HT[i].weight = HT[s1].weight + HT[s2].weight;//新结点的权值
	}
	for (i = 0; i <= num; i++)//输入字符集中的字符
		HC[i].ch = str[i];
	i = 1;
	while (i <= num)
		printf("字符 %c,次数为: %d\n", HC[i].ch, cnt[i++]);
}



void HuffmanEncoding(HuffmanTree HT, HuffmanCode HC)
{//根据赫夫曼树HT求赫夫曼编码表HC
	int c, p, i, j;//c和p分别指示T中孩子和双亲的位置
	char cd[n];//临时存放编码串
	int start;//指示编码在cd中的起始位置
	cd[num] = '\0';//最后一位放上串结束符
	for (i = 1; i <= num; i++)
	{
		start = num;//初始位置
		c = i;//从叶子节点T[i]开始上溯
		while ((p = HT[c].parent)>0)//直至上溯到HT[c]是树根为止
		{//若T[c]是T[p]的做孩子，则生成0；否则生成代码1
			cd[--start] = (HT[p].lchild == c) ? '0' : '1';//cd数组用来存放每一个字母对应的01编码，
			c = p;
		}//while 结束
		strcpy(HC[i].bits, &cd[start]);//将cd数组中德01代码复制到i结点中
		HC[i].len = num - start;
	}//for 结束
}


void coding(HuffmanCode HC, char *str)
{
	int i, j;
	FILE *fp;
	fp = fopen("codefile.txt", "w");
	while (*str) {
		for (i = 1; i <= num; i++)
			if (HC[i].ch == *str) {
				for (j = 0; j<HC[i].len; j++) {
					fputc(HC[i].bits[j], fp);

				}
				break;
			}
		str++;
	}
	fclose(fp);
}



char * decode(HuffmanCode HC)
{//代码文件coodfile.txt的译码*菡枫*
	FILE *fp;
	char str[254];//假设原文本文件不超过254个字符
	char *p;
	static char cd[n + 1];
	int i, j, k = 0, cjs;
	fp = fopen("codefile.txt", "r");//读文件
	while (!feof(fp))
	{
		cjs = 0;
		for (i = 0; i<num && cjs == 0 && !feof(fp); i++)
		{
			cd[i] = ' ';
			cd[i + 1] = '\0';
			cd[i] = fgetc(fp);
			for (j = 1; j <= num; j++)
				if (strcmp(HC[j].bits, cd) == 0)//查找所有的字母的对应的编码，如果有相同的则将该字母放入str中
				{
					str[k] = HC[j].ch;
					k++;
					cjs = 1;
					break;
				}
		}
	}
	str[k] = '\0';
	p = str;
	return p;
}

int main() {
	char st[254], *s, str[27];
	int cn[27];
	HuffmanTree HT;
	HuffmanCode HC;
	printf("输入需要编码的字符串(假设均为大写字母): \n");
	gets(st);
	num = jsq(st, cn, str);//统计字符的种类及各类字符出现的频率
	ChuffmanTree(HT, HC, cn, str);//建立赫夫曼树
	HuffmanEncoding(HT, HC);//生成赫夫曼编码
	coding(HC, st);//建立电文赫夫曼编码文件
	s = decode(HC);//读编码文件译码
	printf("译码后的字符串: \n");
	printf("%s\n", s);
	return 0;
}

