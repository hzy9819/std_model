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
void print(int x)
{
	if (x < 0)putchar('-'), x = -x; if (x >= 10)print(x / 10); putchar(x % 10 + '0');
}

const int N = 1200100, bas = 131;

struct LCT
{
	int ch[N][2], fa[N], V[N], tag[N];

	inline void pushdown(int x)
	{
		if (tag[x])
		{
			tag[ch[x][0]] += tag[x]; tag[ch[x][1]] += tag[x];
			V[ch[x][0]] += tag[x]; V[ch[x][1]] += tag[x];
			tag[x] = 0;
		}
	}

	inline bool isroot(int x)
	{
		return ch[fa[x]][0] != x && ch[fa[x]][1] != x;
	}

	void getdown(int x)
	{
		if (!isroot(x)) getdown(fa[x]); pushdown(x);
	}

	void rotate(int x)
	{
		int y = fa[x], z = fa[y], l, r;
		l = (ch[y][1] == x); r = l ^ 1;
		if (!isroot(y)) ch[z][ch[z][1] == y] = x;
		fa[x] = z; fa[y] = x; fa[ch[x][r]] = y;
		ch[y][l] = ch[x][r]; ch[x][r] = y;
	}

	void splay(int x)
	{
		getdown(x);
		int y, z;
		while (!isroot(x))
		{
			y = fa[x], z = fa[y];
			if (!isroot(y))
			{
				if ((ch[z][0] == y) ^ (ch[y][0] == x)) rotate(x);
				else rotate(y);
			}
			rotate(x);
		}
	}

	void access(int x)
	{
		int t = 0; while (x) { splay(x); ch[x][1] = t; t = x; x = fa[x]; }
	}

	void rever(int x)
	{
		access(x); splay(x);
	}

	void link(int u, int v)
	{
		fa[v] = u; rever(u); V[u] += V[v]; tag[u] += V[v];
	}

	void cut(int v)
	{
		rever(v); V[ch[v][0]] -= V[v]; tag[ch[v][0]] -= V[v]; fa[ch[v][0]] = 0; ch[v][0] = 0;
	}

	int query(int x)
	{
		splay(x); return V[x];
	}
};

struct SAM
{
	LCT lct;
	int trans[N][26], par[N], mx[N];
	int sz, root, suff;

	SAM() { sz = root = suff = 1; }

	void insert(int x)
	{
		int p = suff, np = ++sz;
		lct.V[np] = 1;
		mx[np] = mx[p] + 1;
		while (p && !trans[p][x])
			trans[p][x] = np, p = par[p];
		if (!p) par[np] = root, lct.link(root, np);
		else
		{
			int q = trans[p][x];
			if (mx[q] == mx[p] + 1) par[np] = q, lct.link(q, np);
			else
			{
				int nq = ++sz;
				mx[nq] = mx[p] + 1;
				memcpy(trans[nq], trans[q], sizeof(trans[q]));
				lct.cut(q);
				lct.link(par[q], nq);
				lct.link(nq, q); lct.link(nq, np);
				par[nq] = par[q];
				par[q] = par[np] = nq;
				while (p && trans[p][x] == q)
					trans[p][x] = nq, p = par[p];
			}
		}
		suff = np;
	}

	void add(char *s)
	{
		for (int i = 0; s[i]; ++i) insert(s[i] - 'A');
	}

	int getans(char *s)
	{
		int now = root;
		for (int i = 0; s[i]; ++i)
			if (!(now = trans[now][s[i] - 'A'])) return 0;
		return lct.query(now);
	}
}sam;

inline void decode(char *s, int mask)
{
	int len = strlen(s);
	for (int i = 0; i < len; ++i)
	{
		mask = (mask*bas + i) % len;
		swap(s[mask], s[i]);
	}
}

char opt[10], s[N >> 1];

int main()
{
	int Q = read();
	scanf("%s", s);
	sam.add(s);
	int mask = 0, ans;
	while (Q--)
	{
		scanf("%s%s", opt, s);
		decode(s, mask);
		switch (opt[0])
		{
		case 'A':
			sam.add(s);
			break;
		case 'Q':
			ans = sam.getans(s);
			print(ans); putchar('\n');
			mask ^= ans;
			break;
		}
	}
	return 0;
}
