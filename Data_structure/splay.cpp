
struct splay_tree{
	struct node{
		//...
		node* fa;//add
		//...
	};
	int sep(node* o) {return o->fa->ch[0]==o;}

	void rotate(node *o,int d)
	{
		node *p=o->ch[d^1];
		o->ch[d^1]=p->ch[d];
		p->ch[d]=o;
		if(o->fa!=nl) o->fa->ch[sep(o)^1]=p;
		p->fa=o->fa; o->fa=p;
		if(o->ch[d^1]!=nl) o->ch[d^1]->fa=o;
		o->maintain(); p->maintain();
		o=p;
	}

	void splay(node *&o)
	{
		while(o->fa!=nl)
		{
			if(o->fa->fa==nl) rotate(o->fa,sep(o));
			else
			{
				if(sep(o)!=sep(o->fa)) rotate(o->fa,sep(o)),rotate(o->fa,sep(o));
				else rotate(o->fa->fa,sep(o->fa)),rotate(o->fa,sep(o));
			}
		}
		root=o; //important
	}

	void insert(node* &o,node* fa,int x)
	{
		if(o==nl)
		{
			o=&put[ps++]; *o=node();
			o->dt=x; o->fa=fa;
			o->maintain();
			splay(o);
			return;
		}
		if(o->dt>=x) insert(o->ch[0],o,x);
		else insert(o->ch[1],o,x);
	}

	void find(node* o,int &res,LL tot)
	{
		if(o==nl) return;
		if(o->ch[0]==nl)
		{
			if(tot+o->dt>m) {splay(o); return; } //after find: splay
			else res+=1,find(o->ch[1],res,tot+o->dt);
		}
		else
		{
			if(o->ch[0]->s+tot>m) find(o->ch[0],res,tot);
			else
			{
				tot+=o->ch[0]->s, res+=o->ch[0]->d;
				if(tot+o->dt>m) {splay(o); return; }
				else res++,find(o->ch[1],res,tot+o->dt);
			}
		}
	}
//more: merge, split, ...
	
}

