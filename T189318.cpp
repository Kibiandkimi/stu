//
// Created by kibi on 2021/8/3.
//
#include <bits/stdc++.h>
using namespace std;
long long n, k,f1[305],f2[305];
const long long MOD = 998244353;
int qPow(int a, int b){
    int ss = 1;
    while(b){
        if(b%2){
            ss=(long long)ss*a%MOD;
        }
        a=(long long)a*a%MOD;
        b/=2;
    }
    return ss;
}
int main(){
    cin >> n >> k;
    f1[0] = 1;
    f2[0] = 1;
    for(int i = 1; i <= n; i++){
        int x;
        scanf("%d", &x);
        for(int j = 1; j <= k; j++){
            f1[j] = (f1[j]+f1[j-1])%MOD;
            f2[j] = (f2[j]+(long long)x*f2[j-1])%MOD;
        }
    }
    printf("%lld", (long long)f2[k] * qPow(f1[k], MOD-2)%MOD);
    return 0;
}