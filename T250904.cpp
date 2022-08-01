//
// Created by kibi on 2022/7/17.
//
//5pts
#include <bits/stdc++.h>
int T, r, k;
long long ans;
long long a[1000005];
long long mod = 1e9+7;
long long f(long long x){
    if(x == 0){
        return 0;
    }
    if(x == 1){
        return 1;
    }
    if(a[x]){
        return a[x];
    }
    if(x%2==0){
        a[x] = 2*f(x/2)%mod;
    }else{
        a[x] = (2*f((x-1)/2) + 2*f((x-1)/2)/(x-1) + x) % mod;
    }
    return a[x];
}
long long p(long long x){
    if(!k){
        return 1;
    }
    long long s1 = x, s2 = 1, kk = k;
    while(kk != 1){
        if(kk%2){
            s2 = (s2 * x) % mod;
            kk--;
        }else{
            s1 = (s1 * s1) % mod;
            kk/=2;
        }
    }
    return (s1*s2)%mod;
}
int main(){
    scanf("%d", &T);
    while(T--){
        ans = 0;
        scanf("%d %d", &r, &k);
        for(int i = 0; i <= r; i++){
            ans = (ans+p(f(i)))%mod;
        }
        printf("%lld\n", ans);
    }
}