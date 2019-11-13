// ÂãÈýÎ¬Æ«Ðò


#include<cmath>
#include<ctime>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<iostream>
#include<algorithm>
#include<iomanip>
#include<vector>
#include<string>
#include<bitset>
#include<queue>
#include<map>
#include<set>
 
using namespace std;
 
typedef long long ll;
 
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
	return x*f;
}
void print(int x)
{if(x<0)putchar('-'),x=-x;if(x>=10)print(x/10);putchar(x%10+'0');}
 
const int N=100100;
 
int n,m,a[N];
 
struct node{int a,b,c;}p[N];
 
inline bool cmp(int x,int y)
{return p[x].a==p[y].a?p[x].b==p[y].b?p[x].c<p[y].c:p[x].b<p[y].b:p[x].a<p[y].a;}
 
int bit[N];
 
inline void modify(int x,int val)
{for(;x<=m;x+=(x&-x))bit[x]+=val;}
 
inline int query(int x)
{int res=0;for(;x;x-=(x&-x))res+=bit[x];return res;}
 
int ans[N],res[N],tmp[N];
 
void cdq(int l,int r)
{
	int mid=(l+r)>>1,top=l-1;
	if(l==r)return ;
	cdq(l,mid);cdq(mid+1,r);
	register int i=l,j=mid+1;
	while(j<=r)
	{
		while(i<=mid&&p[a[i]].b<=p[a[j]].b)modify(p[a[i]].c,1),i++;
		res[a[j]]+=query(p[a[j]].c);j++;
	}
	while(i>l)i--,modify(p[a[i]].c,-1);
	i=l;j=mid+1;
	while(j<=r||i<=mid)
	{
		if(i>mid)tmp[++top]=a[j++];
		else if(j>r||p[a[i]].b<p[a[j]].b)tmp[++top]=a[i++];
		else tmp[++top]=a[j++];
	}
	memcpy(a+l,tmp+l,sizeof(int)*(r-l+1));
}
 
int main()
{
	n=read();m=read();
	register int i,j,k;
	for(i=1;i<=n;++i){p[i].a=read();p[i].b=read();p[i].c=read();a[i]=i;}
	sort(a+1,a+1+n,cmp);
	j=1;
	for(i=1;i<=n;i=++j)
	{
		while(!(cmp(a[j],a[j+1])|cmp(a[j+1],a[j])))j++;
		for(k=i;k<=j;++k)res[a[k]]+=j-k;
	}
	cdq(1,n);
	for(i=1;i<=n;++i)ans[res[i]]++;
	for(i=0;i<n;++i){print(ans[i]),puts("");}
	return 0;
}
