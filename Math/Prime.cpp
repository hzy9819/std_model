/*
  素数的线性筛法，晒出1~N内的所有素数
  bool b[N] : 判断该数是否为素数
  int p[N] : 用于存储素数
  sz ： 素数的数量
*/

const int N = 1000010;
int p[N], sz;
bool b[N];

void Prime() {
	for(int i = 2; i < N; ++i) {
		if(!b[i]) p[++sz] = i;
		for(int j = 1; j <= sz && i * p[j] < N; ++j) {
			b[i * p[j]] = 1;
			if(i % p[j] == 0)
				break;
		}
	}
}
