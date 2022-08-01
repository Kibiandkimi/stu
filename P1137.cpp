//
// Created by kibi on 2022/5/13.
//
#include <bits/stdc++.h>
using namespace std;
int n, m, ind[100005], ans[100005];
vector<int> g[100005];
queue<int> q;

int main(){
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= m; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
        ind[v]++;
    }

    for(int i = 1; i <= n; i++){
        ans[i] = 1;
        if(!ind[i]){
            q.push(i);
        }
    }

    while(!q.empty()){
        int u = q.front();
        q.pop();
        int sa = g[u].size();

        for(int i = 0; i < sa; i++){
            int v = g[u][i];

            ans[v] = max(ans[v], ans[u]+1);
            ind[v]--;
            if(!ind[v]){
                q.push(v);
            }
        }
    }

    for(int i = 1; i <= n; i++){
        printf("%d\n", ans[i]);
    }

    return 0;
}