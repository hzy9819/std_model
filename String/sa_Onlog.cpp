 
const int N=20010,M=1000100;
 
int n,m,a[N];
 
int buc[M],sa1[N],sa2[N],rk1[N],rk2[N],ht[N];
int *sa=sa1,*rk=rk1,*tp=sa2,*tmp=rk2;
 
void getsa()
{
	register int i,j,k;
	register bool flag=0;
	for(i=1;i<=n;++i)buc[a[i]]++;
	for(i=1;i<M;++i)buc[i]+=buc[i-1];
	for(i=n;i;i--)sa[buc[a[i]]--]=i;
	for(i=1;i<=n;++i)rk[sa[i]]=rk[sa[i-1]]+(a[sa[i]]!=a[sa[i-1]]);
	
	for(k=1;k<=n;k<<=1)
	{
		for(i=1;i<=n;++i)buc[rk[sa[i]]]=i;
		for(i=n;i;i--)if(sa[i]>k)tp[buc[rk[sa[i]-k]]--]=sa[i]-k;
		for(i=n-k+1;i<=n;++i)tp[buc[rk[i]--]]=i;
		for(i=1;i<=n;++i)
		{
			tmp[tp[i]]=tmp[tp[i-1]]+(rk[tp[i-1]]!=rk[tp[i]]||rk[tp[i-1]+k]!=rk[tp[i]+k]);
			if(tmp[tp[i]]==n)flag=1;
		}
		swap(rk,tmp);swap(sa,tp);if(flag)break;
	}
	
	k=0;
	for(i=1;i<n;++i)
	{
		j=rk[i]-1;
		while(a[sa[rk[i]]+k]==a[sa[j]+k])k++;
		ht[rk[i]]=k;if(k)k--;
	}
}
