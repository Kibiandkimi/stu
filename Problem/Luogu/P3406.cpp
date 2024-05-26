#include <bits/stdc++.h>
using namespace std;

const int N = 100000, M = 100000;

void read(int&);

int main(){
	
	int n, m;
	static int p[M + 5], a[N + 5], b[N + 5], c[N + 5];
	read(n), read(m);

	for(int i = 1; i <= m; i++){
		read(p[i]);
	}

	for(int i = 1; i < n; i++){
		read(a[i]), read(b[i]), read(c[i]);
	}


	static int pre[N + 5], sum[N + 5];

	for(int i = 1; i < m; i++){
		if(p[i] < p[i+1]){
			pre[p[i]]++;
			pre[p[i+1]]--;
		}else{
			pre[p[i+1]]++;
			pre[p[i]]--;
		}
	}

	for(int i = 1; i < n; i++){
		sum[i] = sum[i-1] + pre[i];
	}


	long long ans = 0;

	for(int i = 1; i < n; i++){
		ans += min((long long)sum[i] * a[i], (long long)sum[i]*b[i] + c[i]);
	}

	printf("%lld\n", ans);
}

void read(int &x){
	int s = 0, w = 1, c = getchar();
	while(c < '0' || '9' < c){
		if(c == '-'){
			w = -1;
		}
		c = getchar();
	}
	while('0' <= c && c <= '9'){
		s = s * 10 + c - '0';
		c = getchar();
	}
	x = s * w;
}