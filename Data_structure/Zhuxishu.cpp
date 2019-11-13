#define nn 100002

struct node{
	node* ch[2];
    node() {ch[0]=ch[1]=NULL; d=0;}
	void update()
	{
		if(ch[0]) d+=ch[0]->d;
		if(ch[1]) d+=ch[1]->d;
	}
	int d;
};node* f[nn],put[nn*9];
int n,m,k,sum,siz,li,ri;
int co[nn],a[nn];
int ps=0;

void set0(node* &p,int l,int r)
{
	p=&put[++ps];
	*p=node();
	int mid=(l+r)/2;
	if(l+1==r) return;
	else set0(p->ch[0],l,mid),set0(p->ch[1],mid,r);
}

void build(node* &pr,node* &p,int l,int r,int d)
{
	int mid=(l+r)/2;
	p=&put[++ps];
	*p=node();
	if(l+1==r)
	{
		*p=*pr; p->d++; return;
	}
	if(d>=co[mid])
	{
		build(pr->ch[1],p->ch[1],mid,r,d);
		p->ch[0]=pr->ch[0];
		p->update();
	}
	else
	{
		build(pr->ch[0],p->ch[0],l,mid,d);
		p->ch[1]=pr->ch[1];
		p->update();
	}
}

void find(node* p,node* q,int l,int r,int k)
{
	int mid=(l+r)/2;
	if(l+1==r)
	{
		sum=co[l]; return;
	}
	int ls=0;
	if(q->ch[0]) ls+=q->ch[0]->d;
	if(p->ch[0]) ls-=p->ch[0]->d;
	if(ls>=k) find(p->ch[0],q->ch[0],l,mid,k);
	else find(p->ch[1],q->ch[1],mid,r,k-ls);
}

void init()
{
	for(int i=1;i<=n;++i) scanf("%d",a+i),co[i]=a[i];
	sort(co+1,co+n+1);
	siz=unique(co+1,co+n+1)-(co+1); siz++;
	set0(f[0],1,siz);
	for(int i=1;i<=n;++i)
	{
		build(f[i-1],f[i],1,siz,a[i]);
	}
}

void work()
{
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d%d\n",&li,&ri,&k);
		sum=0;
		find(f[li-1],f[ri],1,siz,k);
		printf("%d\n",sum);
	}	
}

