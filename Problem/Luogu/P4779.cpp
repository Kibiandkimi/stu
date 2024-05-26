//
// Created by kibi on 2021/8/16.
//
#include <bits/stdc++.h>
using namespace std;
int n,m,s,w[100005],vis[100005];
priority_queue<pair<int ,int> > q;
struct node{
    int v,w;
};
vector<node> a[100005];
int main(){
    cin >> n >> m >> s;
    for(int i = 1; i <= m; i++){
        int u,v, ww;
        scanf("%d %d %d", &u, &v, &ww);
        a[u].push_back((node){v, ww});
    }
    for(int i = 1; i <= n; i++) w[i] = 1e9;
    w[s] = 0;
    q.push(make_pair(0,s));
    while(!q.empty()){
        int t = q.top().second;
        q.pop();
        if(vis[t]){
            continue;
        }
        vis[t] = 1;
        int sa = a[t].size();
        for(int i = 0; i < sa; i++){
            if(w[a[t][i].v] > w[t]+a[t][i].w){
                w[a[t][i].v] = w[t] + a[t][i].w;
                q.push(make_pair(w[a[t][i].v], a[t][i].v));
            }
        }
    }
    for(int i = 1; i <= n; i++)printf("%d ", w[i]);
}