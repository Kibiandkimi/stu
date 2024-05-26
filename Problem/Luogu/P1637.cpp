//
// Created by kibi on 2022/8/4.
//
#include <bits/stdc++.h>
using namespace std;
long long n, a[30005], s[30005], f[4][30005], c[60005], ans, m;

long long val(long long x){
    return lower_bound(s+1, s+m+1, x)-s;
}

long long ask(long long x){
    long long res = 0;
    for(; x; x -= (x&(-x))){
        res += c[x];
    }
    return res;
}

void add(long long x, long long v){
    for(; x <= m; x += (x&(-x))){
        c[x] += v;
    }
}

int main(){
    scanf("%lld", &n);
    for(int i = 1; i <= n; i++){
        scanf("%lld", &a[i]);
        s[i] = a[i];
    }
    sort(s+1, s+n+1);
    m = unique(s+1, s+1+n) - s - 1;
    for(int i = 1; i <= n; i++){
        f[1][i] = 1;
        a[i] = val(a[i]);
    }
    for(int i = 2; i <= 3; i++){
        memset(c, 0, sizeof c);
        for(int j = 1; j <= n; j++){
            f[i][j] = ask(a[j]-1);
            add(a[j], f[i-1][j]);
        }
    }
    for(int i = 1; i <= n; i++){
        ans += f[3][i];
    }
    printf("%lld", ans);
}