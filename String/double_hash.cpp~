
//求S的第i个位置向后能匹配T的最长长度
//答案为z[i]

void exkmp(char S[], char T[])
{
	int i, j, maxn, d, len;
	T[m + 1] = '#';
	z[1] = m;
	for(i = m + 2; i <= (len = m + n + 1); ++i)
		T[i] = S[i - m - 1];
	
	for (i = 2, maxn = 0, d = 0; i <= len; ++i)
	{
		z[i] = i > maxn ? 0 : min(maxn - i + 1, z[i - d + 1]);
		if (i + z[i] > maxn)
			while (T[z[i] + 1] == T[i + z[i]])
				++z[i];
		if(i + z[i] -1 > maxn)
			d = i, maxn = i + z[i] - 1;
	}
	
	for (i = 1; i <= n; ++i)
		z[i] = z[i + m + 1];
}
