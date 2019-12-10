#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <algorithm>
#include <queue>
#include <vector>
#define MAXN 10100
#define MAXE 10100
#define INF 1<<22
struct Edge
{
	int from, to, dist;
	Edge(int f, int t, int d) :from(f), to(t), dist(d) {}
	Edge() {}
};
struct HeapNode
{
	int d, u;//d表示边的权值，u表示边的编号
	HeapNode(int dist, int id) :d(dist), u(id) {}
	bool operator < (const HeapNode& rhs)const
	{//边的权值小的先出去
		return d > rhs.d;
	}
};
using namespace std;
struct Dijkstra
{
	int n, m;//点数和边数
	vector<Edge> edges;//边列表
	vector<int> G[MAXN];//每个节点出发的边编号从0开始
	//bool e_book[MAXN];//判断这条边是否在最短路的集合
	bool done[MAXN];//是否已永久标记
	int d[MAXN];//s到各个点的距离
	int p[MAXN];//最短路上的一条边

	void init(int n)
	{
		this->n = n;
		for (int i = 0; i < n; i++)G[i].clear();
		edges.clear();
	}
	void AddEdge(int from, int to, int dist)
	{
		edges.push_back(Edge(from, to, dist));
		m = edges.size();
		G[from].push_back(m - 1);//为每条边编上号
	}
	void dijkstra(int s)
	{//求s到所有点的距离
		priority_queue<HeapNode> Q;
		for (int i = 0; i < n; i++)d[i] = INF;
		d[s] = 0;//起始点到自己的距离为0
		memset(done, 0, sizeof(done));
		Q.push(HeapNode(0, s));//把第一个节点压入优先队列
		while (!Q.empty())
		{
			HeapNode x = Q.top();
			Q.pop();
			int u = x.u;
			if (done[u])continue;//如果这个节点已经走过了就选别的节点
			done[u] = true;//标记要走的节点
			for (int i = 0; i < G[u].size(); i++)
			{
				Edge& e = edges[G[u][i]];
				//测试这个节点通向的所有点的边
				if (d[e.to] > d[u] + e.dist)
				{//如果存在更短的路径就更新它
					d[e.to] = d[u] + e.dist;
					p[e.to] = G[u][i];
					Q.push(HeapNode(d[e.to], e.to));
				}
			}
		}
	}
};
Dijkstra dijkstra;
int main(void)
{
	int T;

	freopen("acm.in", "r", stdin);
	freopen("acm.out", "w", stdout);
	for (scanf("%d", &T); T; T--)
	{
		int n, m;

		scanf("%d%d", &n, &m);
		dijkstra.init(n);
		for (int i = 0; i < m; i++)
		{
			int from, to, dist;

			scanf("%d%d%d", &from, &to, &dist);
			dijkstra.AddEdge(from, to, dist);
		}

		for (int i = 0; i < 6; i++)
		{
			int x, y;

			scanf("%d%d", &x, &y);
			dijkstra.dijkstra(y);
			printf("%d\n", -dijkstra.d[x]);
			dijkstra.AddEdge(x, y, -dijkstra.d[x]);
		}
	}

	return 0;
}
