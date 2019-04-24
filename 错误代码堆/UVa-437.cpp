#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <algorithm>
#define pii pair<int, int>
#define X first
#define Y second
#define MAXN 1000
using namespace std;
struct Node
{
	int a, b, c;
}cuboid_edge;
vector<pii> cuboid;
int heigh[MAXN];
pii mmp[MAXN][MAXN];
vector<int>G[MAXN];
int d[MAXN];
int n;
int dp(int i)
{
	int& ans = d[i];

	if (ans > 0)return ans;
	ans = 0;
	for (int j = 0; j < G[i].size(); j++)
		ans = max(ans, dp(j) + heigh[G[i][j]]);
	ans += d[i];
	return ans;
}
bool fun(pii x, pii y)
{
	bool ok = ((mmp[x.X][x.Y].X > mmp[y.X][y.Y].X && mmp[x.X][x.Y].Y > mmp[y.X][y.Y].Y) || (mmp[x.X][x.Y].X > mmp[y.X][y.Y].Y && mmp[x.X][x.Y].Y > mmp[y.X][y.Y].X));
	return ok;
}
void init(void)
{
	cuboid.clear();
	for (int i = 0; i < MAXN; i++)G[i].clear();
	memset(d, 0, sizeof(d));
}
int solve(void)
{
	int a[3];
	int ans = 0;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 3; j++)scanf("%d", &a[j]);
		//sort(a, a + 3);
		mmp[i][0] = pii(a[1], a[2]);
		mmp[i][1] = pii(a[0], a[2]);
		mmp[i][2] = pii(a[1], a[0]);
		for (int j = 0; j < 3; j++) { heigh[cuboid.size()] = a[j]; cuboid.push_back(pii(i, j)); }
	}
	for (int i = 0; i < cuboid.size(); i++)
		for (int j = 0; j < cuboid.size(); j++)
			if (i!=j && fun(cuboid[i], cuboid[j]))
				G[i].push_back(j);
	for (int i = 0; i < cuboid.size(); i++)ans = max(ans, dp(i));
	
	return ans;
}
int main(void)
{
	//int n;

	while (scanf("%d", &n) != EOF && n)
	{	
		init();
		printf("%d\n", solve());
	}

	return 0;
}