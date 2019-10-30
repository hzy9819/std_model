#include<cmath>
#include<ctime>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<iomanip>
#include<vector>
#include<string>
#include<bitset>
#include<queue>
#include<set>
#include<map>
using namespace std;

typedef long long ll;

inline int read()
{
	int x = 0, f = 1; char ch = getchar();
	while (ch<'0' || ch>'9') { if (ch == '-')f = -1; ch = getchar(); }
	while (ch <= '9'&&ch >= '0') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}
void print(ll x)
{
	if (x < 0)putchar('-'), x = -x; if (x >= 10)print(x / 10); putchar(x % 10 + '0');
}

const int N = 1001000;

int n, T, K;

struct SAM
{
	int trans[N][26], par[N], mx[N];
	int sz, root, suff;
	int size[N];

	SAM() { sz = root = suff = 1; }

	void insert(int x)
	{
		int p = suff, np = ++sz;
		mx[np] = mx[p] + 1; size[np] = 1;
		while (p && !trans[p][x])
			trans[p][x] = np, p = par[p];
		if (!p) par[np] = root;
		else
		{
			int q = trans[p][x];
			if (mx[q] == mx[p] + 1) par[np] = q;
			else
			{
				int nq = ++sz;
				mx[nq] = mx[p] + 1;
				memcpy(trans[nq], trans[q], sizeof(trans[q]));
				par[nq] = par[q];
				par[q] = par[np] = nq;
				while (p && trans[p][x] == q)
					trans[p][x] = nq, p = par[p];
			}
		}
		suff = np;
	}

	void build(char *s)
	{
		register int i;
		for (i = 1; i <= n; ++i) insert(s[i] - 'a');
	}

	int buc[N], sa[N], sum[N];

	void dfs(int u)
	{
		if (K <= size[u]) return;
		K -= size[u];
		for (int i = 0, v; i < 26; ++i)
			if (trans[u][i])
			{
				v = trans[u][i];
				if (K <= sum[v])
				{
					putchar(i + 'a');
					dfs(v); return;
				}
				K -= sum[v];
			}
	}

	void solve()
	{
		register int i, j, tmp;
		for (i = 1; i <= sz; ++i) buc[mx[i]]++;
		for (i = 1; i <= n; ++i) buc[i] += buc[i - 1];
		for (i = sz; i; i--) sa[buc[mx[i]]--] = i;
		for (i = sz; i; i--)
		{
			tmp = sa[i];
			T ? size[par[tmp]] += size[tmp] : size[tmp] = 1;
		}
		size[1] = 0;
		for (i = sz; i; i--)
		{
			tmp = sa[i];
			sum[tmp] = size[tmp];
			for (j = 0; j < 26; ++j) sum[tmp] += sum[trans[tmp][j]];
		}
		if (K > sum[1])puts("-1");
		else dfs(1);
	}
}sam;

char s[N >> 1];

int main()
{
	scanf("%s", s + 1);
	n = strlen(s + 1);
	T = read(); K = read();
	sam.build(s);
	sam.solve();
	return 0;
}
