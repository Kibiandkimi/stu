//
// Created by kibi on 2022/10/15.
//
#include <bits/stdc++.h>
using namespace std;
const int mod = 1000033;
void read(int &x);

int main(){
    int n, t;
    read(n), read(t);
    if(n == 1){
        printf("0");
    }else if(t == 4) {
        printf("-1");
    }else if(t == 3){
        printf("%d", (n-1)%mod);
    }else if(t == 2){
        printf("-1");
    }else if(t == 5){
        printf("%d", ((n+2)*(n-1)/2)%mod);
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