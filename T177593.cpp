//
// Created by kibi on 22-8-14.
//
#include <bits/stdc++.h>
using namespace std;
int n;
int a[10000005];
int b[10000005];
int qz[10000005];
int mod = 1e9+7;

int main(){
    scanf("%d", &n);
    b[0] = 1;
    qz[0] = 1;
    for(int i = 1; i <= n; i++){
        b[i] = (b[i-1]*2)%mod;
        qz[i] = (qz[i-1]+b[i])%mod;
    }
    a[1] = 1;
    for(int i = 2; i <= n; i++){
        a[i] = (int)(((long long)a[i-1]*qz[i-1])%mod);
    }
    printf("%d", a[n]);
}