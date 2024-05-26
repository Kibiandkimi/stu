//
// Created by kibi on 2022/9/25.
//
#include <bits/stdc++.h>
using namespace std;
int n, p, v[55], d[55][55][2], sum[55], loc[55];

void read(int &x);

int main(){
    read(n), read(p);
    for(int i = 1; i <= n; i++){
        read(loc[i]), read(v[i]);
        sum[i] = sum[i-1] + v[i];
    }
    memset(d, 0x3f, sizeof d);
    d[p][p][0] = d[p][p][1] = 0;
    for(int l = 2; l <= n; l++){
        for(int i = max(p-l+1, 1), j = i+l-1; i <= p && j <= n; i++, j++){
            d[i][j][0] = min(d[i][j][0], min(d[i + 1][j][0] + (loc[i + 1] - loc[i]) * (sum[i] + (sum[n] - sum[j])), d[i + 1][j][1] + (loc[j] - loc[i]) * (sum[i] + (sum[n] - sum[j]))));
            d[i][j][1] = min(d[i][j][1], min(d[i][j-1][1] + (loc[j] - loc[j-1]) * (sum[i-1] + (sum[n] - sum[j-1])), d[i][j-1][0] + (loc[j] - loc[i]) * (sum[i-1] + (sum[n] - sum[j-1]))));
        }
    }
    printf("%d", min(d[1][n][0], d[1][n][1]));
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
        if(c == '-'){
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