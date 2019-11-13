/*
你有一个N*N的棋盘，每个格子内有一个整数，初始时的时候全部为0
1
x y A  1<=x,y<=N，A是正整数
将格子x,y里的数字加上A

2
x1 y1 x2 y2 1<=x1<= x2<=N 1<=y1<= y2<=N
输出x1 y1 x2 y2这个矩形内的数字和

3 终止程序
*/
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
#include<bitset>
#include<string>
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
void print(ll x)
{if(x<0)putchar('-'),x=-x;if(x>=10)print(x/10);putchar(x%10+'0');}
 
const int N=200100;
 
int cur=1,tot,root,block;
 
ll ans;
 
struct P
{
	int d[2],mn[2],mx[2],ls,rs;ll val,sum;
	inline int& operator [](int x){return d[x];}
	friend bool operator <(const P &x,const P &y){return x.d[cur]<y.d[cur];}
}p[N];
 
struct kdtree
{
	P tr[N],T;
	
	inline void pushup(int k)
	{
		for(int i=0;i<2;++i)
		{
			tr[k].mn[i]=tr[k].mx[i]=tr[k][i];
			if(tr[k].ls)tr[k].mx[i]=max(tr[k].mx[i],tr[tr[k].ls].mx[i]),tr[k].mn[i]=min(tr[k].mn[i],tr[tr[k].ls].mn[i]);
			if(tr[k].rs)tr[k].mx[i]=max(tr[k].mx[i],tr[tr[k].rs].mx[i]),tr[k].mn[i]=min(tr[k].mn[i],tr[tr[k].rs].mn[i]);
		}
		tr[k].sum=tr[k].val+tr[tr[k].ls].sum+tr[tr[k].rs].sum;
	}
	
	void insert(int &k,int now)
	{
		if(!k)
		{
			k=++tot;
			tr[k].val=tr[k].sum=T.val;
			for(int i=0;i<2;++i){tr[k][i]=tr[k].mx[i]=tr[k].mn[i]=T[i];}
			return ;
		}
		if(T[now]<tr[k][now])insert(tr[k].ls,now^1);
		else if(T[now]>tr[k][now]||(T[now]==tr[k][now]&&T[now^1]^tr[k][now^1]))insert(tr[k].rs,now^1);
		else {tr[k].sum+=T.val;tr[k].val+=T.val;return ;}
		pushup(k);
	}
	
	int build(int l,int r,int now)
	{
		if(l>r)return 0;
		cur=now;
		int mid=(l+r)>>1;
		nth_element(p+l,p+mid,p+r+1);
		tr[mid]=p[mid];
		tr[mid].ls=build(l,mid-1,now^1);
		tr[mid].rs=build(mid+1,r,now^1);
		pushup(mid);
		return mid;
	}
	
	void kdinsert(int x,int y,int num)
	{
		T[0]=x;T[1]=y;T.val=T.sum=num;
		insert(root,0);
		if(tot==block)
		{
			for(int i=1;i<=tot;++i)p[i]=tr[i];
			block+=10000,root=build(1,tot,0);
		}
	}
	
	inline bool in(int x,int y,int a,int b)
	{return T.mx[1]<=b&&T.mn[1]>=y&&T.mx[0]<=a&&T.mn[0]>=x;}
	
	inline bool pin(int x,int y,int a,int b)
	{return T[0]<=a&&T[0]>=x&&T[1]>=y&&T[1]<=b;}
	
	inline bool out(int x,int y,int a,int b)
	{return T.mn[1]>b||T.mx[1]<y||T.mx[0]<x||T.mn[0]>a;}
	
	void query(int k,int x,int y,int a,int b)
	{
		if(!k)return ;T=tr[k];
		if(in(x,y,a,b)){ans+=tr[k].sum;return ;}
		if(out(x,y,a,b)){return ;}
		if(pin(x,y,a,b))ans+=tr[k].val;
		query(tr[k].ls,x,y,a,b);
		query(tr[k].rs,x,y,a,b);
	}
	
	void kdquery(int x,int y,int a,int b)
	{
		ans=0;
		query(root,x,y,a,b);
		print(ans);puts("");
	}
	
}kd;
 
int main()
{
	int n=read();block=10000;
	register int opt=read(),x,y,a,b;
	while(opt^3)
	{
		x=read()^ans;y=read()^ans;a=read()^ans;
		if(opt==1){kd.kdinsert(x,y,a);}
		else b=read()^ans,kd.kdquery(x,y,a,b);
		opt=read();
	}
	return 0;
}
