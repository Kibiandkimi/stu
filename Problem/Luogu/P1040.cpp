//
// Created by kibi on 2022/9/26.
//
#include <bits/stdc++.h>
using namespace std;
int n, rt[55][55];
long long f[55][55];

void read(int &x);
void print(int l, int r);

int main(){
    read(n);
    for(int i = 1; i <= n; i++){
        int t;
        read(t);
        f[i][i] = t;
        f[i][i-1] = 1;
        rt[i][i] = i;
    }
    for(int l = 1; l < n; l++){
        for(int i = 1, j = i+l; j <= n; i++, j++){
            f[i][j] = f[i+1][j] + f[i][i];
            rt[i][j] = i;
            for(int k = i+1; k < j; k++){
                if(f[i][j] < f[i][k-1] * f[k+1][j] + f[k][k]){
                    f[i][j] = f[i][k-1] * f[k+1][j] + f[k][k];
                    rt[i][j] = k;
                }
            }
        }
    }
    printf("%lld\n", f[1][n]);
    print(1, n);
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
        s = s*10 + c-'0';
        c = getchar();
    }
    x = s*w;
}

void print(int l, int r){
    if(l > r){
        return ;
    }
    printf("%d ", rt[l][r]);
    if(l == r){
        return ;
    }
    print(l, rt[l][r]-1);
    print(rt[l][r]+1, r);
}