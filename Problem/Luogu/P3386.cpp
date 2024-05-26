//
// Created by kibi on 2021/8/20.
//
#include <bits/stdc++.h>
using namespace std;
int n,m,e,r[505],vis[505],flag;
vector<int> a[505];
int dfs(int x){
    if(vis[x] == flag)return 0;
    vis[x] = flag;
    for(int i = 0, sa = a[x].size(); i < sa; i++){
        if((!r[a[x][i]])||dfs(r[a[x][i]])){
            r[a[x][i]] = x;
            return 1;
        }
    }
    return 0;
}
int main(){
    cin >> n >> m >> e;
    for(int i = 1; i <= e; i++){
        int u,v;
        scanf("%d %d", &u, &v);
        a[u].push_back(v);
    }
    int s = 0;
    for(int i = 1; i <= n; i++){
        flag = i;
        s += dfs(i);
    }
    cout << s;
    return 0;
}

/*
 * 2022/7/13
#include <bits/stdc++.h>
using namespace std;
int n, m, e;
vector<int> g[1005];
int use[1005];
bool vis[1005];

void add_edge(int x, int y){
    g[x].push_back(y);
    g[y].push_back(x);
}

bool search(int u){
    int sg = g[u].size();
    for(int i = 0; i < sg; i++){
        if(!vis[g[u][i]]){
            vis[g[u][i]] = true;
            if(!use[g[u][i]] || search(use[g[u][i]])){
                use[g[u][i]] = u;
                return true;
            }
        }
    }
    return false;
}

int main(){
    scanf("%d %d %d", &n ,&m, &e);
    for(int i = 1; i <= e; i++){
        int x, y;
        scanf("%d %d", &x, &y);
        add_edge(x, 500+y);
    }

    int ans = 0;
    for(int i = 1; i <= n; i++){
        memset(vis, 0, sizeof vis);
        ans += search(i);
    }
    printf("%d", ans);

    return 0;
}
 */