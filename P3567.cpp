//
// Created by kibi on 22-8-12.
//
#include <bits/stdc++.h>
using namespace std;
int n, m, q, cnt = 1;
int t[500005];
int a[500005], b[500005];
struct node{
    int l, r, ls, rs, v;
}tr[500005<<4];

void build(int l, int r, int u){
    tr[u].l = l, tr[u].r = r;
    if(l == r){
        return ;
    }
    int mid = (l+r)/2;
    tr[u].ls = ++cnt;
    tr[u].rs = ++cnt;
    build(l, mid, tr[u].ls);
    build(mid + 1, r, tr[u].rs);
}

int update(int l, int r, int v, int u){
    int p = ++cnt;
    tr[p] = tr[u];
    tr[p].v++;
    if(tr[u].l == tr[u].r){
        return p;
    }
    int mid = (tr[u].l+tr[u].r)/2;
    if(v <= mid){
        tr[p].ls = update(l, r, v, tr[u].ls);
    }else{
        tr[p].rs = update(l, r, v, tr[u].rs);
    }
    return p;
}

int query(int v, int l, int r, int k, int u){
    if(tr[u].l == tr[u].r){
        return tr[u].l;
    }
    int l1 = tr[tr[v].ls].v - tr[tr[u].ls].v, r1 = tr[tr[v].rs].v - tr[tr[u].rs].v;
    int mid = (tr[u].l+tr[u].r)/2;
    if(l1 > k){
        return query(tr[v].ls, l, r, k, tr[u].ls);
    }
    if(r1 > k){
        return query(tr[v].rs, l, r, k, tr[u].rs);
    }
    return 0;
}

int main(){
    scanf("%d %d", &n, &q);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    sort(b+1, b+1+n);
    t[0] = 1;
    m = unique(b+1, b+1+n) - b - 1;
    build(1, m, 1);
    for(int i = 1; i <= n; i++){
        int l = lower_bound(b+1, b+m+1, a[i])-b;
        t[i] = update(1, m, l, t[i-1]);
    }
    while(q--){
        int t1, t2;
        scanf("%d %d", &t1, &t2);
        printf("%d\n", b[query(t[t2], 1, m, (t2-t1+1)/2, t[t1-1])]);
    }
}