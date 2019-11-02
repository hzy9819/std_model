#define ll long long
#define oo ((LL)1e+18)
#define M(x) memset(x,0,sizeof(x))
#define Mp(x) memset(x,-0x7f,sizeof(x))

struct KM{
	#define maxn 1002
	const ll inf = 1ll << 60;
	ll G[maxn][maxn], hl[maxn], hr[maxn], dt[maxn];
	int fl[maxn], fr[maxn], vl[maxn], vr[maxn], pre[maxn], q[maxn], ql, qr, n;
	void init(int nl, int nr){
		n = max(nl, nr);
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j) G[i][j] = 0;
	}
	void add(int u, int v, ll w){
		G[u][v] = max(G[u][v], w);
	}
	int check(int i){
		if(vl[i] = 1, fl[i] != -1) return vr[q[qr++] = fl[i]] = 1;
		while(i != -1) swap(i, fr[fl[i] = pre[i]]);
		return 0;
	}
	void bfs(int s){
		for(int i = 1; i <= n; ++i) vl[i] = vr[i] = 0, dt[i] = inf;
		for(vr[q[ql = 0] = s] = qr = 1;;){
			for(ll d; ql < qr;){
				for(int i = 1, j = q[ql++]; i <= n; ++i){
					if(!vl[i] && dt[i] >= (d = hl[i] + hr[j] - G[i][j])){
						if(pre[i] = j, d) dt[i] = d;
						else if(!check(i)) return;
					}
				}
			}
			ll d = inf;
			for(int i = 1; i <= n; ++i){
				if(!vl[i] && d > dt[i]) d = dt[i];
			}
			for(int i = 1; i <= n; ++i){
				if(vl[i]) hl[i] += d;
				else dt[i] -= d;
				if(vr[i]) hr[i] -= d;
			}
			for(int i = 1; i <= n; ++i){
				if(!vl[i] && !dt[i] && !check(i)) return;
			}
		}
	}
	ll solve(){
		for(int i = 1; i <= n; ++i) fl[i] = fr[i] = -1, hr[i] = 0;
		for(int i = 1; i <= n; ++i) hl[i] = *max_element(G[i] + 1, G[i] + 1 + n);
		for(int i = 1; i <= n; ++i) bfs(i);
		ll ret = 0;
		for(int i = 1; i <= n; ++i) if(G[i][fl[i]]) ret += G[i][fl[i]]; else fl[i] = 0;
		return ret;
	}
} km;

usage:
	km.init(nl,nr); //left number nl, right number nr
	km.add(x,y,w); //from left to right
	km.solve();
   
