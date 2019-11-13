//lca for beizeng
int lca(int a,int b)
{
	int dep=0;
	if(d[a]<d[b]) swap(a,b);
	while((1<<dep)<=d[a]) dep++;
	dep--;
	for(int i=dep;i>=0;i--)
		if(d[a]-(1<<i)>=d[b]) a=p[a][i];
	if(a==b) return a;

	for(int i=dep;i>=0;i--)
	{
		if(p[a][i]!=-1&&p[a][i]!=p[b][i])
		{
			a=p[a][i];
			b=p[b][i];
		}
	}

	return p[a][0];
}

//lca for treepf
void find(int x,int y)
{
	for(;top[x]!=top[y];)
	{
		if(d[top[x]]>d[top[y]]) x=fa[top[x]];
		else y=fa[top[y]];
	}
	return d[x]<d[y]?x:y;
}
