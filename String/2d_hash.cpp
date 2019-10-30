typedef unsigned long long ui;

const int N = 1010, bas1 = 131, bas2 = 193, mod = 99999997;

int n, m, a, b, matrix[N][N];

ui mi1[N], mi2[N], h[N][N], ha[N][N];

bool book[mod + 10]; char s[N];

int main()
{
	n = read(); m = read(); a = read(); b = read();
	register int i, j, Q; ui tmp;
	for (i = 1; i <= n; ++i)
	{
		scanf("%s", s + 1);
		for (j = 1; j <= m; ++j)
			matrix[i][j] = (s[j] == '1');
	}
	mi1[0] = mi2[0] = 1;
	for (i = 1; i <= a; ++i)
		mi1[i] = (mi1[i - 1] << 7) + mi1[i - 1] + (mi1[i - 1] << 1);
	for (i = 1; i <= b; ++i)
		mi2[i] = (mi2[i - 1] << 7) + mi2[i - 1] + (mi2[i - 1] << 6);
	for (i = 1; i <= n; ++i)
		for (j = 1; j <= m; ++j)
		h[i][j] = ((h[i - 1][j] << 7) + h[i - 1][j] + (h[i - 1][j] << 1) + matrix[i][j]);
	for (i = 1; i <= n; ++i)
		for (j = 1; j <= m; ++j)
		h[i][j] += ((h[i][j - 1] << 7) + h[i][j - 1] + (h[i][j - 1] << 6));

	for (i = a; i <= n; ++i)
		for (j = b; j <= m; ++j)
		{
			tmp = h[i][j];
			tmp -= h[i - a][j] * mi1[a]; tmp -= h[i][j - b] * mi2[b];
			tmp += h[i - a][j - b] * mi1[a] * mi2[b];
			tmp = tmp % mod;
			book[tmp%mod] = 1;
		}

	Q = read();
	while (Q--)
	{
		for (i = 1; i <= a; ++i)
		{
			scanf("%s", s + 1);
			for (j = 1; j <= b; ++j)
				matrix[i][j] = (s[j] == '1');
		}
		memset(ha, 0, sizeof(ha));
		for (i = 1; i <= a; ++i)
			for (j = 1; j <= b; ++j)
				ha[i][j] = ((ha[i - 1][j] << 7) + ha[i - 1][j] + (ha[i - 1][j] << 1) + matrix[i][j]);
		for (i = 1; i <= a; ++i)
			for (j = 1; j <= b; ++j)
				ha[i][j] += ((ha[i][j - 1] << 7) + ha[i][j - 1] + (ha[i][j - 1] << 6));
		
		if (book[ha[a][b] % mod])
			puts("1");
		else 
			puts("0");
	}
	return 0;
}
