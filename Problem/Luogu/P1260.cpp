//
// Created by kibi on 2021/8/19.
//
#include <bits/stdc++.h>
using namespace std;
int n,m,d[1005],vis[1005],s[1005];
struct node{
    int v,w;
};
vector<node> a[1005];
int main(){
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        int aa,b,c;
        scanf("%d %d %d", &aa, &b, &c);
        a[b].push_back(node({aa,c}));
    }
    for(int i = 1; i <= n; i++){
        d[i] = 1e9;
        a[0].push_back(node({i,0}));
    }
    bool flag = true;
    d[0] = 0;
    vis[0] = 1;
    queue<int> q;
    q.push(0);
    while(!q.empty()){
        int t = q.front();
        q.pop();
        vis[t] = 0;
        s[t]++;
        if(s[t]>n){
            flag = false;
            break;
        }
        int sa = a[t].size();
        for(int i = 0; i < sa; i++){
            if(d[a[t][i].v]>d[t]+a[t][i].w){
                d[a[t][i].v] = d[t]+a[t][i].w;
                if(!vis[a[t][i].v]){
                    q.push(a[t][i].v);
                    vis[a[t][i].v] = 1;
                }
            }
        }
    }
    if(!flag){
        cout << "NO SOLUTION";
    }else{
        int mn = 1e9;
        for(int i = 1; i <= n; i++){
            mn = min(d[i], mn);
        }
        mn = 0 - mn;
        for(int i = 1; i <= n; i++){
            printf("%d\n", d[i]+mn);
        }
    }
}