//
// Created by kibi on 2021/8/23.
//
#include <bits/stdc++.h>
using namespace std;
long long n,m,tr[500005];
int lowbit(int x){return x & -x;}
void add(int x, long long num){
    while(x <= n){
        tr[x] += num;
        x += lowbit(x);
    }
    return;
}
long long query(int x){
    long long ans = 0;
    while(x){
        ans += tr[x];
        x-=lowbit(x);
    }
    return ans;
}
int main(){
    cin >> n >> m;
    int l = 0,t;
    for(int i = 1; i <= n; i++){
        scanf("%d", &t);
        add(i, t-l);
        l = t;
    }
    int fl;
    while(m--){
        scanf("%d", &fl);
        if(fl==1){
            int l,r,t;
            scanf("%d %d %d", &l, &r, &t);
            add(l, t);
            add(r+1, -t);
        }else{
            int t;
            scanf("%d", &t);
            printf("%lld\n", query(t));
        }
    }
}