#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 300010, m1 = 469762049, m2 = 998244353, m3 = 1004535809, g = 3;
const long long M = 1ll * m1 * m2;
int n, m, r[N], a[N], b[N], c[N], d[N], ans[3][N], mod;
int fast_pow(int a, int p, int mod) {
    int ans = 1;
    for (; p; p >>= 1, a = 1ll * a * a % mod)
        if (p & 1) ans = 1ll * ans * a % mod;
    return ans;
}
long long fast_mul(long long a, long long b, long long mod) {
    a %= mod, b %= mod;
    return ((a * b - (long long)((long long)((long double)a / mod * b + 1e-3) * mod)) % mod + mod) % mod;
}
void ntt(int n, int *a, int opt, int mod) {
    for (int i = 0; i < n; ++i)
        if (i < r[i]) swap(a[i], a[r[i]]);
    for (int k = 1; k < n; k <<= 1)
        for (int i = 0, wn = fast_pow(g, (mod - 1) / (k << 1), mod); i < n; i += (k << 1))
            for (int j = 0, w = 1; j < k; ++j, w = 1ll * w * wn % mod) {
                int x = a[i + j], y = 1ll * w * a[i + j + k] % mod;
                a[i + j]= (x + y) % mod, a[i + j + k] = (x - y + mod) % mod;
            }
    if (opt == -1) {
        a[0] = 1ll * a[0] * fast_pow(n, mod - 2, mod) % mod;
        for (int i = 1, inv = fast_pow(n, mod - 2, mod); i <= n / 2; ++i) {
            a[i] = 1ll * a[i] * inv % mod;
            if (i != n - i) a[n - i] = 1ll * a[n - i] * inv % mod;
            swap(a[i], a[n - i]);
        }
    }
}
main() {
    static int fn = 1, l = 0;
    scanf("%d%d%d", &n, &m, &mod);
    for (int i = 0; i <= n; ++i) scanf("%d", &a[i]);
    for (int i = 0; i <= m; ++i) scanf("%d", &b[i]);
    while (fn <= n + m) fn <<= 1, ++l;
    for (int i = 0; i < fn; ++i)
        r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
    copy(a, a + n + 1, c), copy(b, b + m + 1, d), ntt(fn, c, 1, m1), ntt(fn, d, 1, m1);
    for (int i = 0; i <= fn; ++i) ans[0][i] = 1ll * c[i] * d[i] % m1;
    memset(c, 0, sizeof c), memset(d, 0, sizeof d);
    copy(a, a + n + 1, c), copy(b, b + m + 1, d), ntt(fn, c, 1, m2), ntt(fn, d, 1, m2);
    for (int i = 0; i <= fn; ++i) ans[1][i] = 1ll * c[i] * d[i] % m2;
    memset(c, 0, sizeof c), memset(d, 0, sizeof d);
    copy(a, a + n + 1, c), copy(b, b + m + 1, d), ntt(fn, c, 1, m3), ntt(fn, d, 1, m3);
    for (int i = 0; i <= fn; ++i) ans[2][i] = 1ll * c[i] * d[i] % m3;
    ntt(fn, ans[0], -1, m1), ntt(fn, ans[1], -1, m2), ntt(fn, ans[2], -1, m3);
    for (int i = 0; i <= n + m; ++i) {
        long long A = (fast_mul(1ll * ans[0][i] * m2 % M, fast_pow(m2 % m1, m1 - 2, m1), M) +
                       fast_mul(1ll * ans[1][i] * m1 % M, fast_pow(m1 % m2, m2 - 2, m2), M)) % M;
        long long k = ((ans[2][i] - A) % m3 + m3) % m3 * fast_pow(M % m3, m3 - 2, m3) % m3;
        printf("%d ", ((k % mod) * (M % mod) % mod + A % mod) % mod);
    }
}
