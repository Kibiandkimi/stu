//
// Created by kibi on 2022/10/14.
//
#include <bits/stdc++.h>
using namespace std;

int tr[4000005];

void read(int &x);

int main(){
    static int T;
    read(T);
    while(T--){
        static int n, mod, siz;
        read(n), read(mod);
        siz = 1;
        while(siz <= n){
            siz <<= 2;
        }
        fill(tr+1, tr+siz+n+2, 1);
        for(int i = 1; i <= n; i++){
            static int a, b, p;
            read(a), read(b);
            if(a == 1){
                p = i + siz;
                tr[p] = b % mod;
            }else{
                p = b + siz;
                tr[p] = 1;
            }
            while(p >>= 1){
                tr[p] = (int)((long long)tr[p << 1] * tr[p << 1 | 1] % mod);
            }
            printf("%d\n", tr[1]);
        }
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