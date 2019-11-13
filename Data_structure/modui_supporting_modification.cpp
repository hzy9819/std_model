 
const int N=200100;
 
int block,bel[N>>1];
 
struct Query
{
	int t,l,r,pos;
	// t : the number of change queries before
	friend bool operator <(const Query &x,const Query &y)
	{return bel[x.t]==bel[y.t] ? (bel[x.l]==bel[y.l] ? x.r<y.r : bel[x.l]<bel[y.l]) : bel[x.t]<bel[y.t];}
	
}q[N>>1];
 
void modui()
{
	register int i, l(1), r(0), t(0);
	for (i = 1; i <= tot; ++i)
	{
		while (t < q[i].t)
			if (P[t + 1] <= r && P[t + 1] >= l)
				t++,
				    modify(Y[t], -1),
					modify(X[t], 1),
					a[P[t]] = X[t];
			else
				t++,
					a[P[t]] = X[t];
		while (t > q[i].t)
			if (P[t] <= r && P[t] >= l)
				modify(X[t] ,-1),
					modify(Y[t], 1),
					a[P[t]] = Y[t],
					t--;
			else
				a[P[t]] = Y[t], t--;
		while(r < q[i].r)
			r++, modify(a[r], 1);
		while(l > q[i].l)
			l--, modify(a[l], 1);
		while(r > q[i].r)
			modify(a[r], -1), r--;
		while(l < q[i].l)
			modify(a[l], -1), l++;
		ans[q[i].pos] = query();
	}
}
 
int main()
{
	int n=read(),Q=read();
	
	register int i(1),j,opt,now,tmp(1);
	
	while(i*i*i<n) i++;
	block=i*i;
	for(i=j=now=1;i<=n;++i,++j)
	{
		bel[i]=now;
		if(j==block)
			now++,j=0;
	}
	
	for(i=1;i<=n;++i) a[i]=read();
	memcpy(pre,a,sizeof(int)*(n+1));
	for(i=1,now=0;i<=Q;++i)
	{
		opt=read();
		switch(opt)
		{
			case 1:
				q[++tot].t=now;q[tot].pos=tot;
				q[tot].l=read();q[tot].r=read();
				break;
			case 2:
				P[++now]=read();
				break;
		}
	}
	sort(q+1,q+1+tot);
	
}
