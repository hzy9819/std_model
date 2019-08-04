/*
  欧几里得算法，求gcd(a, b);
*/
LL gcd(LL a, LL b) {
	if(a < b) swap(a, b);
	LL t;
	while(b)
		t = a % b, a = b, b = t;
	return a;
}

/*
  拓展欧几里得算法，求解方程：ax + by = gcd(a, b)
  返回值为gcd(a, b)
*/

LL exgcd(LL a, LL b, LL & x, LL & y) {
	if(b == 0) {
		x = 1, y = 0;
		return a;
	}
	else {
		LL d = exgcd(b, a % b, y, x);
		y -= a / b * x;
		return d;
	}
}

/*
  以下为更简单的写法，用于解同余方程ax = z (mod b)
*/

LL exgcd(LL a, LL b, LL z) { return a ? (exgcd(b % a, a, -z) * b + z) / a : z / b; }

/*
  同余方程应用：求乘法逆元
  以下为求a在模p下的逆元
*/

LL inv(LL a, LL p) { return exgcd(a, p, 1); }
