#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#define SIGMA_SIZE 26
#define MAXN_TEXT_LEN 1000111
#define MAXN_M_LEN 77
#define MAXNNODE 155
using namespace std;
char text[MAXN_TEXT_LEN], P[MAXNNODE][MAXN_M_LEN];
map<string, int> ms;
struct AHO_CORASICK
{
	int ch[MAXNNODE][SIGMA_SIZE];
	int val[MAXNNODE];//每个字符串的结尾节点都有一个非零的val
	int f[MAXNNODE];//fail函数
	int last[MAXNNODE];//输出链表的下一个节点
	int cnt[MAXNNODE];
	int sz;

	AHO_CORASICK() { sz = 1; memset(ch[0], 0, sizeof(ch[0])); }
	void init()
	{
		sz = 1;
		memset(ch[0], 0, sizeof(ch[0]));
		memset(cnt, 0, sizeof(cnt));
		ms.clear();
	}
	int idx(char c) { return c - 'a'; }//字符串c的编号
	void insert(char* s, int v)
	{
		int u = 0, n = strlen(s);
		for (int i = 0; i < n; i++)
		{
			int c = idx(s[i]);

			if (!ch[u][c])
			{
				memset(ch[sz], 0, sizeof(ch[sz]));
				val[sz] = 0;
				ch[u][c] = sz++;
			}
			u = ch[u][c];
		}
		val[u] = v;
		ms[string(s)] = v;
	}
	void getFail()
	{
		queue<int> q;
		f[0] = 0;//初始化队列

		for (int c = 0; c < SIGMA_SIZE; c++)
		{
			int u = ch[0][c];
			if (u) { f[u] = 0; q.push(u); last[u] = 0; }
		}
		//按BFS顺序计算fail
		while (!q.empty())
		{
			int r = q.front();

			q.pop();
			for (int c = 0; c < SIGMA_SIZE; c++)
			{
				int u = ch[r][c];
				if (!u)continue;
				q.push(u);
				int v = f[r];
				while (v && !ch[v][c])
					v = f[r];
				f[u] = ch[v][c];
				last[u] = val[f[u]] ? f[u] : last[f[u]];
			}
		}
	}
	void find(char* T)
	{
		int n = strlen(T);
		int j = 0;

		for (int i = 0; i < n; i++)
		{
			int c = idx(T[i]);

			while (j && !ch[j][c])j = f[j];
			j = ch[j][c];
			if (val[j])print(j);
			else if (last[j])print(last[j]);
		}
	}
	void print(int j)
	{
		if (j)
		{
			//printf("%d: %d\n", j, val[j]);
			cnt[val[j]]++;
			print(last[j]);
		}
	}
}ac;
int main(void)
{
	int n;

	while (scanf("%d", &n) != EOF && n)
	{
		ac.init();
		for (int i = 1; i <= n; i++)
		{
			scanf("%s", P[i]);
			ac.insert(P[i], i);
		}

		ac.getFail();
		scanf("%s", text);
		ac.find(text);
		int best = -1;
		for (int i = 1; i <= n; i++)best = max(best, ac.cnt[i]);
		printf("%d\n", best);
		for (int i = 1; i <= n; i++)if (ac.cnt[ms[string(P[i])]] == best)printf("%s\n", P[i]);
	}


	return 0;
}