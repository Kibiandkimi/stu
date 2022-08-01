//
// Created by kibi on 2022/6/24.
//

#include <bits/stdc++.h>
using namespace std;
//struct edge{
//    int next, to;
//}e[200005];
struct Node{
    long long sum, lazy, l, r, ls, rs;
}node[200005];
long long rt, n, m, r, cnt, a[100005], f[100005], d[100005], size[100005], son[100005], rk[100005], top[100005], id[100005];
long long mod;
vector<long long> e[200005];
void f1(long long fa, long long dep, long long u){
    d[u] = dep;
    f[u] = fa;
    size[u] = 1;
    long long sa = e[u].size();
    for(long long i = 0; i < sa; i++){
        if(e[u][i] == fa){
            continue;
        }
        f1(u, dep+1, e[u][i]);
        size[u] += size[e[u][i]];
        if(size[e[u][i]] > size[son[u]]){
            son[u] = e[u][i];
        }
    }
}
void f2(long long t, long long u){
    top[u] = t;
    id[u] = ++cnt;
    rk[cnt] = u;
    if(!son[u]){
        return ;
    }
    f2(t, son[u]);
    long long sa = e[u].size();
    for(long long i = 0; i < sa; i++){
        if(e[u][i]!=son[u] && e[u][i]!=f[u]){
            f2(e[u][i], e[u][i]);
        }
    }
}

void push_up(long long p){
    node[p].sum = (node[node[p].ls].sum + node[node[p].rs].sum + node[p].lazy * (node[p].r - node[p].l + 1)) % mod;
}
void build(long long l, long long r, long long p){
    if(l == r){
        node[p].l = node[p].r = l;
        node[p].sum = a[rk[l]];
    }else {
        long long mid = (l+r)/2;
        node[p].ls = cnt++;
        node[p].rs = cnt++;
        build(l, mid, node[p].ls);
        build(mid + 1, r, node[p].rs);
        //        tr[p] = tr[p*2] + tr[p*2 + 1];
        node[p].l = node[node[p].ls].l;
        node[p].r = node[node[p].rs].r;
        push_up(p);
    }
}
long long query(long long l, long long r, long long p){
    if(node[p].l>=l && node[p].r<=r){
        return node[p].sum;
    }
    long long s = (node[p].lazy*(min(node[p].r, r) - max(node[p].l,l) + 1))%mod;
    long long mid = (node[p].l + node[p].r) / 2;
    if(l <= mid){
        s = (s + query(l, r, node[p].ls)) % mod;
    }
    if(mid < r){
        s = (s + query(l, r, node[p].rs)) % mod;
    }
    return s;

}
void update(long long l, long long r, long long p, long long k) {
    if(node[p].l >= l && node[p].r <= r){
        node[p].sum = (node[p].sum + (node[p].r-node[p].l+1) * k) % mod;
        node[p].lazy = (node[p].lazy + k) % mod;
    }else{
        long long mid = (node[p].l + node[p].r) / 2;
        if(l <= mid){
            update(l, r, node[p].ls, k);
        }
        if(mid < r){
            update(l, r, node[p].rs, k);
        }
        push_up(p);
    }
}

long long sum_l(long long x, long long y){
    long long ans = 0, fx = top[x], fy = top[y];
    while(fx != fy){
        if(d[fx]>=d[fy]){
            ans = (ans + query(id[fx], id[x], rt)) % mod;
            x = f[fx], fx = top[x];
        }else{
            ans = (ans + query(id[fy], id[y], rt)) % mod;
            y = f[fy], fy = top[y];
        }
    }
    if(id[x] <= id[y]){
        ans = (ans + query(id[x], id[y], rt)) % mod;
    }else{
        ans = (ans + query(id[y], id[x], rt)) % mod;
    }
    return ans%mod;
}
void update_l(long long x, long long y, long long k){
    long long fx = top[x], fy = top[y];
    while(fx != fy){
        if(d[fx] >= d[fy]){
            update(id[fx], id[x], rt, k);
            x = f[fx], fx = top[x];
        }else{
            update(id[fy], id[y], rt, k);
            y = f[fy], fy = top[y];
        }
    }
    if(id[x] <= id[y]){
        update(id[x], id[y], rt, k);
    }else{
        update(id[y], id[x], rt, k);
    }
}

int main(){
    scanf("%d %d %d %d", &n, &m, &r, &mod);
    for(long long i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }
    for(long long i = 1; i < n; i++){
        long long x, y;
        scanf("%d %d", &x, &y);
        e[x].push_back(y);
        e[y].push_back(x);
    }
    cnt = 0;
    f1(0, 1, r);
    f2(r, r);
    cnt = 0;
    rt = cnt++;
    build(1, n, rt);
    for(long long i = 1; i <= m; i++){
        long long op, x, y, z;
        scanf("%lld", &op);
        if(op == 1){
            scanf("%lld %lld %lld", &x, &y, &z);
            update_l(x, y, z%mod);
        }else if(op == 2){
            scanf("%lld %lld", &x, &y);
            printf("%lld\n", sum_l(x, y)%mod);
        }else if(op == 3){
            scanf("%lld %lld", &x, &z);
            update(id[x], id[x]+size[x]-1, rt, z%mod);
        }else if(op == 4){
            scanf("%lld", &x);
            printf("%lld\n", query(id[x], id[x]+size[x]-1, rt)%mod);
        }
    }

}