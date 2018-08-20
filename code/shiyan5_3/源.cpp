#include <stdio.h>
#include <string.h>
#define n 100// Ҷ�ӽ����
#define m 2*n-1//�շ������ֵĽ������



typedef struct {
	char ch;
	char bits[9];//��ű���λ��
	int len;//���볤��
}CodeNode;
typedef CodeNode HuffmanCode[n + 1];
typedef struct {
	int weight;//Ȩֵ
	int lchild, rchild, parent;//���Һ��Ӽ�˫��ָ��
}HTNode;//���еĽ������
typedef HTNode HuffmanTree[m + 1];//0�ŵ�Ԫ������
int num;//��ĸ���͵ĸ���
void select(HuffmanTree T, int k, int *s1, int *s2)
{//��HT[1����k]��ѡ��parentΪ0��Ȩֵ��С����������㣬����ŷֱ�ΪS1��S2
	int i, j;
	int min1 = 100;
	for (i = 1; i <= k; i++)//����s1
		if (T[i].weight<min1 && T[i].parent == 0)
		{
			j = i; min1 = T[i].weight;
		}
	*s1 = j;
	min1 = 32767;
	for (i = 1; i <= k; i++)//����s2,����s1��ͬ
		if (T[i].weight<min1 && T[i].parent == 0 && i != (*s1))
		{
			j = i;
			min1 = T[i].weight;
		}
	*s2 = j;
}

int jsq(char *s, int cnt[], char str[])
{
	//ͳ�Ƹ��ַ����и�����ĸ�ĸ����Լ��ַ�������
	char *p;
	int i, j, k;
	int temp[27];
	for (i = 1; i <= 26; i++)
		temp[i] = 0;
	for (p = s; *p != '\0'; p++)
	{//ͳ�Ƹ����ַ�����
		if (*p >= 'A' && *p <= 'Z') {
			k = *p - 64;
			temp[k]++;
		}
	}
	j = 0;
	for (i = 1, j = 0; i <= 26; i++)//ͳ���ж������ַ�
		if (temp[i] != 0) {
			j++;
			str[j] = i + 64;//����Ӧ�������͵�������
			cnt[j] = temp[i];//�����Ӧ�����Ȩֵ
		}
	return j;
}


void ChuffmanTree(HuffmanTree HT, HuffmanCode HC, int cnt[], char str[])
{//����շ�����HT
	int i, s1, s2;
	for (i = 1; i <= 2 * num - 1; i++)//��ʼ��HT�����Һ��ӣ�˫�ף�Ȩֵ��Ϊ0
	{
		HT[i].lchild = 0; HT[i].rchild = 0;
		HT[i].parent = 0; HT[i].weight = 0;
	}
	for (i = 1; i <= num; i++)//����num��Ҷ�ڵ��Ȩֵ
		HT[i].weight = cnt[i];
	for (i = num + 1; i <= 2 * num - 1; i++)//��numd���濪ʼ�½�����������ɵĸ��ڵ�
	{
		select(HT, i - 1, &s1, &s2);//��HT[1����i-1]��ѡ��parentΪ0��Ȩֵ��С����������㣬����ŷֱ�Ϊs1��s2
		HT[s1].parent = i; HT[s2].parent = i;//��s1��s2��parent��ֵ
		HT[i].lchild = s1; HT[i].rchild = s2;//�½������Һ���
		HT[i].weight = HT[s1].weight + HT[s2].weight;//�½���Ȩֵ
	}
	for (i = 0; i <= num; i++)//�����ַ����е��ַ�
		HC[i].ch = str[i];
	i = 1;
	while (i <= num)
		printf("�ַ� %c,����Ϊ: %d\n", HC[i].ch, cnt[i++]);
}



void HuffmanEncoding(HuffmanTree HT, HuffmanCode HC)
{//���ݺշ�����HT��շ��������HC
	int c, p, i, j;//c��p�ֱ�ָʾT�к��Ӻ�˫�׵�λ��
	char cd[n];//��ʱ��ű��봮
	int start;//ָʾ������cd�е���ʼλ��
	cd[num] = '\0';//���һλ���ϴ�������
	for (i = 1; i <= num; i++)
	{
		start = num;//��ʼλ��
		c = i;//��Ҷ�ӽڵ�T[i]��ʼ����
		while ((p = HT[c].parent)>0)//ֱ�����ݵ�HT[c]������Ϊֹ
		{//��T[c]��T[p]�������ӣ�������0���������ɴ���1
			cd[--start] = (HT[p].lchild == c) ? '0' : '1';//cd�����������ÿһ����ĸ��Ӧ��01���룬
			c = p;
		}//while ����
		strcpy_s(HC[i].bits, &cd[start]);//��cd�����е�01���븴�Ƶ�i�����
		HC[i].len = num - start;
	}//for ����
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
{//�����ļ�coodfile.txt������*�շ�*
	FILE *fp;
	char str[254];//����ԭ�ı��ļ�������254���ַ�
	char *p;
	static char cd[n + 1];
	int i, j, k = 0, cjs;
	fp = fopen("codefile.txt", "r");//���ļ�
	while (!feof(fp))
	{
		cjs = 0;
		for (i = 0; i<num && cjs == 0 && !feof(fp); i++)
		{
			cd[i] = ' ';
			cd[i + 1] = '\0';
			cd[i] = fgetc(fp);
			for (j = 1; j <= num; j++)
				if (strcmp(HC[j].bits, cd) == 0)//�������е���ĸ�Ķ�Ӧ�ı��룬�������ͬ���򽫸���ĸ����str��
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

void main() {
	char st[254], *s, str[27];
	int cn[27];
	HuffmanTree HT;
	HuffmanCode HC;
	printf("������Ҫ������ַ���(�����Ϊ��д��ĸ): \n");
	gets(st);
	num = jsq(st, cn, str);//ͳ���ַ������༰�����ַ����ֵ�Ƶ��
	ChuffmanTree(HT, HC, cn, str);//�����շ�����
	HuffmanEncoding(HT, HC);//���ɺշ�������
	coding(HC, st);//�������ĺշ��������ļ�
	s = decode(HC);//�������ļ�����
	printf("�������ַ���: \n");
	printf("%s\n", s);
}
