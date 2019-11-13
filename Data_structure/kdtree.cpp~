#include <bits/stdc++.h>
#define LL long long
#define db double
#define ls(o) ((o) << 1)
#define rs(o) (((o) << 1) + 1)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 100010;
const int LEN = 45;

int read() {
	int f = 0, w = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

inline void Merge(LL * res, LL * src1, LL * src2) {
		int p1 = 0 , p2 = 0;
		for(int i = 0; i < LEN; ) {
			if(!src1[p1] && !src2[p2])
				break;
			if(!src1[p1]) {
				while(src2[p2] && i < LEN) res[i++] = src2[p2++];
				break;
			}
			if(!src2[p2]) {
				while(src1[p1] && i < LEN) res[i++] = src1[p1++];
				break;
			}
			res[i++] = (src1[p1] > src2[p2] ? src1[p1++] : src2[p2++]);
		}
}

struct zkw_Seg {
	int n, M;
	LL tr[N << 2][LEN];
	LL res[LEN], tmp[LEN];
	
	void Update(int x) {
		Merge(tr[x], tr[ls(x)], tr[rs(x)]);
	}
	
	void Init(int _n, LL * src) {
		n = _n;
		for(M = 1; M < n; M <<= 1) ;
		memset(tr, 0, 8 * (M + N + 1) * LEN);
		for(int i = M + 1; i <= M + N; ++i)
			tr[i][0] = src[i - M];
		for(int i = M - 1; i; --i)
			Update(i);
	}
	void Query(int l, int r) {
		memset(res, 0, sizeof res);
		for(l = l + M - 1, r = r + M + 1; l ^ r ^ 1; l >>= 1, r >>= 1) {
			if(~l & 1) {
				memcpy(tmp, res, sizeof(res));
				memset(res, 0, sizeof(res));
				Merge(res, tmp, tr[l ^ 1]);
			}
			if(r & 1) {
				memcpy(tmp, res, sizeof(res));
				memset(res, 0, sizeof(res));
				Merge(res, tmp, tr[r ^ 1]);
			}
		}
	}
}Tree;

int n, q;
LL a[N];

int main() {
	Hzy("11");
	while(~scanf("%d%d", &n, &q)) {
		for(int i = 1; i <= n; ++i)
			a[i] = read();
		Tree.Init(n, a);

		int l, r;
		for(int i = 1; i <= q; ++i) {
			l = read(), r = read();
			Tree.Query(l, r);
			LL a, b, c;
			for(int j = 0; j < LEN - 2; ++j) {
				a = Tree.res[j], b = Tree.res[j + 1], c = Tree.res[j + 2];
				if(!a || !b || !c) {
					printf("-1\n");
					break;
				}
				if(a < b + c) {
					printf("%lld\n", a + b + c);
					break;
				}
			}
		}
	}
	return 0;
}
