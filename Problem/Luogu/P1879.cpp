//
// Created by kibi on 2022/9/28.
//
#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9;
int n, m, d[10005][15], avl[15];
bool st[10005];

void read(int &x);

int main(){
    read(n), read(m);
    for(int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int t;
            read(t);
            avl[i] = (avl[i] << 1) + t;
        }
    }
    for(int i = 0, mxi = 1<<m; i < mxi; i++){
        st[i] = ((i&(i<<1))==0);
    }
    d[0][0] = 1;
    for(int i = 1, mxi = n; i <= mxi; i++){
        for(int j = 0, mxj = (1<<m); j < mxj; j++){
            if(st[j] && ((j & avl[i])==j) ){
                for(int k = 0, mxk = (1<<m); k < mxk; k++){
                    if((k & j) == 0){
                        d[j][i] = (d[j][i] + d[k][i-1]) % mod;
                    }
                }
            }
        }
    }
    long long ans = 0;
    for(int i = 0, mxi = (1<<m); i < mxi; i++){
        ans = (ans + d[i][n]) % mod;
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
    while('0'<=c && c<='9'){
        s = s*10 + c-'0';
        c = getchar();
    }
    x = s*w;
}