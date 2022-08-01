//
// Created by kibi on 2021/7/28.
//
#include <bits/stdc++.h>
using namespace std;
const int mo = 1000000007;
int t,n,m;
long long jc[1000005], d[1000005], inv[1000005];
long long f(int x){
    if(d[x]){
        return d[x];
    }
    d[x] = ((x-1)*f(x-1)%mo+(x-1)*f(x-2)%mo)%mo;
    return d[x];
}
long long q(long long a, long long b){
    long long s = 1;
    while(b){
        if(b%2){
            s=a*s%mo;
        }
        a=a*a%mo;
        b/=2;
    }
    return s;
}
int main(){
    d[2] = 1;
    jc[1] = 1;
    inv[1] = 1;
    for(int i = 2; i <= 1000000; i++){
        jc[i] = (jc[i-1]*i)%mo;
        inv[i] = q(jc[i], mo-2);
    }
    cin >> t;
    for(int i = 1; i <= t; i++){
        scanf("%d %d", &n, &m);
        if(n-m==1){
            printf("0\n");
        }else if(n==m){
            printf("1\n");
        }else if(m==0){
            printf("%lld\n", f(n)%mo);
        }else {
            long long sum;
            sum = ((jc[n] * inv[n - m] % mo) * inv[m] % mo) * f(n - m) % mo;
            printf("%lld\n", sum);
        }
    }
}