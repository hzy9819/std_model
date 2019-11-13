// calculate definite integral of f(x) from a to b

db cal(db l,db r)
{
	return (r-l) * (  f(l) + f(r) + 4*f( (l+r)/2 )  ) / 6;
}
 
db simpson(db l,db r)
{
	db mid = (l+r) / 2;
	db S0 = cal(l, r),
		S1 = cal(l, mid),
		S2 = cal(mid, r);
	if(abs(S0-S1-S2)<eps)
		return S0;
	return simpson(l, mid) + simpson(mid, r);
}
