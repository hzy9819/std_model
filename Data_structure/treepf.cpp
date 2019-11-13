struct node{
	int n;
	node* next;
	node() {n=0; next=NULL; }
};node* a[nn];

void fdfs(int u,int fa)
{
	pr[u][0]=fa; fr[u]=fa;
	if(fa!=-1) dep[u]=dep[fa]+1;
	node* p=a[u];
	int k=u,dmx=0,ds=0;
	d[u]=1;
	while(p!=NULL)
	{
		k=p->n;
		if(k!=fa)
		{
			fdfs(k,u); d[u]+=d[k];
			if(dmx<d[k]) dmx=d[k],ds=k;
		}p=p->next;
	}
	suc[u]=ds;
}

void sdfs(int u,int pm)
{
	num[u]=++ni; b[ni]=w[u]; top[u]=pm;
	if(suc[u]==0) return;
	sdfs(suc[u],pm);
	node* p=a[u];
	int k=0;
	while(p!=NULL)
	{
		k=p->n;
		if(k!=fr[u]&&k!=suc[u]) sdfs(k,k);
		p=p->next;
	}
}
