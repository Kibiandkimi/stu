//
// Created by kibi on 2022/7/21.
//
#include <bits/stdc++.h>
using namespace std;
int n, m;
vector<int> g[100005];
int dfn[100005], low[100005], cnt;
long long ans[100005], size[100005];
bool c[100005];

void tarjan(int u, int fa){
    low[u] = dfn[u] = ++cnt;
    size[u] = 1;
    int flag = 0, sum = 0;
    int sg = g[u].size();
    for(int i = 0; i < sg; i++){
        if(g[u][i] == fa){
            continue ;
        }
        if(!dfn[g[u][i]]){
            tarjan(g[u][i], u);
            size[u] += size[g[u][i]];
            low[u] = min(low[u], low[g[u][i]]);
            if(low[g[u][i]] >= dfn[u]){
                ans[u] += size[g[u][i]] * (n-size[g[u][i]]);
                sum += size[g[u][i]];
                flag++;
                if(u!=1||flag>1){
                    c[u] = true;
                }
            }
        }else{
            low[u] = min(low[u], dfn[g[u][i]]);
        }
    }
    if(!c[u]){
        ans[u] = 2*(n-1);
    }else{
        ans[u] += (n-1)+(long long)(n-sum-1)*(sum+1);
    }
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= m; i++){
        int x, y;
        scanf("%d %d", &x, &y);
        g[x].push_back(y);
        g[y].push_back(x);
    }

    tarjan(1, 0);

    for(int i = 1; i <= n; i++){
        printf("%lld\n", ans[i]);
    }

}