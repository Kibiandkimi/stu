//
// Created by kibi on 2022/9/10.
//
#include <bits/stdc++.h>
using namespace std;
int n, a[500005], c[500005], b[500005];

void read(int &x);

int main(){
    read(n);
    for(int i = 1; i <= n; i++){
        read(a[i]);
        c[n-i+1] = a[i];
    }
    int r1 = 0, r2 = 1;
    for(int i = 1; i <= n; i++){
        read(b[i]);
        r1 += b[i]!=a[i], r2 += b[i]!=c[i];
    }
    printf("%d", min(r1, r2));
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
        if (c == '-'){
            w *= -1;
        }
        c = getchar();
    }
    while('0' <= c &&  c <= '9'){
        s = s*10 + c-'0';
        c = getchar();
    }
    x = s*w;
}