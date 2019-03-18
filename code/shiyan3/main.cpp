#include<iostream>
#include<string>
#include<fstream>
using namespace std;
#define PATH "D:/string1.txt"
#define MAXLEN 10240
typedef char SString[MAXLEN + 1];
int Length(SString S)
{
	return strlen(S);
}
//�ڶ����㷨  next
int Index_KMP(SString S, SString T, int pos,int next[])
{
	int i = pos;
	int j = 1;
	while (i <= Length(S) && j <= Length(T))
	{
		if (j == 0 || S[i] == T[j])
		{
			++i; ++j;
		}
		else
			j = next[j];
		if (j == Length(T))
			break;
	}
	if (j >= Length(T))
		return i - Length(T);
	else
		return 0;
}
void get_next(SString S,int next[])
{
	int i = 1;
	next[1] = 0;
	int j = 0;
	while (i < Length(S))
	{
		if (j == 0 || S[i] == S[j])
		{
			++i; ++j; next[i] = j;
		}
		else
			j = next[j];
	}
}
void StrAssign(SString S, char* s)// ����һ����ֵ����s�Ĵ�T 
{
	int i = 0;
	S[0] = '0';
	for (i = 0; i<=strlen(s); ++i)
	{
		S[i+1] = s[i];
	}
	S[i] = '\0';
}
int main()
{
	SString S, T;//������ģʽ��
	char s[MAXLEN]="\0", t[100];
	int next[100] = {0};
	char ch;
	int i = 0;
	ifstream input(PATH);
	if (!input)
	{
		cout << "�ļ���ʧ��" << endl;
		exit(1);
	}
	while (!input.eof())
	{
		input.get(ch);
		s[i] = ch;
		i++;
	}
	input.close();
	StrAssign(S, s);//����
	cout << "��������Ҫƥ���ģʽ����";
	cin.get(t,100);
	StrAssign(T, t);
	get_next(T, next);
	if (Index_KMP(S, T, 1, next) == 0)
		cout << "��������δƥ�䵽���ַ���" << endl;
	else
		cout << "�ڵ�" << Index_KMP(S, T, 1, next)+1 << "λ" << endl;

	return 0;
}
/*
#include<iostream>
#include<string>
#include<fstream>
using namespace std;
#define PATH "D:/string1.txt"
#define MAXLEN 10240
typedef char SString[MAXLEN + 1];
int Length(SString S)
{
return strlen(S);
}
//��һ���㷨 ����ƥ��
int Index(SString S, SString T, int pos)
{
	int m = 0;
	int n = 0;
	int i = pos;
	int j = 0;
	while (i <= Length(S) && j <= Length(T))
	{
		if (S[i] == T[j])
		{
			++i;
			++j;
			if (j == Length(T))//���������
			{
				m = 1;
				n = i;
			}
		}
		else
		{
			i = i - j + 1; j = 0;
		}
	}
	if (m == 1)
	return n - Length(T)+1;
	else
	return 0;
}
void StrAssign(SString S, char* s)// ����һ����ֵ����s�Ĵ�T
{
	int i;
	for (i = 0; i<strlen(s); ++i)
	{
		S[i] = s[i];
	}
	S[i] = '\0';
}
int main()
{
	SString S, T;//������ģʽ��
	char s[MAXLEN]="\0", t[100];
	int next[100] = {0};
	char ch;
	int i = 0;
	ifstream input(PATH);
	if (!input)
	{
		cout << "�ļ���ʧ��" << endl;
		exit(1);
	}
	while (!input.eof())
	{
		input.get(ch);
		s[i] = ch;
		i++;
	}
	input.close();
	StrAssign(S, s);//����
	cout << "��������Ҫƥ���ģʽ����";
	cin.get(t,100);
	StrAssign(T, t);
	if (Index(S, T, 0) == 0)
	cout << "��������δƥ�䵽���ַ���" << endl;
	else
	cout << "�ڵ�"<<Index(S, T, 0) <<"λ"<< endl;

	return 0;
}
*/