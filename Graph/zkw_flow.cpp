#define M(x) memset(x,0,sizeof(x))
#define Mp(x) memset(x,-0x7f,sizeof(x))
#define LL long long
#define INF ((int)1e+9)
#define maxcost ((LL)1e+18)
#define nn 1002
#define edn 600002
#define nl NULL

struct ZKW{
	struct node{
		int n,f,id;
		LL w;
		node* next;
		node() {n=f=id=w=0; next=nl; }
	};node* a[nn];
	int pt=0;
	node put[edn];
    LL flow,cost;
    LL dis[nn],b[nn];
	int n,ss,tt;
	void add_(int x,int y,int f,LL w)
	{
		node* p=&put[pt++]; p->n=y; p->f=f; p->id=pt-1; p->w=w;
		if(a[x]!=nl) p->next=a[x]; a[x]=p;
	}
	void add(int x,int y,int f,LL w)
	{
		add_(x,y,f,w);
		add_(y,x,0,-w);
	}

	queue<int> Q;
	bool spfa()
	{
		int u=0;
		memset(dis,0x7f,sizeof(dis));
		memset(b,0,sizeof(b));
		while(!Q.empty()) Q.pop();
		Q.push(ss);
		dis[ss]=0;
		while(!Q.empty())
		{
			u=Q.front(); Q.pop();
			b[u]=0;
			for(node* p=a[u];p!=nl;p=p->next)
			{
				if(p->f>0&&dis[p->n]-(dis[u]+p->w)>0)
				{
					dis[p->n]=dis[u]+p->w;
					if(!b[p->n])
					{
						Q.push(p->n),b[p->n]=1;
					}
				}
			}
		}
		if(dis[tt]>INF) return 1;else return 0;
	}
	
    int aug(int x,int maxf){
        b[x]=1;
        if(x==tt) return cost+=(dis[tt]-dis[ss])*maxf,flow+=maxf,maxf;
        int y,tmp,sum=0;
		for(node* p=a[x];p!=nl;p=p->next)
			if(p->f>0&&!b[y=p->n]&&dis[x]+p->w-dis[y]==0&&(tmp=aug(y,min(maxf,p->f))))
			{
				p->f-=tmp;
				put[p->id^1].f+=tmp;
				sum+=tmp;
				maxf-=tmp;
			}
        return sum;
    }

    bool mdf(){
        if(b[tt]) return 1;
		int y;
		LL z=maxcost;
		for(int i=0;i<=tt;++i) //for all the nodes
		{
			if(!b[i]) continue;
			for(node* p=a[i];p!=nl;p=p->next)
				if(p->f>0&&!b[y=p->n]) z=min(z,dis[i]+p->w-dis[y]);
		}
		if(z>=maxcost) return 0;
        for(int i=0;i<=tt;i++) if(b[i]) dis[i]-=z;
        return 1;
    } 

    LL solve(int _n,int _ss,int _tt){
		n=_n,ss=_ss,tt=_tt;
        flow=0, cost=0;
		memset(dis,0,sizeof(dis));
		spfa(); //needed for graphs with minus weight edges
        do
			memset(b,0,sizeof(b)),aug(ss,INF);
		while(mdf());
		return cost;
    }
}zkw;

usage:
zkw.add(a,b,f,w);
zkw.solve(n,ss,tt);
