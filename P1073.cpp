//
// Created by kibi on 2022/7/18.
//
#include <bits/stdc++.h>
using namespace std;
int n, m;
int c[100005];
vector<int> g1[100005], g2[100005];
bool f1[100005], f2[100005];
int b[100005];
int mix[100005], mxx[100005];

void add_edge(int u, int v){
    g1[u].push_back(v);
    g2[v].push_back(u);
}

bool cmp(int a, int b){
    return c[a] < c[b];
}

void op1(int s, int v){
    queue<int> q;
    q.push(s);
    while (!q.empty()){
        int u = q.front();
        q.pop();
        mix[u] = v;
        int sa = g1[u].size();
        for(int i = 0; i < sa; i++){
            if(!mix[g1[u][i]]){
                mix[g1[u][i]] = v;
                q.push(g1[u][i]);
            }
        }
    }
}

void op2(int s, int v){
    queue<int> q;
    q.push(s);
    while (!q.empty()){
        int u = q.front();
        q.pop();
        mxx[u] = v;
        int sa = g2[u].size();
        for(int i = 0; i < sa; i++){
            if(!mxx[g2[u][i]]){
                //                mxx[g2[u][i]] = v;
                q.push(g2[u][i]);
            }
        }
    }
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++){
        scanf("%d", &c[i]);
    }
    for(int i = 1; i <= m; i++){
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        add_edge(x, y);
        if(z == 2){
            add_edge(y, x);
        }
    }
    queue<int> q;
    q.push(1);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        f1[u] = true;
        int sa = g1[u].size();
        for(int i = 0; i < sa; i++){
            if(!f1[g1[u][i]]){
                q.push(g1[u][i]);
            }
        }
    }

    q.push(n);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        f2[u] = true;
        int sa = g2[u].size();
        for(int i = 0; i < sa; i++){
            if(!f2[g2[u][i]]){
                q.push(g2[u][i]);
            }
        }
    }

    for(int i = 1; i <= n; i++){
        b[i] = i;
    }
    sort(b+1, b+1+n, cmp);

    for(int i = 1; i <= n; i++){
        if((!mix[b[i]]) && f1[b[i]]){
            op1(b[i], c[b[i]]);
        }
    }

    for(int i = n; i >= 1; i--){
        if((!mxx[b[i]]) && f2[b[i]]){
            op2(b[i], c[b[i]]);
        }
    }

    int ans = 0;
    for(int i = 1; i <= n; i++){
        if(f1[i] && f2[i]){
            ans = max(ans, mxx[i] - mix[i]);
        }
    }
    printf("%d", ans);

}