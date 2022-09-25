//
// Created by kibi on 2022/9/24.
//
#include <bits/stdc++.h>
using namespace std;
const int mod = 19650827;
int n, d[2005][2005][2], a[2005];

void read(int &x);

int main(){
    read(n);
    for(int i = 1; i <= n; i++){
        read(a[i]);
        d[i][i][0] = 1;
    }
    for(int l = 1; l < n; l++){
        for(int i = 1, j = i+l; j <= n; i++, j++){
            if(a[i] < a[i+1]){
                d[i][j][0] = (d[i][j][0] + d[i+1][j][0]) % mod;
            }
            if(a[i] < a[j]){
                d[i][j][0] = (d[i][j][0] + d[i+1][j][1]) % mod;
            }
            if(a[j] > a[i]){
                d[i][j][1] = (d[i][j][1] + d[i][j-1][0]) % mod;
            }
            if(a[j] > a[j-1]){
                d[i][j][1] = (d[i][j][1] + d[i][j-1][1]) % mod;
            }
        }
    }
    printf("%d", (d[1][n][1] + d[1][n][0]) % mod);
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