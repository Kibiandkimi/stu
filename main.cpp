#include <bits/stdc++.h>
using namespace std;
int n, m;
const int mod = 998244353;
struct node{
    int l, r, ls, rs, v;
}tr[4000005];
struct island{
    int l, r, h;
}is[500005];

bool cmp(island a, island b){
    return a.h > b.h;
}

int a[500005];
void build(int u, int l, int r){
    tr[u].l = l, tr[u].r = r;
    if(l == r){
        tr[u].v = a[l];
        return ;
    }
    int mid = (l+r)/2;
    build(u*2, l, mid);
    build(u*2+1, mid+1, r);
    tr[u].v = tr[tr[u].ls = u*2].v + tr[tr[u].rs = u*2+1].v;
}

int query(int u, int l, int r){
    if(l<=tr[u].l&&tr[u].r<=r){
        return tr[u].v % mod;
    }
    int ans = 0;
    if(l<=tr[tr[u].ls].r){
        ans = (ans+query(tr[u].ls, l, r))%mod;
    }
    if(r>=tr[tr[u].rs].l){
        ans = (ans+query(tr[u].rs, l, r))%mod;
    }
    return ans % mod;
}

void add(int u, int x, int v){
    tr[u].v = (tr[u].v + v) % mod;
    if(tr[u].l == tr[u].r){
        return;
    }
    if(x <= tr[tr[u].ls].r){
        add(tr[u].ls, x, v);
    }else{
        add(tr[u].rs, x, v);
    }
}

void clear(int u, int l, int r){
    if(tr[u].l == tr[u].r){
        tr[u].v = 0;
        return ;
    }
    if(l<=tr[tr[u].ls].r){
        clear(tr[u].ls, l, r);
    }
    if(r>=tr[tr[u].rs].l){
        clear(tr[u].rs, l, r);
    }
    tr[u].v = tr[tr[u].ls].v + tr[tr[u].rs].v;
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= m; i++){
        int l, r, h;
        scanf("%d %d %d", &l ,&r, &h);
        is[i].l = l, is[i].r = r, is[i].h = h;
    }
    sort(is+1, is+1+m, cmp);

    for(int i = 1; i <= n; i++){
        int t;
        scanf("%d", &t);
        a[t]++;
    }
    build(1, 1, 500005);

    queue<pair<pair<int, int>, int> > q;
    int last = -1;
    for(int i = 1; i <= m; i++){
        if(last != is[i].h){
            while(!q.empty()){
                auto u = q.front();
                q.pop();
                add(1, u.first.first, u.second);
                add(1, u.first.second, u.second);
            }
        }
        int v = query(1, is[i].l, is[i].r);
        clear(1, is[i].l, is[i].r);
        q.push({{is[i].l, is[i].r}, v});
//        q.push();
    }
    while(!q.empty()){
        auto u = q.front();
        q.pop();
        add(1, u.first.first, u.second);
        add(1, u.first.second, u.second);
    }
    printf("%d", query(1, 1, 500005));

}