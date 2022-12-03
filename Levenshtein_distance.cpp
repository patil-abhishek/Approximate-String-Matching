#include <iostream>
#include <vector>
#include <string>
using namespace std;

void lev_dist(string &a, string &b)
{
	int m = a.length();
	int n = b.length();
	vector<vector<int>> d(m + 1, vector<int>(n + 1, 0));
	for (int i = 0; i <= m; i++)
		d[i][0] = i;
	for (int j = 0; j <= n; j++)
		d[0][j] = j;
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			int min1 = min(d[i - 1][j] + 1, d[i][j - 1] + 1);
			int min2 = d[i - 1][j - 1] + 1;
			if (a[i - 1] == b[j - 1])
				min2 -= 1;
			d[i][j] = min(min1, min2);
		}
	}
	cout <<"Edit distance : "<< d[m][n];
}

int main()
{
	string a, b;
	cout<<"enter 2 strings "<<endl;
	cin >> a >> b;
	lev_dist(a, b);
	return 0;
}