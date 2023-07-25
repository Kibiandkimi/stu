//
// Created by kibi on 23-7-20.
//
#include <bits/stdc++.h>
using namespace std;

const int T = 2000, P = 2000;

void read(int&);

int main(){
    int t, p, w;
    static int f[T + 5][P + 5];

    read(t), read(p), read(w);

    memset(f, 0xc0, sizeof f);

    for(int i = 1; i <= t; i++){
        int ap, bp, as, bs;
        read(ap), read(bp), read(as), read(bs);
        for(int j = 0; j <= as; j++){
            f[i][j] = -1 * j * ap;
        }
        for(int j = 0; j <= p; j++){
            f[i][j] = max(f[i][j], f[i-1][j]);
        }
        if(i <= w){
            continue;
        }

        int l = 1, r = 0;

        static int q[T+5];

        for(int j = 0; j <= p; j++){
            while(l <= r && q[l] < j - as){
                l++;
            }
            while(l <= r && f[i-w-1][q[r]] + q[r]*ap <= f[i-w-1][j] + j*ap){
                r--;
            }
            q[++r] = j;
            if(l <= r){
                f[i][j] = max(f[i][j], f[i-w-1][q[l]] + q[l]*ap-j*ap);
            }

        }

        l = 1, r = 0;

        for(int j = p; j >= 0; j--){
            while(l <= r && q[l] > j+bs){
                l++;
            }
            while(l <= r && f[i-w-1][q[r]] + q[r] * bp <= f[i-w-1][j] + j*bp){
                r--;
            }
            q[++r] = j;
            if(l <= r){
                f[i][j] = max(f[i][j], f[i-w-1][q[l]] + q[l] * bp - j * bp);
            }
        }
    }
    int ans = 0;
    for(int i = 0; i <= p; i++){
        ans = max(ans, f[t][i]);
    }
    printf("%d\n", ans);
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