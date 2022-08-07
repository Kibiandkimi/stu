//
// Created by kibi on 2022/8/7.
//
#include <bits/stdc++.h>
using namespace std;
long long n, a[100005];
long long mn = 1e9;
long long ans = 1;
const long long mod = 1000000007;

int main(){
    scanf("%lld", &n);
    for(int i = 1; i <= n; i++){
        scanf("%lld", &a[i]);
        mn = min(mn, a[i]);
        //        mx = max(mx, a[i]);
    }
    for(int i = 1; i <= n; i++){
        ans = (ans*(a[i]/mn))%mod;
    }
    printf("%lld %lld", mn, ans);

}