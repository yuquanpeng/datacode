#include<iostream>
#include<string>
#include<fstream>
using namespace std;
#define MAXLEN 1024
typedef unsigned char SString[MAXLEN + 1];
int Index(SString S, SString T, int pos)
{
	int i = pos;
	int j = 1;
	if (1 <= pos&&pos <= S[0])
	{
		while (i <= S[0] && j <= T[0])
		{
			if (S[i] == T[i])
			{
				++i;
				++j;
			}
			else
			{
				i = i - j + 2; j = 1;
			}
			if (j > T[0])
				return i - T[0];
			else
				return 0;
		}
	}
	else
	{
		cout << "�޷�ƥ��" << endl;
		return 0;
	}
}
void StrAssign(SString &S, string s)// ����һ����ֵ����s�Ĵ�T ""
{
	int i;
	if (s.length() > MAXLEN)
	{
		cout << "���鳤�ȳ���MAXLEN" << endl;
		exit(1);
	}
	else
	{
		S[0] = s.length();
		for (i = 1; i <= S[0]; i++)
			S[i] = s[i];
	}
}
int main()
{
	SString S, T;//������ģʽ��
	string s,t;
	ifstream input("D:\string1.dat",ios::in);
	if (!input)
	{
		cout << "�ļ���ʧ��" << endl;
		exit(1);
	}
	input >> s;
	input.close();
	StrAssign(S, s);//����
	cout << s << endl;
	cout << "��������Ҫƥ���ģʽ����";
	cin >> t;
	StrAssign(T, t);
	cout << Index(S, T, 1);
	return 0;
}
