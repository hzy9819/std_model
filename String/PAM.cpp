namespace PAM
{
	int nt[N][26], fail[N], len[N], cnt[N], num[N];
	int suff, sz;

	void initial()
	{
		len[1] = -1;
		len[2] = 0;
		fail[1] = fail[2] = 1;
		suff = sz = 2;
	}

	int insert(char *s, int pos)
	{
		int k = s[pos] - 'a', cur = suff;
		while (s[pos] != s[pos - len[cur] - 1])
			cur = fail[cur];
		if (!nt[cur][k])
		{
			nt[cur][k] = suff = ++sz;
			cnt[sz] = 1;
			len[sz] = len[cur] + 2;
			if (len[sz] == 1)
			{
				suff = sz;
				num[sz] = 1;
				fail[sz] = 2;
				return num[suff];
			}
			cur = fail[cur];
			while (s[pos] != s[pos - len[cur] - 1])
				cur = fail[cur];
			fail[sz] = nt[cur][k];
			num[sz] = num[fail[sz]] + 1;
		}
		else
			cnt[suff = nt[cur][k]]++;

		return num[suff];
	}

}
