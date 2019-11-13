
const int N=100100;
 
int n,Q;
 
struct point
{
	int val,pos;
	
	friend bool operator <(const point &x,const point &y)
	{return x.val<y.val;}
}p[N];
 
int block,bel[N];
 
struct query
{
	int l,r,pos;
	
	friend bool operator <(const query &x,const query &y)
	{return bel[x.l]==bel[y.l] ? x.r<y.r : bel[x.l]<bel[y.l];}
}q[N];

void solve()
{
	register int i,j,l,r;
	ll mx(0);
	for(i=1;i<=Q;++i)
	{
		if(bel[q[i].l]!=bel[q[i-1].l])
		{
			mx=0,
			r=bel[q[i].l]*block;
			memset(cnt,0,sizeof(cnt));
		}
		if(bel[q[i].l]==bel[q[i].r])
		{
			for(j=q[i].l;j<=q[i].r;++j)
				cnt[a[j]]++, mx = max(mx,1ll*cnt[a[j]]*V[a[j]]);
			for(j=q[i].l;j<=q[i].r;++j)
				cnt[a[j]]--;
			ans[q[i].pos]=mx;mx=0;
			continue;
		}
		while(r<q[i].r)
			r++,cnt[a[r]]++,mx=max(mx,1ll*cnt[a[r]]*V[a[r]]);
		
		ll pre=mx;
		l=bel[q[i].l]*block;
		while(l>=q[i].l)
			cnt[a[l]]++,mx=max(mx,1ll*cnt[a[l]]*V[a[l]]),l--;
		while(l<bel[q[i].l]*block)
			l++,cnt[a[l]]--;
		
		ans[q[i].pos]=mx;
		mx=pre;
	}
}
 
int main()
{
	n=read(),Q=read();
	block=floor(sqrt(n));
	register int i,j,tot(1);
	for(i=1;i<=n;++i)
		p[i].val=read(),p[i].pos=i;
	
	sort(p+1,p+1+n);
	V[1]=p[1].val,a[p[1].pos]=1;
	for(i=2;i<=n;++i)
	{
		if(p[i].val!=p[i-1].val)
			tot++,V[tot]=p[i].val;
		a[p[i].pos]=tot;
	}
	for(i=j=tot=1;i<=n;++i,++j)
	{
		bel[i]=tot;
		if(j==block) tot++,j=0;
	}
	
	for(i=1;i<=Q;++i)
		q[i].l=read(),q[i].r=read(),q[i].pos=i;
	sort(q+1,q+Q+1);
	
}
