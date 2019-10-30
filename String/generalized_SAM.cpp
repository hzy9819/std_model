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

const int N = 200100;

int n, K;

ll Ans[N];

string ss[N >> 1];

struct SAM
{
	int trans[N][26], mx[N], par[N];
	int sz, root, suff;

	SAM() { sz = root = suff = 1; }

	void insert(int x)
	{
		int p = suff, np = ++sz;
		mx[np] = mx[p] + 1;

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
				vis[nq] = vis[q];
				num[nq] = num[q];
				memcpy(trans[nq], trans[q], sizeof(trans[q]));
				par[nq] = par[q];
				par[q] = par[np] = nq;
				while (p && trans[p][x] == q)
					trans[p][x] = nq, p = par[p];
			}
		}
		suff = np;
	}

	int st[N], top;
	int vis[N], num[N], col[N];

	void pushup(int x)
	{
		while (top)
		{
			int tmp(st[top]);
			col[tmp] = x;
			while (tmp && vis[tmp] != x)
				num[tmp]++,
				vis[tmp] = x,
				tmp = par[tmp];
			top--;
		}
	}

	void build(char *s, int x)
	{
		suff = root; top = 0;
		register int i;
		for (i = 1; s[i]; ++i)
			insert(s[i] - 'a'), st[++top] = suff;
		pushup(x);
	}

	int buc[N], sa[N];
	ll sum[N];

	void get_ans(int x)
	{
		if (x == 1 || vis[x])
			return;
		vis[x] = 1;
		get_ans(par[x]);
		sum[x] += sum[par[x]];
	}

	void solve()
	{
		register int i, tmp;
		for (i = 1; i <= sz; ++i)
			buc[mx[i]]++;
		for (i = 1; i <= sz; ++i)
			buc[i] += buc[i - 1];
		for (i = sz; i; i--)
			sa[buc[mx[i]]--] = i;

		for (i = 1; i <= sz; ++i)
			sum[i] = (num[i] >= K)*(mx[i] - mx[par[i]]);

		memset(vis, 0, sizeof(vis));
		for (i = 1; i <= sz; ++i)
			get_ans(i);
		for (i = 1; i <= sz; ++i)
			Ans[col[i]] += sum[i];

	}

}sam;

char s[N >> 1];

int main()
{
	n = read(); K = read();
	register int i;
	for (i = 1; i <= n; ++i)
		scanf("%s", s + 1),
		ss[i] = string(s + 1),
		sam.build(s, i);
	sam.solve();
	for (i = 1; i <= n; ++i)
		print(Ans[i]), putchar(' ');
	return 0;
}
