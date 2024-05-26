//
// Created by kibi on 2022/8/1.
//
#include <bits/stdc++.h>
using namespace std;
int n, size[1000005];
long long t_ans, ans, ans_id;
class node{
public:
    int v;
};
vector<int> g[1000005];
void dfs1(int u, int fa){
    int sg = g[u].size();
    size[u] = 1;
    for(int i = 0; i < sg; i++){
        if(g[u][i] == fa){
            continue ;
        }
        dfs1(g[u][i], u);
        size[u] += size[g[u][i]];
    }
    t_ans += size[u];
}

void dfs2(int u, int fa){
    int sg = g[u].size();
    for(int i = 0; i < sg; i++){
        if(g[u][i] == fa){
            continue;
        }
        long long temp = t_ans;
        t_ans = t_ans - size[g[u][i]] + (n - size[g[u][i]]);
        ans = max(t_ans, ans);
        if(ans == t_ans){
            ans_id = g[u][i];
        }
        dfs2(g[u][i], u);
        t_ans = temp;
    }

}

int main(){
    scanf("%d", &n);
    for(int i = 1; i < n; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs1(1, 0);
    t_ans -= size[1];
    ans = max(ans, t_ans);
    ans_id = 1;
    dfs2(1, 0);
    printf("%lld", ans_id);
}