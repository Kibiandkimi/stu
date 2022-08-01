//
// Created by kibi on 2021/10/13.
//
#include <bits/stdc++.h>
using namespace std;
struct node{
    int v,w,g;
};
struct pr{
    int t,x,s;
    bool operator < (const pr &b) const{
        return this->t<b.t;
    }
    bool operator > (const pr &b) const{
        return this->t>b.t;
    }
    bool operator <= (const pr &b) const{
        return this->t<=b.t;
    }
    bool operator >= (const pr &b) const{
        return this->t>=b.t;
    }
};
int d[205][(1<<14)], vis[205][(1<<14)];
int n,m,p,k,ans;
priority_queue<pr> q;
vector<node> a[205];
int j[205];
int f(){
    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= (1<<p); j++){
            d[i][j] = 1e9;
        }
    }
    q.push({0,1,0});
    while(!q.empty()){
        int t = -q.top().t, x = q.top().x, s = q.top().s;
        q.pop();
        if(x == n){
            return t;
        }
        if(vis[x][s]){
            continue;
        }
        vis[x][s] = 1;
        int sa = a[x].size();
        for(int i = 0; i < sa; i++){
            if((d[a[x][i].v][s|j[x]]>a[x][i].w+t)&&((a[x][i].g&(s|j[x]))==a[x][i].g)){
                d[a[x][i].v][s|j[x]] = a[x][i].w+t;
                q.push({-(a[x][i].w+t), a[x][i].v, s|j[x]});
            }
        }
    }
    return -1;
}
//int f(int x, int g){
//    if(x == n){
//        return 0;
//    }
//    int sa = a[x].size(), mn = 1e9;
//    for(int i = 0; i < sa; i++){
//        if((!vis[a[x][i].v])&&((a[x][i].g&(g|j[x]))==a[x][i].g)){
//            vis[a[x][i].v] = 1;
//            mn = min(mn, f(a[x][i].v, g|j[x]) + a[x][i].w);
//            vis[a[x][i].v] = 0;
//        }
//    }
//    return mn;
//}
int main(){
    scanf("%d %d %d %d", &n, &m, &p, &k);
    for(int i = 1; i <= k; i++){
        int d, t;
        scanf("%d %d", &d, &t);
        for(int tj = 1; tj <= t; tj++){
            // int p;
            int tt;
            scanf("%d", &tt);
            // p = (1<<(tt-1));
            j[d] |= (1<<(tt-1));
        }
    }
    for(int i = 1; i <= m; i++){
        int u,v,w,s,d = 0;
        scanf("%d %d %d %d", &u, &v, &w, &s);
        for(int j = 1; j <= s; j++){
            int t;
            scanf("%d", &t);
            d |= (1<<(t-1));
        }
        a[u].push_back({v,w,d});
        a[v].push_back({u,w,d});
    }
    printf("%d", f());
    //    int as = f(1, 0);
    //    if(as == 1e9){
    //        printf("-1");
    //    }else{
    //        printf("%d", as);
    //    }
}