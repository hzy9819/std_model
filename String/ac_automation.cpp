#include<cmath>
#include<ctime>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<complex>
#include<iostream>
#include<algorithm>
#include<iomanip>
#include<vector>
#include<string>
#include<queue>
#include<set>
#include<map>
using namespace std;
inline int read()
{
	int x = 0, f = 1; char ch = getchar();
	while (ch<'0' || ch>'9') { if (ch == '-')f = -1; ch = getchar(); }
	while (ch <= '9'&&ch >= '0') { x = (x << 3) + (x << 1) + ch - '0'; ch = getchar(); }
	return x * f;
}

const int N = 1000100;

int n, top = 0, sz = 1, tr[N][26], fail[N], q[N], f[N], danger[N];

char s[N], aim[N], a[N];

bool mark[N];

void insert()
{
	int len = strlen(a);
	int now = 1, k;
	for (int i = 0; i < len; i++)
	{
		k = a[i] - 'a';
		if (!tr[now][k])
			tr[now][k] = ++sz;
		now = tr[now][k];
	}
	danger[now]++;
}

void ac_automation()
{
	int head = 0, tail = 1, k, now; q[0] = 1;
	while (head < tail)
	{
		now = q[head++];
		for (int i = 0; i < 26; i++)
		{
			if (tr[now][i])
			{
				k = fail[now];//while(!tr[k][i])k=fail[k];  
				fail[tr[now][i]] = tr[k][i];
				q[tail++] = tr[now][i];
			}
			else
			{
				tr[now][i] = tr[fail[now]][i];
			}
		}
	}
}

void solve()
{
	n = strlen(aim); int k, now = 1, ans = 0; f[0] = 1;
	for (int i = 0; i < n; i++)
	{
		mark[now] = 1;
		k = aim[i] - 'a';
		now = tr[now][k];
		if (!mark[now])
			for (int j = now; j; j = fail[j])
			{
				ans += danger[j]; danger[j] = 0;
			}
	}
	printf("%d\n", ans);
}

int main()
{
	scanf("%s", aim);
	for (int i = 0; i < 26; i++)
		tr[0][i] = 1; fail[1] = 0;
	n = read();
	while (n--)
		scanf("%s", a), insert();
	ac_automation();
	solve();
	return 0;
}
/*
idorememberyourbirthday
3
birthday
remember
timeless
2
*/
