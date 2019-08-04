/*
  计算几何的基本声明和数值定义
*/

const db eps = 1e-8; // 误差
const db PI = acos(-1.);

int dcmp(db x) {
	if(fabs(x) < eps) return 0;
	return x > 0 ? 1 : -1;
} // 判断是否在误差内，不然返回正负性

struct Point {
	db x, y;
	Point(db _x = 0, db _y = 0) : x(_x), y(_y) {}
	db angle() const {
		if(dcmp(x) == 0) {
			if(dcmp(y == 0)) return 0.0;
			else if(dcmp(y) == 1) return PI / 2.0;
			else return PI * 1.5;
		}
		else if(dcmp(x) == -1) return PI + atan(y / x);
		else if(dcmp(x) == 1 && dcmp(y) >= 0) return atan(y / x);
		else if(dcmp(x) == 1 && dcmp() == -1) return atan(y / x) + 2.0 * PI;
		else return 0.0;
	} // 极角
	db Length() const { return sqrt(x * x + y * y) ;}
};

Point operator + (Point a, Point b) { return Point(a.x + b.x, a.y + b.y); }
Point operator - (Point a, Point b) { return Point(a.x - b.x, a.y - b.y); }
Point operator * (Point a, db k) { return Point(a.x * k, a.y * k); }
Point operator / (Point a, db k) { return Point(a.x / k, a.y / k); }

bool operator == (Point a, Point b) { return dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) == 0; }
db Dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }
db Cross(Piont a, Point b) { return a.x * b.y - a.y * b.x; }
db Length(Point a, Point b) { return Dot(a, a); }

struct Polygon {
	int num; // 点数
	Point * p;
	db Area() const { // 面积
		db ans = 0;
		ans = Cross(p[0], p[num - 1]);
		for(int i = 1; i < num; ++i)
			ans += Cross(p[i], p[i - 1]);
		return fabs(ans) * 0.5;
	}
	db C() const { // 周长
		db ans = 0;
		ans = Length(p[0] - p[num - 1]);
		for(int i = 1; i < num; ++i)
			ans += Length(p[i] - p[i - 1]);
		return ans;
	}
	db Rotating_Calipers() const { // 旋转卡壳求凸包的直径
		int q = 1;
		db ans = 0;
		p[num] = p[0]; // 注意此处要将数组稍微开大
		for(int i = 0; i < num; ++i) {
			while(Cross(p[i + 1] - p[i], p[q + 1] - p[i]) > Cross(p[i + 1] - p[i], p[q] - p[i])) q = (q + 1) % n;
			ans = max(ans, max(Length(p[i + 1] - p[q + 1]), Length(p[i] - p[q])));
		}
		return ans;
	}
};

struct Line { // 用两个点表示一条线
	Point p, v; 
	Line() {}
	Line(Point _p, Point _v) : p(p), v(v) {}
};
	
