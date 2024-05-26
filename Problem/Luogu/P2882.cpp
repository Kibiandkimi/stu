#include <bits/stdc++.h>
using namespace std;

const int N = 5000;

void read(int&);
void read(bool&);

int main(){
	
	int n;
	static bool a[N + 5];
	static int pre[N + 5], sum[N + 5];

	read(n);
	for(int i = 1; i <= n; i++)
	{
		read(a[i]);
	}

	for (int i = n; i >= 1; --i)
	{
		int ans = 0;
		bool flag = false;
		for (int j = 1; j <= n; ++j)
		{
			sum[j] = sum[j-1] + pre[j];
			if(!(a[j] ^ (sum[j]%2))){
				if(j+i-1 > n){
					flag = true;
					break;
				}
				ans++;
				pre[j]++;
				sum[j]++;
				pre[j+i]--;
			}
		}
		if(!flag){
			printf("%d %d\n", i, ans);
			return 0;
		}
		memset(sum, 0, sizeof sum);
		memset(pre, 0, sizeof pre);
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

void read(bool &x){
	int c = getchar();
	while(c != 'B' && c != 'F'){
		c = getchar();
	}
	x = (c == 'F');
}