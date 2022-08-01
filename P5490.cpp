//
// Created by kibi on 2021/8/24.
//
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int n;
struct node{
    ll y1,y2,x,f;
};
struct seg{
    ll l,r,sum,len;
};
node a[1000005];
seg tr[4000005];
ll d[1000005];
bool cmp(node a, node b){
    return a.x<b.x;
}
void build(ll x, ll l, ll r){
    tr[x].l = l;
    tr[x].r = r;
    tr[x].sum = tr[x].len = 0;
    if(l == r)return;
    ll mid = (l+r)/2;
    build(x<<1, l, mid);
    build(x<<1|1, mid+1, r);
}
void pushup(ll x){
    int l = tr[x].l, r = tr[x].r;
    if(tr[x].sum){
        tr[x].len = d[r+1] - d[l];
    }else{
        tr[x].len = tr[x*2].len + tr[x*2+1].len;
    }
}
void change(ll x, ll l, ll r, ll c){
    if(d[tr[x].r+1] <= l||r <= d[tr[x].l]){
        return;
    }
    if(l <= d[tr[x].l] && d[tr[x].r+1] <= r){
        tr[x].sum += c;
        pushup(x);
        return;
    }
    change(x*2, l, r, c);
    change(x*2+1, l, r, c);
    pushup(x);
}
int main(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        int x1,x2,y1,y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        d[i*2-1] = y1;
        d[i*2] = y2;
        a[i*2-1] = {y1,y2,x1,1};
        a[i*2] = {y1,y2,x2,-1};
    }
    sort(a+1, a+1+2*n, cmp);
    sort(d +1, d +1+2*n);
    ll to = unique(d+1, d+2*n+1) - d - 1;
    n*=2;
    build(1, 1, to-1);
    ll ans = 0;
    for(int i = 1; i < n; i++){
        change(1, a[i].y1, a[i].y2, a[i].f);
        ans += tr[1].len * (a[i+1].x - a[i].x);
    }
    printf("%lld", ans);
}