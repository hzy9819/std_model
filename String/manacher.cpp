//得到每个字符为中心、结尾的最长回文串长度

const int N = 300100;

char s[N], ch[N];
int p[N], f[N];

int main()
{
	scanf("%s", ch + 1);
	register int i, j, maxn, d, ans, n;
	n = strlen(ch + 1);
	for (i = 1; i <= n; ++i)
		s[i << 1] = ch[i], s[(i << 1) - 1] = '#'; 
	s[(n << 1) + 1] = '#'; s[0] = '$';
	n <<= 1; 
	d = maxn = ans = 0;
	for (i = 1; i <= n; ++i)
	{
		if (i < maxn)
			p[i] = min(p[(d << 1) - i], maxn - i); 
		else 
			p[i] = 1;
		while (!(s[i - p[i]] ^ s[i + p[i]]))
			p[i]++;
		if (i + p[i] - 1 > maxn)
		{
			for (j = maxn + 1; j <= i + p[i] - 1; ++j)
				f[j] = j - i + 1;
			maxn = i + p[i] - 1;
			d = i;
		}
		ans = max(ans, f[i - p[i]] + p[i] - 1);
	}
	print(ans);
	puts("");
	return 0;
}
