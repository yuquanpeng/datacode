#include<iostream>
using namespace std;
const int MAX = 100;
int l[MAX + 1];//��ž��������ֵ
int m[MAX][MAX];//������¼��i��j����������Ž�
int t[MAX][MAX];//������¼���Ž�Ķϵ�
int n;//�������
int MaxtrixChain()
{
	for (int i = 0; i <= n; i++)
		m[i][i] = 0;//��ʼ������
	for (int k = 2; k <= n; k++)
	{
		for (int i = 0; i <= n - k; i++)
		{
			int j = k + i - 1;
			m[i][j] = m[i + 1][j] + l[i + 1] * l[i] * l[j + 1];
			t[i][j] = i;
			for (int q = i+1; q < j; q++)
			{
				int temp = m[i][q] + m[q + 1][j] + l[i] * l[q + 1] * l[j + 1];
				if (temp < m[i][j])
				{
					m[i][j] = temp;
					t[i][j] = q;
				}
			}
		}
	}
	return m[0][n-1];
}
void print(int i, int j)
{
	if (i == j)
	{
		cout << (char)('A' + i);
		return;
	}

	if (i < t[i][j])
		cout << '(';
	print(i, t[i][j]);

	if (i < t[i][j])
		cout << ')';
	if (t[i][j] + 1<j)
		cout << '(';
	print(t[i][j] + 1, j);

	if (t[i][j] + 1<j)
		cout << ')';
}
void print()
{
	cout << '(';
	print(0, n - 1);
	cout << ')';
	cout << endl;
}
int main()
{
	cout << "���������ĸ����� ";
	cin >> n;
	cout << "�������A10*30*B30*70*C70*1*D1*200 -> 10 30 70 1 200�� :" << endl;
	for (int i = 0; i <= n; i++)
		cin >> l[i];
	cout << "�������� " ;
	MaxtrixChain();
	print(0, n - 1); //���ս�ֵΪ m[0][n-1];
	cout << endl;
	return 0;
}
