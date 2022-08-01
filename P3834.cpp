//
// Created by kibi on 2021/10/19.
//
#include <bits/stdc++.h>
using namespace std;
int n,q,m,cnt;
int a[200005],b[200005];
int t[200005];
int sum[200005<<5], l[(200005<<5)], r[(200005<<5)];
int build(int tl, int tr){
    int p = ++cnt;
    sum[p] = 0;
    if(tl < tr){
        int mid = (tl+tr)/2;
        l[p] = build(tl, mid);
        r[p] = build(mid+1, tr);
    }
    return p;
}
int update(int pre, int tl, int tr, int x){
    int p = ++cnt;
    l[p] = l[pre];
    r[p] = r[pre];
    sum[p] = sum[pre] + 1;
    if(tl < tr){
        int mid = (tl + tr) / 2;
        if(x <= mid){
            l[p] = update(l[pre], tl, mid, x);
        }else{
            r[p] = update(r[pre], mid + 1, tr, x);
        }
    }
    return p;
}
int query(int u, int v, int tl, int tr, int k){
    if(tl >= tr){
        return tl;
    }
    int mid = (tl + tr)/2, tem = sum[l[v]] - sum[l[u]];
    if(tem>=k){
        return query(l[u], l[v], tl, mid, k);
    }else{
        return query(r[u], r[v], mid+1, tr, k-tem);
    }
}
int main(){
    scanf("%d %d", &n, &q);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    sort(b+1, b+1+n);
    m = unique(b+1, b+1+n)-b-1;
    t[0] = build(1, m);
    for(int i = 1; i <= n; i++){
        int tem = lower_bound(b+1, b+1+m, a[i])-b;
        t[i] = update(t[i-1], 1, m, tem);
    }
    for(int i = 1; i <= q; i++){
        int l, r, k;
        scanf("%d %d %d", &l, &r, &k);
        int tem = query(t[l-1], t[r], 1, m, k);
        printf("%d\n", b[tem]);
    }
}
// 2022/6/26
//可持久化权值线段树，主席树
/*
#include <bits/stdc++.h>
using namespace std;
struct Node{
    int ls, rs, l, r, sum;
}node[4000005];
int a[200005], n, m, t[200005], size[4000005], cnt, rt, root[200005];

int f(int l, int r, int x){
    int mid = (l+r)/2;
    if(t[mid] < x){
        return f(mid+1, r, x);
    }else if(t[mid] > x){
        return f(l, mid-1, x);
    }else{
        return mid;
    }
}

void build(int l, int r, int cur){
    if(l == r){
        //        node[cur].sum = a[i];
        node[cur].l = node[cur].r = l;
        node[cur].sum = 0;
        return ;
    }
    int mid = (l+r)/2;
    node[cur].ls = cnt++;
    node[cur].rs = cnt++;
    build(l, mid, node[cur].ls);
    build(mid + 1, r, node[cur].rs);
    node[cur].l = node[node[cur].ls].l;
    node[cur].r = node[node[cur].rs].r;
}
void update(int cur, int x){
    node[cnt] = node[cur];
    cur = cnt;
    if(node[cur].l == node[cur].r){
        node[cur].sum++;
        return ;
    }
    int mid = (node[cur].l+node[cur].r)/2;
    if(x <= mid){
        int ls = node[cur].ls;
        node[cur].ls = ++cnt;
        update(ls, x);
    }else{
        int rs = node[cur].rs;
        node[cur].rs = ++cnt;
        update(rs, x);
    }
    node[cur].sum = node[node[cur].ls].sum + node[node[cur].rs].sum;
}
int query(int l, int r, int k){
    if(node[r].l == node[r].r){
        return t[node[r].l];
    }
    //    int mid = (node[r].l+node[r].r) / 2;
    int num = node[node[r].ls].sum - node[node[l].ls].sum;
    if(k<=num){
        return query(node[l].ls, node[r].ls, k);
    }else{
        return query(node[l].rs, node[r].rs, k-num);
    }
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
        t[i] = a[i];
    }
    sort(t+1, t+n+1);
    size[0] = unique(t+1, t+n+1) - t - 1;
    rt = cnt++;
    root[0] = rt;
    build(1, size[0], rt);
    for(int i = 1; i <= n; i++){
        int x = f(1, size[0], a[i]);
        root[i] = ++cnt;
        update(root[i-1], x);
    }
    while(m--){
        int l, r, k;
        scanf("%d %d %d", &l, &r, &k);
        printf("%d\n", query(root[l-1], root[r], k));
    }
}
*/