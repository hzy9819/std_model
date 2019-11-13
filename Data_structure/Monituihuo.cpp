/*---- from poj1379 ----*/

struct point{
	db x,y;
	point() {}
	point(db _x, db _y):x(_x),y(_y) {}
}p[nn];
typedef point vector;
const db iniT=1e4,endT=1e-4,maxR=1073741823;
const db PI=acos(-1.0);
int t,m,x,y;
db T,ansx,ansy,ans,tmpx,tmpy,rate;
int d[4][2]={{1,1},{1,-1},{-1,1},{-1,-1}};

db R()
{
	return ((rand()<<15)|rand())*1.0/maxR;
}

inline db dist(point _p,point _q) {return sqrt((_p.x-_q.x)*(_p.x-_q.x)+(_p.y-_q.y)*(_p.y-_q.y)); }

db F(point _p) //can be changed
{
	db dis=1e9;
	for(int i=1;i<=m;++i)
	{
		dis=min(dis,dist(_p,p[i]));
	}
	return dis;
}

int main()
{
	srand((int)time(0));
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);

	int xi,yi;
	db x0,y0,dx,dy,ang,nF,tF;
	scanf("%d\n",&t);
	while(t--)
	{
		scanf("%d%d%d\n",&x,&y,&m);
		for(int i=1;i<=m;++i)
		{
			scanf("%d%d\n",&xi,&yi);
			p[i]=point(xi,yi);
		}
		T=max(x,y);
		rate=0.999;
		ans=ansx=ansy=0;
		x0=x*R(),y0=y*R();
		while(T>endT)
		{
			nF=F(point(x0,y0));
			ang=R()*2*PI;
			dx=T*cos(ang),dy=T*sin(ang);
			for(int j=0;j<4;++j)
			{
				tmpx=x0+d[j][0]*dx,tmpy=y0+d[j][1]*dy;
				if(tmpx<0) tmpx=0;
				if(tmpx>x) tmpx=x;
				if(tmpy<0) tmpy=0;
				if(tmpy>y) tmpy=y;
				tF=F(point(tmpx,tmpy));
				if(tF>nF) {x0=tmpx,y0=tmpy; break; }
				else if(R()<exp(-(nF-tF)/T)) {x0=tmpx,y0=tmpy; break; }
			}
			if(F(point(x0,y0))>ans)
			{
				ans=F(point(x0,y0));
				ansx=x0,ansy=y0;
			}
			T*=rate;
		}

		printf("The safest point is (%.1lf, %.1lf).\n",ansx,ansy);
	}

	return 0;
}
