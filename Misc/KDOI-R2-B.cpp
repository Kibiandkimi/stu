//
// Created by kibi on 2022/10/23.
//
#include <bits/stdc++.h>
using namespace std;

void read(int &x);

int main(){
    const int mod = 998244353;
    int n, k;
    read(n), read(k);
    if(k == 1 || k == 2*n){
        printf("1");
    }else if(k == 2){
        if(n == 2){
            printf("2");
        }else {
            printf("1");
        }
    }else if(k == 3){
        printf("%d", (2 + n-1 + n-1)%mod);
    }else {
        for (int i = 1; i <= k; i++) {
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