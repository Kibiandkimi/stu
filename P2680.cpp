//
// Created by kibi on 2021/8/30.
//
#include <bits/stdc++.h>
using namespace std;
int n, m, mxl, ans, num, ret, b[300005], d[300005], ta[300005], vis[300005], s[300005];
struct node{
    int v,w;
};
struct leng{
    int l,u,v,lca;
}len[300005];
vector<node> a[300005];
vector<node> q[300005];
int find(int x){
    if(b[x]!=x){
        b[x] = find(b[x]);
    }
    return b[x];
}
void tarjan(int u, int pre){
    int sa = a[u].size();
    for(int i = 0; i < sa; i++){
        int v = a[u][i].v;
        if(v == pre)continue;
        d[v] = d[u]+a[u][i].w;
        tarjan(v, u);
        ta[v] = a[u][i].w;
        int f1 = find(v), f2 = find(u);
        if(f1 != f2){
            b[f1] = find(f2);
        }
        vis[v] = 1;
    }
    int sq = q[u].size();
    for(int i = 0; i < sq; i++){
        if(vis[q[u][i].v]){
            int p = q[u][i].w;
            len[p].lca = find(q[u][i].v);
            len[p].l = d[u] + d[q[u][i].v] - 2*d[len[p].lca];
            mxl = max(mxl, len[p].l);
        }
    }
}
void f(int u, int pre){
    int sa = a[u].size();
    for(int i = 0; i < sa; i++){
        int v = a[u][i].v;
        if(v==pre)continue;
        f(v, u);
        s[u] += s[v];
    }
    if(s[u]==num&&ta[u]>ret){
        ret = ta[u];
    }
}
bool check(int x){
    memset(s, 0, sizeof(s));
    num = ret = 0;
    for(int i = 1; i <= m; i++){
        if(len[i].l > x){
            s[len[i].u]++;
            s[len[i].v]++;
            s[len[i].lca]-=2;
            num++;
        }
    }
    f(1, 0);
    if(mxl-ret>x){
        return 0;
    }
    return 1;
}
int main(){
    cin >> n >> m;
    for(int i = 1; i < n; i++){
        int u,v,w;
        scanf("%d %d %d", &u, &v, &w);
        a[u].push_back({v,w});
        a[v].push_back({u,w});
    }
    for(int i = 1; i <= n; i++){
        b[i] = i;
    }
    for(int i = 1; i <= m; i++){
        int u,v;
        scanf("%d %d", &u, &v);
        q[u].push_back({v,i});
        q[v].push_back({u,i});
        len[i].u = u;
        len[i].v = v;
    }
    tarjan(1, 0);
    int l = 0, r = mxl, mid;
    while(l <= r){
        mid = (l+r)/2;
        if(check(mid)){
            r = mid-1;
            ans = mid;
        }else{
            l = mid+1;
        }
    }
    cout << ans;
}
