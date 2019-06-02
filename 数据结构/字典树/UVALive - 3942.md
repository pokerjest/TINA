[题目传送门](https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1943)字典树的入门 加上简单的dp  
```cpp
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <vector>
using namespace std;
const int maxnode = 4000 * 100 + 65536;
const int sigma_size = 26;
const int maxl = 300333;
const int maxw = 4444;
const int maxwl = 111;
const int MOD = 20071027;
struct Tire
{
	int ch[maxnode][sigma_size];
	int val[maxnode];
	int sz;//节点总数
	Tire() { sz = 1; memset(ch[0], 0, sizeof(ch[0])); }//初始只有一个根结点
	int idx(char c) { return c - 'a'; }//字符c的编号
	void clear(void) { sz = 1; memset(ch[0], 0, sizeof(ch[0])); }
	void insert(char* s, int v)
	{
		int u = 0, n = strlen(s);

		for (int i = 0; i < n; i++)
		{
			int c = idx(s[i]);

			if (!ch[u][c])
			{//节点不存在
				memset(ch[sz], 0, sizeof(ch[sz]));
				val[sz] = 0;//中间节点附加信息为0
				ch[u][c] = sz++;//新建节点
			}
			u = ch[u][c];//往下走
		}
		val[u] = v;//字符串最后一个字符的附加信息为v
	}
	void find_predixes(const char* s, int len, vector<int>& ans)
	{
		int u = 0;

		for (int i = 0; s[i]; i++)
		{
			int c = idx(s[i]);

			if (!ch[u][c])break;
			u = ch[u][c];
			if (val[u] != 0)ans.push_back(val[u]);//如果有单词就存入vector
		}
	}
}tire;
int dp[maxl], len[maxw];
char word[maxwl];
char text[maxl];
//string word;
int main(void)
{
	int kase = 1;
	int n;

	//cin >>text;
	while (cin >> text >> n)
	{
		//cin >> n;
		//Tire tire;结构体里面的数组太多了 因此不能在main函数里面定义这个结构体 否则爆栈
		tire.clear();
		for (int i = 1; i <= n; i++)
		{
			cin >> word;
			len[i] = strlen(word);
			tire.insert(word, i);//将每个单词和每个单词的特征码放进去
		}
		memset(dp, 0, sizeof(dp));
		int L = strlen(text);
		dp[L] = 1;
		for (int i = L - 1; i >= 0; i--)
		{//从后往前遍历 
			vector<int> p;//在i位置之后还有多少个以text[i]开头的单词
			tire.find_predixes(text + i, L - i, p);
			for (int j = 0; j < p.size(); j++)//i+len[p[j]]指的是当前位置加上接入的长度
				dp[i] = (dp[i] + dp[i + len[p[j]]]) % MOD;
		}
		printf("Case %d: %d\n", kase++, dp[0]);
	}


	return 0;
}
```