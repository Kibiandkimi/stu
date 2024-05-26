//
// Created by kibi on 2021/8/23.
//
#include <bits/stdc++.h>
using namespace std;
#define ll long long
struct node{
    ll l,r;
    ll j;
    ll c;
    ll s;
}t[300005];
ll a[300005];
ll p;
ll n,m,l,r,x,fl;
void build(ll l, ll r, ll x){
    t[x].l = l;
    t[x].r = r;
    t[x].j = 0;
    t[x].c = 1;
    if(l==r){
        t[x].s = a[l];
        return;
    }
    ll mid = (l+r)/2;
    build(l, mid, x*2);
    build(mid+1, r, x*2+1);
    t[x].s = t[x*2].s + t[x*2+1].s;
    return;
}
void pushdown(ll x){
    t[x*2].j = (t[x*2].j*t[x].c+t[x].j)%p;
    t[x*2+1].j = (t[x*2+1].j*t[x].c+t[x].j)%p;
    t[x*2].c = (t[x*2].c*t[x].c)%p;
    t[x*2+1].c = (t[x*2+1].c*t[x].c)%p;
    t[x*2].s = (((t[x*2].r-t[x*2].l+1)*t[x].j)%p+(t[x*2].s*t[x].c)%p)%p;
    t[x*2+1].s = (((t[x*2+1].r-t[x*2+1].l+1)*t[x].j)%p+(t[x*2+1].s*t[x].c)%p)%p;
    t[x].j = 0;
    t[x].c = 1;
    return;
}
void c(ll l, ll r, ll x, ll s){
    if(l<=t[x].l&&t[x].r<=r){
        t[x].s = t[x].s*s%p;
        t[x].j = t[x].j*s%p;
        t[x].c = t[x].c*s%p;
        return;
    }else{
        pushdown(x);
        ll mid = (t[x].l+t[x].r)/2;
        if(l<=mid)c(l,r,x*2,s);
        if(mid<r)c(l,r,x*2+1,s);
        t[x].s = (t[x*2].s+t[x*2+1].s)%p;
    }
    return;
}
void j(ll l, ll r, ll x, ll s){
    if(l <= t[x].l&&t[x].r <= r){
        t[x].j = (t[x].j + s)%p;
        t[x].s = (t[x].s + s*(t[x].r - t[x].l + 1)%p)%p;
        return;
    }else{
        pushdown(x);
        ll mid = (t[x].l+t[x].r)/2;
        if(l <= mid)j(l, r, x*2, s);
        if(mid < r)j(l, r, x*2+1, s);
        t[x].s = (t[x*2].s + t[x*2+1].s)%p;
        return;
    }
}
ll query(ll l, ll r, ll x){
    if(l <= t[x].l && t[x].r <= r){
        return t[x].s%p;
    }
    pushdown(x);
    ll mid = (t[x].l+t[x].r)/2, s = 0;
    if(l <= mid)s=query(l, r, x*2)%p;
    if(mid < r)s=s + query(l, r, x*2+1);
    return s%p;

}
int main(){
    cin >> n >> m >> p;
    for(int i = 1; i <= n; i++)scanf("%lld", &a[i]);
    build(1, n, 1);
    while(m--){
        scanf("%d", &fl);
        if(fl == 1){
            //            int l,r,s;
            scanf("%d %d %d", &l, &r, &x);
            c(l, r, 1, x);
        }else if(fl == 2){
            //            int l,r,s;
            scanf("%d %d %d", &l, &r, &x);
            j(l, r, 1, x);
        }else{
            //            int l,r;
            scanf("%d %d", &l, &r);
            printf("%lld\n", query(l, r, 1));
        }
    }
    return 0;
}