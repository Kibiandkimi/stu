#include <bits/stdc++.h>
using namespace std;

const int N = 1000000;

int main(){
	static char s[N + 5];
	scanf("%s", s+1);
	static int f[N+5];
	int ans = 0, end = -1;
	for(int i = 2; s[i]; i++){
		if(s[i] == '(' || s[i] == '['){
			continue;
		}else if(s[i] == ')' && s[i - f[i-1] - 1] == '(' || 
			s[i] == ']' && s[i - f[i-1] - 1] == '['){
			f[i] = f[i-1]+2+f[i-f[i-1]-2];
			if(ans < f[i]){
				ans = f[i];
				end = i;
			}

		}
	}

	for(int i = end-ans+1; i <= end; i++){
		printf("%c", s[i]);
	}
}