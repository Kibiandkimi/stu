//
// Created by kibi on 22-9-4.
//
#include <bits/stdc++.h>
using namespace std;
int n, s, t, Y1[300005], Y2[300005];
long long W[300005];
bool flag;
struct Node{
    Node(int tv, long long tw, int tid){
        v = tv, w = tw, id = tid;
    }
    int v;
    long long w;
    int id;
    int flag;
};
vector<Node> g[300005];

bool getType(int c);
void read(int &x);
void f(int u, int fa = 0);

int main(){
    //    freopen("t.in", "r", stdin);
    read(n), read(s), read(t);
    for(int i = 1; i < n; i++){
        int u, v, w;
        read(u), read(v), read(w);
        Y1[i] = g[u].size();
        Y2[i] = u;
        g[u].emplace_back(v, (long long)w, g[v].size());
        g[v].emplace_back(u, (long long)w, g[u].size()-1);
    }
    memset(W, 0x3f, sizeof W);
    W[s] = 0, f(s), flag = true, W[t] = 0, f(t);
    long long ans = 0;
    for(int i = 1; i <= n; i++){
        ans += W[i];
    }
    printf("%lld\n", ans);
    for(int i = 1; i < n; i++){
        printf("%d", g[Y2[i]][Y1[i]].flag);
    }
    //    fclose(stdin);
}

bool getType(int c){
    return c<'0'||'9'<c;
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(getType(c)){
        if(c == '-'){
            w *= -1;
        }
        c = getchar();
    }
    while(!getType(c)){
        s = s*10 + c-'0';
        c = getchar();
    }
    x = s*w;
}

void f(int u, int fa){
    int sg = g[u].size();
    for(int i = 0; i < sg; i++){
        if(!flag){
            if(g[u][i].v == fa){
                continue ;
            }
            W[g[u][i].v] = W[u]+g[u][i].w;
            g[u][i].flag = 2;
            g[g[u][i].v][g[u][i].id].flag = 1;
            f(g[u][i].v, u);
        }else{
            if(W[u]+g[u][i].w<W[g[u][i].v]){
                W[g[u][i].v] = W[u]+g[u][i].w;
                g[u][i].flag = 2;
                g[g[u][i].v][g[u][i].id].flag = 1;
                f(g[u][i].v, u);
            }else{
                if(g[u][i].v == fa){
                    continue;
                }
                g[u][i].flag = 0;
                g[g[u][i].v][g[u][i].id].flag = 0;
            }
        }
    }
}