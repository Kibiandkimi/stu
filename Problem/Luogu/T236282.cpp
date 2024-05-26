//
// Created by kibi on 2022/8/6.
//
#include <bits/stdc++.h>
using namespace std;
int n, cnt, b[100005], b2[100005];
int lca[1005][1005];
char c[100005];
bool vis[100005];
struct node{
    int son[40] = {0}, v = 0, dep = 0;
}tri[400005];
struct node2{
    int u, v, w;
};

int g(char c){
    if('0'<=c&&c<='9'){
        return c-'0';
    }else{
        return 10+c-'a';
    }
}

void build(int st){
    int u = 0;
    for(int i = st; i <= n; i++){
        if(!tri[u].son[g(c[i])]){
            tri[u].son[g(c[i])] = ++cnt;
            tri[cnt].v++;
            tri[cnt].dep = tri[u].dep+1;
            //            tri[cnt].id = cnt;
            b[cnt] = cnt;
            b2[cnt] = cnt;
        }else{
            tri[tri[u].son[g(c[i])]].v++;
        }
        u = tri[u].son[g(c[i])];
    }
}

int find2(int x){
    if(x != b2[x]){
        return b2[x] = find2(b2[x]);
    }
    return x;
}

void f(int u, int fa){
    //    int sg = g[u].size();
    for(int i : tri[u].son){
        if(!i){
            continue;
        }
        f(i, u);
    }
    vis[u] = true;

    //    int sq = q[u].size();
    for(int i = 1; i <= cnt; i++){
        if(i == u){
            continue ;
        }
        if(vis[i]){
            lca[u][i] = lca[i][u] = find2(b2[i]);
        }
    }
    b2[u] = find2(b2[fa]);
}

vector<node2> edge;

bool cmp(node2 a, node2 b){
    return a.w < b.w;
}

int find(int x){
    if(b[x] != x){
        return b[x] = find(b[x]);
    }
    return x;
}

int main(){
    scanf("%d %s", &n, c+1);
    for(int i = 1; i <= n; i++){
        build(i);
    }
    f(0, 0);
    for(int i = 1; i <= cnt; i++){
        for(int j = 1; j < i; j++){
            edge.push_back({i, j, tri[i].v+tri[j].v+tri[lca[i][j]].dep});
        }
    }

    sort(edge.begin(), edge.end(), cmp);
    int se = edge.size();
    int ans = 0;
    int rn = 0;
    for(int i = 0; i < se; i++){
        int u = edge[i].u, v = edge[i].v, w = edge[i].w;
        if(find(b[u]) != find(b[v])){
            b[find(b[u])] = b[v];
            ans += w;
            rn++;
        }
        if(rn == cnt-1){
            printf("%d", ans);
            return 0;
        }
    }
}