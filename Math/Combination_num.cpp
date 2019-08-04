/*
  分了不同的情况求解组合数取模，注意模数要求是素数，非素数考虑递推
  部分函数引用自Exgcd.cpp
*/

/*
  case: n, m = 10^5
  预处理 n! 和 m!和他们的乘法逆元
  p: 模数
  fac：阶乘
  inv：阶乘的逆
*/
void Init() {
	for(int i = 2; i < N; ++i) {
		fac[i] = fac[i - 1] * i % p;
		f[i] = (p - p / i) * f[p % i] % p;
		inv[i] = inv[i - 1] * f[i] % p;
	}
}

LL C(LL n, LL m, LL p) {
	if(m > n) return 0;
	return fac[a] * inv[b] % p * inv[a - b] % p;
}

/*
  case: n = 10^9, m = 10^5
  暴力计算n!/(n-m)! 和 m! 和逆元
  qpow: 快速幂
*/

LL qpow(LL a, LL b, LL p) {
	LL ans = 1;
	while(b) {
		if(b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}

LL C(LL n, LL m, LL p) {
	if(m > n) return 0;
	LL ans = 1;
	for(int i = 1; i <= m; ++i)
		ans = ans * (n - i + 1) % p * qpow(i, p - 2, p) % p;
	return ans;
}

/*
  case: n, m = 10^18, p = 10^5
  lucas定理：C(n, m) = for(i = 0; i <= k; ++i) ans = ans * C(n[i], m[i])
  其中 m = m[k] * p^k + m[k - 1] * p^(k-1) ...
  n同理

  对于C(n[i], m[i])的求解应用上面提及的算法即可
*/

LL lucas(LL n, LL m, LL p) {
	if(!m) return 1;
	return C(n % p, m % p, p) * lucas(n / p, m / p, p) % p;
}
