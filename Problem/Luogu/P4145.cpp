//
// Created by kibi on 2021/8/25.
//
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll n,m,a[100005];
struct node{
    ll l,r,f,s;
};
node tr[400005];
void build(ll l, ll r, ll x){
    tr[x].l = l;
    tr[x].r = r;
    if(l == r){
        tr[x].f = a[l]==1;
        tr[x].s = a[l];
        return;
    }
    ll mid = (l+r)/2;
    build(l, mid, x*2);
    build(mid+1, r, x*2+1);
    tr[x].f = tr[x*2].f&&tr[x*2+1].f;
    tr[x].s = tr[x*2].s+tr[x*2+1].s;
}
void ch(ll l, ll r, ll x){
    if(tr[x].f)return;
    if(tr[x].l==tr[x].r){
        tr[x].s = sqrt(tr[x].s);
        tr[x].f = tr[x].s==1;
        return;
    }
    ll mid = (tr[x].l+tr[x].r)/2;
    if(r<=mid){
        ch(l, r, x*2);
    }else if(l > mid){
        ch(l, r, x*2+1);
    }else{
        ch(l, mid, x*2);
        ch(mid+1, r, x*2+1);
    }
    tr[x].s = tr[x*2].s+tr[x*2+1].s;
    tr[x].f = tr[x*2].f&&tr[x*2+1].f;
}
ll query(ll l, ll r, ll x){
    if(tr[x].l == tr[x].r){
        return tr[x].s;
    }
    if(l<=tr[x].l&&tr[x].r<=r){
        return tr[x].s;
    }
    ll mid = (tr[x].l+tr[x].r)/2;
    if(l > mid){
        return query(l, r, x*2+1);
    }else if(r <= mid){
        return query(l, r, x*2);
    }
    return query(l,r,x*2)+query(l,r,x*2+1);
}
int main(){
    cin >> n;
    for(ll i = 1; i <= n; i++){
        scanf("%lld", &a[i]);
    }
    build(1,n,1);
    cin >> m;
    for(ll i = 1; i <= m; i++){
        ll k,t1,t2;
        scanf("%lld %lld %lld", &k, &t1, &t2);
        int l = min(t1,t2), r = max(t1, t2);
        if(k){
            printf("%lld\n", query(l,r,1));
        }else{
            ch(l,r,1);
        }
    }
}