#include<cmath>
#include<ctime>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<iomanip>
#include<vector>
#include<string>
#include<bitset>
#include<queue>
#include<set>
#include<map>
using namespace std;
 
typedef long long ll;
 
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
void print(int x)
{if(x<0)putchar('-'),x=-x;if(x>=10)print(x/10);putchar(x%10+'0');}
 
const int N=1010;
 
int K,n,A,D,P;
 
inline int qpow(int x,int y)
{
	int res(1);
	while(y)
	{
		if(y&1) res=(ll)res*x%P;
		x=(ll)x*x%P;
		y>>=1;
	}
	return res;
}
 
inline int inv(int x)
{return x==1 ? 1 : (ll)(P-P/x)*inv(P%x)%P;}
 
int a[N],X[N],Y[N];
 
void Lagrange_interpolation(int deg)
{
	register int i,j,k;
	static int f[N],g[N];
	memset(a,0,sizeof(a));
	memset(f,0,sizeof(f)),
	memset(g,0,sizeof(g));
	f[0]=1;
	// f[i][j]=f[i-1][j-1]-f[i-1][j]*X[i]
	// f[j]=g[j-1]-g[j]*X[i]
	// g[j-1]=f[j]+g[j]*X[i]
	
	for(i=1;i<=deg;++i)
	{
		for(j=deg;j;--j)
			f[j]=(f[j-1]+(ll)(P-X[i])*f[j])%P;
		f[0]=(ll)f[0]*(P-X[i])%P;
	}
	for(i=1;i<=deg;++i)
	{
		for(j=deg;j;--j)
			g[j-1]=(f[j]+(ll)g[j]*X[i])%P;
		k=1;
		for(j=1;j<=deg;++j)
			if(j==i) continue;
			else k=(ll)k*((ll)P+X[i]-X[j])%P;
		k=(ll)inv(k)*Y[i]%P;
		
		for(j=0;j<deg;++j)
			a[j]=(a[j]+(ll)k*g[j])%P;
	}
}
 
inline int get_value(int deg,int x)
{
	register int i,res(0),pw(1);
	for(i=0;i<=deg;++i)
		res=(res+(ll)a[i]*pw)%P,
		pw=(ll)x*pw%P;
	return res;
}
 
void solve()
{
	K=read(),n=read(),A=read(),D=read(),P=read();
	n%=P,A%=P,D%=P;
	register int i;
	
	Y[0]=(K==0);
	for(i=1;i<=K+2;++i)
		X[i]=i,Y[i]=((ll)Y[i-1]+qpow(i,K))%P;
	Lagrange_interpolation(K+2);
	printf("%d ",get_value(K+1,n));
	
	for(i=1;i<=K+3;++i)
		X[i]=i,Y[i]=((ll)Y[i-1]+get_value(K+1,i))%P;
	Lagrange_interpolation(K+3);
	printf("%d ",get_value(K+2,n));
	
	Y[0]=get_value(K+2,A);
	for(i=1;i<=K+4;++i)
		X[i]=i,Y[i]=((ll)Y[i-1]+get_value(K+2,(A+(ll)D*i)%P))%P;
	Lagrange_interpolation(K+4);
	printf("%d\n",get_value(K+3,n));
}
 
int main()
{
	int T=read();
	while(T--) solve();
	return 0;
}
 
