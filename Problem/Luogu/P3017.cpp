#include <bits/stdc++.h>
using namespace std;

const int N = 500;

void read(int&);
bool check(int x, auto data, auto sum);

int main(){
	
	int r, c, a, b;
	static int n[N + 5][N + 5], sum[N + 5][N + 5];

	read(r), read(c), read(a), read(b);
	array data = {r, c, a, b};

	for(int i = 1; i <= r; i++){
		for(int j = 1; j <= c; j++){
			read(n[i][j]);
			sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + n[i][j];
		}
	}

	int _l = 0, _r = sum[r][c], ans;

	while(_l <= _r){
		int mid = (_l+_r)/2;
		if(check(mid, data, sum)){
			_l = mid+1;
			ans = mid;
		}else{
			_r = mid-1;
		}
	}

	printf("%d\n", ans);
}

bool check(int x, auto data, auto sum){
	int now = 0, num = 0;
	auto[r, c, a, b] = data;
	// int r = data[0], c = data[1], a = data[2], b = data[3];
	for(int i = 1; i <= r; i++){
		int dis = 0, s = 0;
		for(int j = 1; j <= c; j++){
			int tem = (sum[i][j]-sum[i][j-1]) - (sum[now][j]-sum[now][j-1]);
			if(dis + tem < x){
				dis += tem;
			}else{
				s++;
				dis = 0;
			}
		}
		if(s >= b){
			now = i, num++;
		}
	}
	if(num < a){
		return false;
	}
	return true;
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