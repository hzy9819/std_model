/*
  求串a的next数组
*/
  

void GetNext(string & a, int * nxt) {
	int n = a.size();
	nxt[0] = 0;
	for(int i = 1, k = 0; i < n; ++i) {
		while(a[k] != a[i] && k != 0)
			k = nxt[k - 1];
		if(a[k] == a[i])
			k++;
		nxt[i] = k;
	}
}

/*
  求串b在a中出现的次数
*/

int KMP(string & a, string & b, int * nxt) {
	int ans = 0, n = a.size(), m = b.size();
	for(int i = 0, k = 0; i < n; ++i) {
		while(a[i] != b[k] && k != 0)
			k = nxt[k - 1];
		if(a[i] == b[k])
			k++;
		if(k == m)
			ans++, k = 0;
	}
	return ans;
}
