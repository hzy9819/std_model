
const int N = 1001000, bas_1 = 233, bas_2 = 2333, mod_1 = int(1e9+7), mod_2 = 19260817;
 
int n;
 
char s[N];
 
int pw_1[N], pw_2[N];
int hs_1[N], hs_2[N];
 
inline int calc_1(int x, int y)
{
	return (hs_1[y] - 1ll * hs_1[x - 1] * pw_1[y - x + 1] % mod_1 + mod_1) % mod_1;
}
 
inline int calc_2(int x, int y)
{
	return (hs_2[y] - 1ll * hs_2[x - 1] * pw_2[y - x + 1] % mod_2 + mod_2) % mod_2;
}
 
inline bool check_1(int x, int y, int a, int b)
{
	return calc_1(x, y) == calc_1(a, b);
}
 
inline bool check_2(int x, int y, int a, int b)
{
	return calc_2(x, y) == calc_2(a, b);
}

//检查两串是否相同
inline bool check(int x, int y, int a, int b)
{
	return check_1(x, y, a, b) && check_2(x, y, a, b);
}

//得到哈希值
int get_hash(int n, char s[])
{
	int i;
	pw_1[0] = pw_2[0] = 1;
	for (i = 1; i <= n; ++i)
		pw_1[i] = 1ll * pw_1[i - 1] * bas_1 % mod_1,
		pw_2[i] = 1ll * pw_2[i - 1] * bas_2 % mod_2,
		hs_1[i] = (1ll * hs_1[i - 1] * bas_1 + s[i]) % mod_1,
		hs_2[i] = (1ll * hs_2[i - 1] * bas_2 + s[i]) % mod_2;
}
