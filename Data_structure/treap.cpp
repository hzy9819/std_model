struct treap{
	void push(int p) {}

	int merge(int p,int q)
	{
		if(!p||!q) return p|q;
		if(f[p]<f[q])
		{
			r[p]=merge(r[p],q),push(p);
			return p;
		}
		else
		{
			l[q]=merge(p,l[q]),push(q);
			return q;
		}
	}

	struct data{
		int l,r;
		data(int _l=0,int _r=0) {l=_l,r=_r; }
	};

	data split(int p,int val)
	{
		if(!p) return data(0,0);
		if(d[p]>=val)
		{
			data x=split(l[p],val);
			l[p]=x.r;
			return data(x.l,p);
		}
		else
		{
			data x=split(r[p],val);
			r[p]=x.l;
			return data(p,x.r);
		}
	}
	
};

