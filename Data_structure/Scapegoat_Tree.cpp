/*
1. 插入x数
2. 删除x数(若有多个相同的数，因只删除一个)
3. 查询x数的排名(若有多个相同的数，因输出最小的排名)
4. 查询排名为x的数
5. 求x的前驱(前驱定义为小于x，且最大的数)
6. 求x的后继(后继定义为大于x，且最小的数)
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
#include<string>
#include<bitset>
#include<queue>
#include<map>
#include<set>
using namespace std;
 
typedef long long ll;
typedef double db;
 
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
	return x*f;
}
 
void print(int x)
{if(x<0)putchar('-'),x=-x;if(x>=10)print(x/10);putchar(x%10+'0');}
 
const int N=2001000,inf=0X3f3f3f3f;
const db alpha=0.75;
 
struct scapegoat_tree{int s[2],fa,sz,val;}tr[N];
 
int root,tot;
 
void initial()
{
	tot=2;root=1;
	tr[1].val=-inf;tr[1].sz=2;tr[1].s[1]=2;
	tr[2].val=inf;tr[2].sz=1;tr[2].fa=1;
}
 
bool balance(int k)
{return (alpha*tr[k].sz>=(db)tr[tr[k].s[0]].sz)&&(alpha*tr[k].sz>=(db)tr[tr[k].s[1]].sz);}
 
int sta[N],top;
 
void seek(int k)
{if(!k)return;seek(tr[k].s[0]);sta[++top]=k;seek(tr[k].s[1]);}
 
int build(int l,int r)
{
	if(l>r)return 0;
	int mid=(l+r)>>1,now=sta[mid];
	tr[now].s[0]=build(l,mid-1);
	tr[now].s[1]=build(mid+1,r);
	tr[tr[now].s[1]].fa=tr[tr[now].s[0]].fa=now;
	tr[now].sz=tr[tr[now].s[0]].sz+tr[tr[now].s[1]].sz+1;
	return now;
}
 
void rebuild(int k)
{
	top=0;seek(k);
	int fa=tr[k].fa,son=(tr[fa].s[1]==k),now=build(1,top);
	tr[now].fa=fa;
	tr[fa].s[son]=now;
	if(root==k)root=now;
}
 
void insert(int x)
{
	register int now=root,inv=0,i;
	register bool son;
	tr[++tot].val=x;tr[tot].sz=1;
	while(1)
	{
		tr[now].sz++;
		son=(x>=tr[now].val);
		if(tr[now].s[son])now=tr[now].s[son];
		else {tr[tot].fa=now;tr[now].s[son]=tot;break;}
	}
	for(i=tot;i;i=tr[i].fa)if(!balance(i))inv=i;
	if(inv)rebuild(inv);
}
 
inline int get_pos(int x)
{
	int now=root;
	while(tr[now].val^x)
	x<tr[now].val?now=tr[now].s[0]:now=tr[now].s[1];
	return now;
}
 
void del(int k)
{
	if(tr[k].s[0]&&tr[k].s[1])
	{
		int aim=tr[k].s[0];
		while(tr[aim].s[1])aim=tr[aim].s[1];
		tr[k].val=tr[aim].val;
		k=aim;
	}
	int tmp=tr[k].s[0]?tr[k].s[0]:tr[k].s[1],son=(tr[tr[k].fa].s[1]==k);
	tr[tr[k].fa].s[son]=tmp;tr[tmp].fa=tr[k].fa;
	if(root==k)root=tmp;
	while(tr[k].fa)k=tr[k].fa,tr[k].sz--;
}
 
inline int query_rank(int x)
{
	int now=root,res=0;
	while(now)
	tr[now].val<x?(res+=tr[tr[now].s[0]].sz+1,now=tr[now].s[1]):now=tr[now].s[0];
	return res;
}
 
inline int query_kth(int kth)
{
	int now=root;
	while(1)
	{
		if(tr[tr[now].s[0]].sz+1==kth)return now;
		tr[tr[now].s[0]].sz>=kth?now=tr[now].s[0]:(kth-=tr[tr[now].s[0]].sz+1,now=tr[now].s[1]);
	}
}
 
inline int query_pre(int x)
{
	int now=root,res;
	while(now)
	tr[now].val<x?(res=tr[now].val,now=tr[now].s[1]):now=tr[now].s[0];
	return res;
}
 
inline int query_sub(int x)
{
	int now=root,res;
	while(now)
	tr[now].val>x?(res=tr[now].val,now=tr[now].s[0]):now=tr[now].s[1];
	return res;
}
 
int main()
{
	register int n,opt,x;
	initial();
	n=read();
	while(n--)
	{
		opt=read();x=read();
		switch(opt)
		{
			case 1:insert(x);break;
			case 2:del(get_pos(x));break;
			case 3:print(query_rank(x));puts("");break;
			case 4:print(tr[query_kth(x+1)].val);puts("");break;
			case 5:print(query_pre(x));puts("");break;
			case 6:print(query_sub(x));puts("");break;
		}
	}
	return 0;
}
