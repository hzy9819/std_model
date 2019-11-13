//error correction model
inline int ecm(db x)
{
	if (fabs(x) < eps)
		return 0;
	return x > 0 ? 1 : -1;
}

inline db sqr(db x)
{
	return x * x;
}

struct point
{
	db x, y;
	point() {}
	point(db a, db b) : x(a), y(b) {}

	void input()
	{
		scanf("%lf%lf", &x, &y);
	}

	friend point operator + (const point &a, const point &b)
	{
		return point(a.x + b.x, a.y + b.y);
	}

	friend point operator - (const point &a, const point &b)
	{
		return point(a.x - b.x, a.y - b.y);
	}

	friend bool operator == (const point &a, const point &b)
	{
		return !ecm(a.x - b.x) && !ecm(a.y - b.y);
	}

	friend point operator * (const point &a, const db &b)
	{
		return point(a.x * b, a.y * b);
	}

	friend point operator * (const db &b, const point &a)
	{
		return point(a.x * b, a.y * b);
	}

	friend point operator / (const point &a, const db &b)
	{
		return point(a.x / b, a.y / b);
	}

	double norm()
	{
		return sqrt(sqr(x) + sqr(y));
	}
};

db det(const point &a, const point &b)
{
	return a.x * b.y - a.y * b.x;
}

db dot(const point &a, const point &b)
{
	return a.x * b.x + a.y * b.y;
}

db dist(const point &a, const point &b)
{
	return (a - b).norm();
}

point rotate_point(const point &p, db A)
{
	db tx = p.x, ty = p.y;
	return point(tx*cos(A) - ty * sin(A), tx*sin(A) + ty * cos(A));
}
