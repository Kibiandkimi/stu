//
// Created by kibi on 2022/9/25.
//
#include <bits/stdc++.h>
using namespace std;
int n, m, t[505], g[505][205];

void read(int &x);

int main(){
    read(n), read(m);
    for(int i = 1; i <= n; i++){
        read(t[i]);
    }
    sort(t+1, t+1+n);
    for(int i = 1; i <= n; i++){
        g[i][0] = 1e9;
        for(int j = 0; j <= min(t[i] - t[i-1] - m, m-1); j++){
            g[i][0] = min(g[i][0], g[i-1][j]);
        }
        for(int j = 1; j < 2*m; j++){
            g[i][j] = min(g[i][j-1], t[i] + j - t[i-1] - m >= 0 && t[i] + j - t[i-1] - m < 2*m ? g[i-1][t[i] + j - t[i-1] - m] : (int)1e9 );
        }
        for(int j = 0; j < 2*m; j++){
            g[i][j] = min(g[i][j], t[i] + j - t[i-1] < 2*m ? g[i-1][t[i] + j - t[i-1]] : (int)1e9) + j;
        }
    }
    int ans = 1e9;
    for(int i = 0; i < m; i++){
        ans = min(ans, g[n][i]);
    }
    printf("%d", ans);
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c) {
        if (c == '-') {
            w = -1;
        }
        c = getchar();
    }
    while('0'<=c && c<='9'){
        s = s*10 + c-'0';
        c = getchar();
    }
    x = s*w;
}