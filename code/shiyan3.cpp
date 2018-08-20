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
		cout << "无法匹配" << endl;
		return 0;
	}
}
void StrAssign(SString &S, string s)// 生成一个其值等于s的串T ""
{
	int i;
	if (s.length() > MAXLEN)
	{
		cout << "数组长度超出MAXLEN" << endl;
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
	SString S, T;//主串和模式串
	string s,t;
	ifstream input("D:\string1.dat",ios::in);
	if (!input)
	{
		cout << "文件打开失败" << endl;
		exit(1);
	}
	input >> s;
	input.close();
	StrAssign(S, s);//主串
	cout << s << endl;
	cout << "请输入你要匹配的模式串：";
	cin >> t;
	StrAssign(T, t);
	cout << Index(S, T, 1);
	return 0;
}
