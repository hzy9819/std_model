// 邻接表

/*
	描述一条有向边
	to：指向的点
	next：下一条边
	w：边权
*/
struct Edge {
	int to, next, w;
}; 

/*
	加入一条边
	x，y：边 x->y
	w: 边权
	e： 边数组
	lst： 邻接表头（初始值为-1）
	d：边数（每次插入+1）
*/

void add(int x, int y, int w) {
	e[d].to = y, e[d].next = lst[x], e[d].w = w, lst[x] = d++;
}

/*
	实例：遍历一个点所有的相邻点
	x: 遍历点
*/
void For(int x) {
	for(int i = lst[x]; i >= 0; i = e[i].next)
		cout << e[i].to << " ";
}
