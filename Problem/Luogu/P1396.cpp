//
// Created by kibi on 2021/10/5.
//
#include <bits/stdc++.h>
using namespace std;
int n,m,s,t;
priority_queue< pair<int, int> > q;
int vis[10005],dis[10005];
struct node{
    int s,w;
};
vector<node> a[10005];
int main(){
    scanf("%d %d %d %d", &n, &m, &s, &t);
    for(int i = 1; i <= m; i++){
        int u,v,w;
        scanf("%d %d %d", &u, &v, &w);
        a[u].push_back({v,w});
        a[v].push_back({u,w});
    }
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0;
    q.push(make_pair(0,s));
    while(!q.empty()){
        int x = q.top().second;
        q.pop();
        if(vis[x]){
            continue;
        }
        vis[x] = 1;
        int sa = a[x].size();
        for(int i = 0; i < sa; i++){
            int k = max(dis[x], a[x][i].w), r = a[x][i].s;
            if(k<dis[r]){
                dis[r] = k;
                q.push(make_pair(-dis[r],r));
            }
        }
    }
    printf("%d", dis[t]);
}