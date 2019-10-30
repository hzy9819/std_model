
namespace SAM
{
	int trans[N << 1][26], par[N << 1], mx[N << 1];
	int sz(1), root(1), suff(1);
	bool book[N << 1];
	int pos[N << 1];

	void insert(int x, int now)
	{
		int p = suff, np = ++sz;
		mx[np] = mx[p] + 1;
		pos[np] = now, book[np] = 1;
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
				mx[nq] = mx[p] + 1, pos[nq] = pos[q];
				memcpy(trans[nq], trans[q], sizeof(trans[q]));
				par[nq] = par[q];
				par[q] = par[np] = nq;
				while (p && trans[p][x] == q)
					trans[p][x] = nq, p = par[p];
			}
		}
		suff = np;
	}

	void build()
	{
		register int i;
		for (i = n; i; --i)
			insert(str[i] - 'a', i);
	}
}

namespace SA
{
	int trans[N << 1][26];

	int cnt, sa[N], rk[N], height[N];

	void dfs(int u)
	{
		if (!u) return;
		if (SAM::book[u])
			sa[rk[SAM::pos[u]] = ++cnt] = SAM::pos[u];
		for (int i = 0; i < 26; ++i)
			dfs(trans[u][i]);
	}

	void get_sa()
	{
		register int i;
		for (i = 2; i <= SAM::sz; ++i)
			trans[SAM::par[i]][str[SAM::pos[i] + SAM::mx[SAM::par[i]]] - 'a'] = i;
		dfs(SAM::root);
	}

	void get_height()
	{
		register int i, j, k(0);
		for (i = 1; i <= n; ++i)
		{
			j = rk[i] - 1;
			while (str[i + k] == str[sa[j] + k]) k++;
			height[rk[i]] = k;
			if (k) k--;
		}
	}
}

void get_sa(char str[])
{
	n = strlen(str + 1);
	SAM::build();
	SA::get_sa();
	SA::get_height();
}
