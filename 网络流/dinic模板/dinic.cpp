#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <algorithm>
#include <vector>
#define MAXN 110
using namespace std;
struct Edge
{
	int from, to, cap, flow;
	Edge(int u, int v, int c, int f) :from(u), to(v), cap(c), flow(f) {}
	Edge() {}
};
struct Dinic
{
	int n, m, s, t;//节点数 边数(包括反向弧) 原点编号 汇点编号
	vector<Edge> edges;//边表 edges[e]和edges[e^1]互为反向弧
	vector<int> G[MAXN];//邻接表
	bool vis[MAXN];
	int d[MAXN];
	int cur[MAXN];

};
int main(void)
{



	return 0;
}