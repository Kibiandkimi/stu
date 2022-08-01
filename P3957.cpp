//
// Created by kibi on 2021/10/3.
//
#include <bits/stdc++.h>
using namespace std;
long long n,d,k,l,r,fr,ta;
long long dp[500005],a[500005],b[500005],q[500005];
bool check(long long x){
    long long l = max(d-x, (long long)1), r = d+x;
    for(long long i = 1; i <= n; i++){
        dp[i] = -1e18;
    }
    fr = ta = 0;
    dp[0] = 0;
    long long cur = 0;
    for(long long i = 1; i <= n; i++){
        for(; cur<i&&a[i]-a[cur]>=l;cur++){
            if(fr==ta){
                q[++ta] = cur;
            }else{
                while(fr<ta&&dp[cur]>=dp[q[ta]]){
                    ta--;
                }
                q[++ta] = cur;
            }
        }
        while(fr<ta&&a[i]-a[q[fr+1]]>r){
            fr++;
        }
        if(fr<ta){
            dp[i] = dp[q[fr+1]]+b[i];
        }else{
            dp[i] = -1e18;
        }
        if(dp[i]>=k){
            return 1;
        }
    }
    return 0;
}
int main(){
    scanf("%lld%lld%lld", &n, &d, &k);
    for(int i = 1; i <= n; i++){
        scanf("%lld %lld", &a[i], &b[i]);
    }
    l = 0, r = a[n];
    while(l<r){
        long long mid = (l+r)/2;
        if(check(mid)){
            r = mid;
        }else {
            l = mid + 1;
        }
    }
    if(!check(l)){
        printf("-1");
    }else{
        printf("%lld", l);
    }
}