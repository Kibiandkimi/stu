//
// Created by kibi on 2022/5/14.
//
#include <bits/stdc++.h>
using namespace std;
int m;
vector<int> g[1005];
int ind[1005];
int mn = 1005;
int st;
//queue<int> q;
int ans[2005], tot;
int gg[1005][1005];

bool cmp(int a, int b){
    return a<b;
}

void f(int u){
    int sa = g[u].size();
    //    bool flag = false;
    for(int i = 0; i < sa; i++){
        int v = g[u][i];
        if(!gg[u][v]){
            continue;
        }
        //        flag = true;
        gg[u][v] = --gg[v][u];
        f(v);
    }
    //    if(!flag){
    //        ans[tot++] = u;
    //    }
    ans[tot++] = u;
}

int main(){
    scanf("%d", &m);
    for(int i = 1; i <= m; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
        ind[u]++;
        ind[v]++;
        mn = min(mn, u);
        mn = min(mn, v);
        gg[u][v] = ++gg[v][u];
    }

    st = mn;
    for(int i = mn; i <= 505; i++){
        if(ind[i]%2){
            st = i;
            break;
        }
        //        sort(g[i].begin(), g[i].end(), cmp);
    }

    for(int i = mn; i <= 505; i++){
        sort(g[i].begin(), g[i].end(), cmp);
    }

    f(st);

    for(int i = tot-1; i >= 0; i--){
        printf("%d\n", ans[i]);
    }

    return 0;
}