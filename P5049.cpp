//
// Created by kibi on 22-8-10.
//
//92pts the code is same as P5022
#include <bits/stdc++.h>
using namespace std;
int n, m;
bool vis[6005], in_r[6005], flag_sp, st_sp;
int ans[6005], cnt = 1, st_r;
vector<int> g[6005];
stack<int> s;
stack<int> sec_min;

bool cmp(int a, int b){
    return a < b;
}

void f(int u){
    int sg = g[u].size();
    vis[u] = true;
    ans[cnt++] = u;
    for(int i = 0; i < sg; i++){
        if(!vis[g[u][i]]) {
            f(g[u][i]);
        }
    }
}

int find_r(int u, int fa){
    int sg = g[u].size();
    s.push(u);
    vis[u] = true;
    for(int i = 0; i < sg; i++){
        if(g[u][i] == fa){
            continue;
        }
        if(vis[g[u][i]]){
            in_r[s.top()] = true;
            s.pop();
            st_r = g[u][i];
            return g[u][i];
        }else{
            if(int t = find_r(g[u][i], u)){
                if(t == -1){
                    return -1;
                }
                in_r[s.top()] = true;
                s.pop();
                if(t == u){
                    return -1;
                }
                return t;
            }
        }
    }
    s.pop();
    return 0;
}

void sp_f(int u){
    vis[u] = true;
    ans[cnt++] = u;
    int sg = g[u].size();
    if((!sec_min.empty())&&sec_min.top() == u){
        sec_min.pop();
    }
    if(u == st_r){
        flag_sp = true;
        int t;
        for(t = 0; vis[g[u][t]]; t++){}
        for(int i = t; i < sg; i++){
            if(!vis[g[u][i]]) {
                if(in_r[g[u][i]] && i+1 < sg && !st_sp) {
                    sec_min.push(g[u][i + 1]);
                }
                sp_f(g[u][i]);
            }
        }
    }
    if(flag_sp&&!st_sp){
        int t;
        for(t = 0; vis[g[u][t]]; t++){}
        for(int i = t; i < sg; i++){
            if(vis[g[u][i]]){
                continue;
            }
            if(in_r[g[u][i]]){
                if(sg>i+1) {
                    sec_min.push(g[u][i + 1]);
                }
            }
            if(in_r[g[u][i]] && g[u][i] > sec_min.top()){
                st_sp = true;
                continue;
//                if(i == sg-1){
//                    return ;
//                }else{
//                    vis[g[u][i]] = true;
//                    ans[cnt++] = g[u][i];
//                    for(int j = i+1; j < sg; j++){
//                        if(!vis[g[u][j]]){
//                            sp_f(g[u][j]);
//                        }
//                    }
//                    return;
//                }
            }
            sp_f(g[u][i]);
        }
    }else {
        for (int i = 0; i < sg; i++) {
            if (!vis[g[u][i]]) {
                sp_f(g[u][i]);
            }
        }
    }
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= m; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(int i = 1; i <= n; i++){
        sort(g[i].begin(), g[i].end(), cmp);
    }
    if(n-1 == m) {
        f(1);
    }else{
        find_r(1, 0);
        memset(vis, 0, sizeof vis);
        sp_f(1);
    }
    for(int i = 1; i <= n; i++){
        printf("%d ", ans[i]);
    }
}