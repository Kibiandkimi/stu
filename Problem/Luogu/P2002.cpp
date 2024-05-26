//
// Created by kibi on 2022/7/21.
//
#include <bits/stdc++.h>
using namespace std;

int n, m;
vector <int> g1[100005], g2[100005];
stack<int> st;
bool inst[100005];
int dfn[100005], low[100005], cnt, s;
vector<int> v[100005];
int id[100005];
int in[100005];

void tarjan(int u){
    dfn[u] = ++cnt;
    low[u] = dfn[u];
    st.push(u);
    inst[u] = true;
    int sg = g1[u].size();
    for(int i = 0; i < sg; i++){
        if(!dfn[g1[u][i]]){
            tarjan(g1[u][i]);
            low[u] = min(low[u], low[g1[u][i]]);
        }else if(inst[g1[u][i]]){
            low[u] = min(low[u], dfn[g1[u][i]]);
        }
    }
    if(dfn[u] == low[u]){
        s++;
        int top;
        do{
            top = st.top();
            v[s].push_back(top);
            id[top] = s;
            inst[top] = false;
            st.pop();
        }while(top != u);
    }
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= m; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        g1[u].push_back(v);
    }
    for(int i = 1; i <= n; i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }

    for(int i = 1; i <= s; i++){
        int sv = v[i].size();
        for(int j = 0 ; j < sv; j++){
            int sg = g1[v[i][j]].size();
            for(int k = 0; k < sg; k++){
                if(id[ g1[ v[i][j] ][k] ]!=i) {
                    g2[i].push_back(id[g1[v[i][j]][k]]);
                    in[id[g1[v[i][j]][k]]]++;
                }
            }
        }
    }


    //    for(int i = 1; i <= n; i++){
    //        int sg = g1[i].size();
    //        for(int j = 0; j < sg; j++){
    //            if(id[g1[i][j]] != id[i]){
    //                in[id[g1[i][j]]]++;
    //            }
    //        }
    //    }

    int ans = 0;
    for(int i = 1; i <= s; i++){
        ans += !in[i];
    }

    printf("%d", ans);
    //    printf("%d", ans);
}