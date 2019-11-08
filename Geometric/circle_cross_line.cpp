
// P = A + t(B - A)
// sqr(P.x - o.x) + sqr(P.y - o.y) = sqr(R)
void circle_cross_line(point a, point b, point o, db r, point ret[], int &num)
{
	db x0 = o.x, y0 = o.y;
	db x1 = a.x, y1 = a.y;
	db x2 = b.x, y2 = b.y;
	db dx = x2 - x1, dy = y2 - y1;
	point v = b - a;
	db A = sqr(dx) + sqr(dy);
	db B = 2 * dot(v, a - o);
	db C = sqr(x1 - x0) + sqr(y1 - y0) - sqr(r);
	db delta = B * B - 4 * A*C;
	num = 0;

	if (ecm(delta) >= 0)
	{
		db t1 = (-B - sqrt(delta)) / 2.0 / A;
		db t2 = (-B + sqrt(delta)) / 2.0 / A;

		if (ecm(t1 - 1) <= 0 && ecm(t1) >= 0)
			ret[++num] = point(x1 + dx*t1, y1 + dy*t1);
		if (ecm(t1 - t2) && ecm(t2 - 1) <= 0 && ecm(t2) >= 0)
			ret[++num] = point(x1 + dx*t2, y1 + dy*t2);
	}
}
