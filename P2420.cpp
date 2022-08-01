//
// Created by kibi on 2021/7/21.
//
#include <bits/stdc++.h>
using namespace std;
int n,m,dis[100005],vis[100005];
struct node{
    int s,w;
};
vector<node> a[100005];
int main(){
    cin >> n;
    for(int i = 1; i <= n-1; i++){
        int u,v,w;
        cin >> u >> v >> w;
        a[u].push_back(node({v,w}));
        a[v].push_back(node({u,w}));
    }
    queue<node> q;
    q.push((node){1,0});
    while(!q.empty()){
        node t = q.front();
        node n = t;
        dis[t.s]=t.w;
        for(int i = 0; i < a[n.s].size(); i++){
            t = n;
            if(!vis[a[n.s][i].s]){
                vis[a[n.s][i].s]=1;
                t.s=a[n.s][i].s;
                t.w=t.w^a[n.s][i].w;
                q.push(t);
            }
        }
        q.pop();
    }
    cin >> m;
    for(int i = 1; i <= m; i++){
        int a,b;
        cin >> a >> b;
        cout << (dis[a]^dis[b]) << endl;
    }
}