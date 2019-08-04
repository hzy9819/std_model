/*
	Spfa算法求单源最短路
	lst: 邻接表头
	e: 边数组
	dis: 求单源最短路的结果(初始值为-1)
	s: 起点
	in_queue: 记录点是否在队列中的bool数组(视情况开在函数外)
*/

void Spfa(int * lst, Edge * e, int * dis, int s) {
	Queue <int> Q;
	dis[s] = 0;
	Q.push(s), in_queue[s] = 1;
	while(!Q.empty()) {
		int x = Q.front();
		Q.pop(), in_queue[x] = 0;
		for(int i = lst[x]; i >= 0; i = e[i].next)
			if(dis[e[i].to] == -1 || dis[e[i].to] > dis[x] + e[i].w) {
				dis[e[i].to] = dis[x] + e[i].w;
				if(!in_queue[e[i].to])
					Q.push(e[i].to), in_queue[e[i].to] = 1;
			}
	}

}