//最小表示法

const int N = 301000;

int minimum_representation()
{
	int n = read();
	static int a[N];
	for (int i = 1; i <= n; i++)
		a[i] = read();
	a[0] = a[n];
	int i = 1, j = 2, k = 0;
	while (i <= n && j <= n && k <= n)
	{
		int t = a[(i + k) % n] - a[(j + k) % n];
		if (!t)
			k++;
		else
		{
			if (t > 0)i += k + 1;
			else
				j += k + 1;
			if (i == j)
				i++;
			k = 0;
		}
	}
	int t = min(i, j);
	for (int i = 0; i < n - 1; i++)
	{
		print(a[(i + t) % n]);
		putchar(' ');
	}
	print(a[t - 1]);
	puts("");
	return 0;
}
/*
10
10 9 8 7 6 5 4 3 2 1
1 10 9 8 7 6 5 4 3 2
*/
