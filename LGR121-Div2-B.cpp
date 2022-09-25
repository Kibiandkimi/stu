//
// Created by kibi on 2022/9/24.
//
#include <bits/stdc++.h>
using namespace std;
long long n, a[3000005], ans, mxp, mnp = 1e18, nowP, nowS;
bool flag[3000005];

void read(long long &x);

int main(){
    read(n);
    for(int i = 1; i <= n; i++){
        long long l, r;
        read(l), read(r);
        a[l]++, a[r+1]--;
        mnp = min(mnp, l);
        mxp = max(mxp, r+1);
        flag[l] = flag[r+1] = true;
    }
    for(int i = (int)mnp; i <= mxp; i++){
        if(!flag[i]){
            nowS++;
        }else{
            ans = max(ans, nowP * (nowS-1));
            nowS = 1;
            nowP += a[i];
        }
    }
    printf("%lld", ans);
}

void read(long long &x){
    long long s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
        if(c == '-'){
            w = -1;
        }
        c = getchar();
    }
    while('0'<=c && c<='9'){
        s = s*10 + c-'0';
        c = getchar();
    }
    x = s*w;
}