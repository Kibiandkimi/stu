//
// Created by kibi on 23-7-31.
//
#include <bits/stdc++.h>
using namespace std;

const int N = 100000, K = 100, Mod = 100003;

void read(int&);

int main(){
    int n, k;
    read(n), read(k);

    static int f[N + 5];

    f[0] = 1;

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= min(k, i); j++){
            f[i] = (f[i] + f[i-j]) % Mod;
        }
    }

    printf("%d\n", f[n]);
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