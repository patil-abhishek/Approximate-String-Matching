#include <iostream>
#include <vector>
#include <string>
#include <limits.h>
using namespace std;

void disp(vector<vector<int>> &p, string &a, string &b, int i, int j, string &sol1, string &sol2)
{
	if (i == 0 || j == 0)
	{
		return;
	}
	if (p[i][j] == 2)
	{
		disp(p, a, b, i - 1, j - 1, sol1, sol2);
		sol1.push_back(a[i - 1]);
		sol2.push_back(b[j - 1]);
	}
	else if (p[i][j] == 1)
	{
		disp(p, a, b, i, j - 1, sol1, sol2);
		sol1.append("-");
		sol2.push_back(b[j - 1]);
	}
	else 
	{
		disp(p, a, b, i - 1, j, sol1, sol2);
		sol2.append("-");
		sol1.push_back(a[i - 1]);
	}
	return;
}

int main()
{
	string a, b;
	cout<<"enter string A: ";
	getline(cin,a);
	cout<<"enter string B: ";
	getline(cin,b);
	int m = a.length();
	int n = b.length();
	int gap = -2, match = 0, mismatch = -1;
	vector<vector<int>> d(m + 1, vector<int>(n + 1, 0));
	vector<vector<int>> p(m + 1, vector<int>(n + 1, 0));
	for (int i = 1; i <= m; i++)
		d[i][0] = i * gap;
	for (int j = 1; j <= n; j++)
		d[0][j] = j * gap;
	//lu=2 l=1 u=3
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			int val = INT_MIN;
			if (a[i - 1] == b[j - 1])
				if (val < d[i - 1][j - 1] + match)
				{
					val = d[i - 1][j - 1] + match;
					p[i][j] = 2;
				}
				else if (val < d[i - 1][j - 1] + mismatch)
				{
					val = d[i - 1][j - 1] + mismatch;
					p[i][j] = 2;
				}
			if (val < d[i - 1][j] + gap)
			{
				val = d[i - 1][j] + gap;
				p[i][j] = 3;
			}
			if (val < d[i][j - 1] + gap)
			{
				val = d[i][j - 1] + gap;
				p[i][j] = 1;
			}
			d[i][j] = val;
		}
	}
	cout <<"Score : "<< d[m][n] << endl;
	string sol1 = "";
	string sol2 = "";
	disp(p, a, b, m, n, sol1, sol2);
	cout<<"optimally aligned strings"<<endl;
	cout << sol1 << endl;
	cout << sol2 << endl;
	return 0;
}