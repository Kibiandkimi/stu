#include <bits/stdc++.h>
using namespace std;

const int N = 1000;

void read(int&);

int main(){
	int n, m;
	read(n), read(m);

	static int sum[N + 5][N + 5], pre[N + 5][N + 5];
	for(int i = 1; i <= m; i++){
		int x1, y1, x2, y2;
		read(x1), read(y1), read(x2), read(y2);
		pre[x1][y1]++;
		pre[x1][y2+1]--;
		pre[x2+1][y1]--;
		pre[x2+1][y2+1]++;
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			sum[i][j] = pre[i][j] + sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
			printf("%d ", sum[i][j]);
		}
		printf("\n");
	}
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