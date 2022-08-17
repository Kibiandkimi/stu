//
// Created by kibi on 22-8-14.
//
#include <bits/stdc++.h>
using namespace std;
long long n, c, a[1000005], t[1000005];
long long mx;

int tr[4005];

void insert(int x){
    for(;x<=mx;x+=(x&-x)){
        tr[x]++;
    }
}

int query(int x){
    int res = 0;
    for(;x>=0;x-=(x&-x)){
        res += tr[x];
        if(!x){
            break;
        }
    }
    return res;
}

int main(){
    scanf("%lld %lld", &n, &c);
    mx = c;
    if(!c){
        printf("0");
        return 0;
    }
    bool flag = false;
    for(int i = 1; i <= n; i++){
        scanf("%lld", &a[i]);
        mx = max(a[i], mx);
        if(a[i] < a[i-1]){
            flag = true;
        }
    }
    if(!flag) {
        long long ans = 1e18;
        t[1] = c * (n - 1);
        for (int i = 2; i <= n; i++) {
//        if((a[i]-a[i-1])*(i-1) < c){
//            t[i] = t[i-1] + (a[i]-a[i-1])*(i-1);
//            ans = min(ans, t[i]);
//        }
            t[i] = t[i - 1] + (a[i] - a[i - 1]) * (i - 1) - c;
            ans = min(ans, t[i]);
        }
        printf("%lld", ans);
    }else if(mx < 105){
        int sm[100005], um[100005], uum[100005], downs[100005], last_down = 1e8;
//        for(int i = 1; i <= n; i++){
//            sa[i] = a[i];
//        }
        for(int i = 1; i <= n; i++){
            insert((int)a[i]);
            uum[i] = um[a[i]];
            um[a[i]]++;
            if(a[i] <= last_down){
                downs[i+1] = downs[i]+1;
            }
        }
        for(int i = 1; i <= mx; i++){
            sm[i] = query((int)i-1);
        }
        long long res = 0, ans = 1e18;
        int d = (int)mx, ld = 1;
//        for(int i = 0; i <= mx; i++){
//            res = 0;
//        ans = min(ans, res);
//        }
        while(d>0 && sm[d]>um[d]*c){
            d--;
        }
//        for(int i = 2; i <= n; i++){
//            if(d>a[i]){
//                while(d>0&&(i-ld+sm[ld]-sm[i]-uum[i]-(downs[i]-downs[ld]))*c<)
//
//            }
//        }
        for(int j = 1; j <= n; j++){
            res += a[j]>d?c:d-a[j];
        }
        printf("%lld", ans);
    }else{

    }
}