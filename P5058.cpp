//
// Created by kibi on 2022/7/21.
//
#include <bits/stdc++.h>
using namespace std;
int n, m;
vector<int> g[200005];
int dfn[200005], low[200005], cnt;
int s, t;
bool cut[200005];

void tarjan(int u, int fa){
    low[u] = dfn[u] = ++cnt;
    int sg = g[u].size();
    int flag = 0;
    for(int i = 0; i < sg; i++){
        if(g[u][i] == fa){
            continue;
        }
        if(!dfn[g[u][i]]){
            tarjan(g[u][i], u);
            low[u] = min(low[u], low[g[u][i]]);
            if(low[g[u][i]] >= dfn[u] && u!=s && u!=t && (dfn[g[u][i]] <= dfn[s] && dfn[g[u][i]] > dfn[t] || dfn[g[u][i]] <= dfn[t] && dfn[g[u][i]] > dfn[s])){
                cut[u] = true;
            }//else if(u==s){
             //                flag++;
             //            }
        }else{
            low[u] = min(low[u], dfn[g[u][i]]);
        }
    }
    //    if(u==s&&flag>=2){
    //        cut[u] = true;
    //    }
}

int main(){
    scanf("%d", &n);
    while(true){
        int x, y;
        scanf("%d %d", &x, &y);
        if(x==y&&x==0){
            break;
        }
        g[x].push_back(y);
        g[y].push_back(x);
    }
    scanf("%d %d", &s, &t);
    tarjan(s, 0);
    for(int i = 1; i <= n; i++){
        if(cut[i]){
            printf("%d", i);
            return 0;
        }
    }
    printf("No solution");
}