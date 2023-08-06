//
// Created by kibi on 2022/7/20.
//
#include <bits/stdc++.h>
using namespace std;
int n, m, r;
struct node{
    int v, id;
};
vector<int> g[500005];
vector<node> q[500005];
int ans[500005];
int b[500005];
bool vis[500005];

int find(int x){
    if(x != b[x]){
        return b[x] = find(b[x]);
    }
    return x;
}

void f(int u, int fa){
    int sg = g[u].size();
    for(int i = 0; i < sg; i++){
        if(g[u][i] == fa){
            continue ;
        }
        f(g[u][i], u);
    }
    vis[u] = true;

    int sq = q[u].size();
    for(int i = 0; i < sq; i++){
        if(vis[q[u][i].v]){
            ans[q[u][i].id] = find(b[q[u][i].v]);
        }
    }
    b[u] = find(b[fa]);
}

int main(){
    scanf("%d %d %d", &n, &m, &r);
    for(int i = 1; i < n; i++){
        int x, y;
        scanf("%d %d", &x, &y);
        g[x].push_back(y);
        g[y].push_back(x);
        b[i] = i;
    }
    b[n] = n;
    for(int i = 1; i <= m; i++){
        int x, y;
        scanf("%d %d", &x, &y);
        q[x].push_back({y, i});
        q[y].push_back({x, i});
    }
    f(r, r);
    for(int i = 1; i <= m; i++){
        printf("%d\n", ans[i]);
    }
}

/*

#include <bits/stdc++.h>
using namespace std;

const int N = 500000;

void read(int&);

int main(){
    
    class Tree{
        int head[N + 5], nxt[2*N + 5], to[2*N + 5], cnt;
        int fo[N+5][20], dep[N+5];

        void dfs(int u, int fa){
            dep[u] = dep[fa]+1;
            fo[u][0] = fa;
            for(int i = 1; i <= 19; i++){
                fo[u][i] = fo[ fo[u][i-1] ][i-1];
            }
            for(int i = head[u]; i; i = nxt[i]){
                int v = to[i];
                if(v != fa){
                    dfs(v, u);
                }
            }
        }

    public:
        void add_edge(int u, int v){
            to[++cnt] = v;
            nxt[cnt] = head[u];
            head[u] = cnt;

            to[++cnt] = u;
            nxt[cnt] = head[v];
            head[v] = cnt;
        }

        void pre_lca(int root){
            dfs(root, 0);
        }

        int get_lca(int x, int y){
            if(dep[x] > dep[y]){
                swap(x, y);
            }
            for(int i = 19; i >= 0; i--){
                if(dep[fo[y][i]] >= dep[x]){
                    y = fo[y][i];
                }
            }
            if(y == x){
                return x;
            }
            for(int i = 19; i >= 0; i--){
                if(fo[x][i] != fo[y][i]){
                    x = fo[x][i];
                    y = fo[y][i];
                }
            }
            return fo[x][0];
        }

    };

    static Tree tree;

    int n, m, s;
    read(n), read(m), read(s);
    for(int i = 1; i < n; i++){
        static int u, v;
        read(u), read(v);
        tree.add_edge(u, v);
    }

    tree.pre_lca(s);

    for(int i = 1; i <= m; i++){
        static int u, v;
        read(u), read(v);
        printf("%d\n", tree.get_lca(u, v));
    }

}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
        if(c == '-'){
            w = -1;
        }
        c = getchar();
    }
    while('0' <= c && c <= '9'){
        s = s * 10 + c - '0';
        c = getchar();
    }
    x = s * w;
}s

*/

/*

#include <bits/stdc++.h>
using namespace std;

const int N = 500000;

void read(int&);

int main(){
    
    class Tree{
        int head[N + 5], nxt[2*N + 5], to[2*N + 5], cnt;
        int fo[N+5][20], dep[N+5];

        void dfs(int u, int fa){
            dep[u] = dep[fa]+1;
            fo[u][0] = fa;
            for(int i = 1; i <= 19; i++){
                fo[u][i] = fo[ fo[u][i-1] ][i-1];
            }
            for(int i = head[u]; i; i = nxt[i]){
                int v = to[i];
                if(v != fa){
                    dfs(v, u);
                }
            }
        }

    public:
        void add_edge(int u, int v){
            to[++cnt] = v;
            nxt[cnt] = head[u];
            head[u] = cnt;

            to[++cnt] = u;
            nxt[cnt] = head[v];
            head[v] = cnt;
        }

        void pre_lca(int root){
            dfs(root, 0);
        }

        int get_lca(int x, int y){
            if(dep[x] > dep[y]){
                swap(x, y);
            }
            for(int i = 19; i >= 0; i--){
                if(dep[fo[y][i]] >= dep[x]){
                    y = fo[y][i];
                }
            }
            if(y == x){
                return x;
            }
            for(int i = 19; i >= 0; i--){
                if(fo[x][i] != fo[y][i]){
                    x = fo[x][i];
                    y = fo[y][i];
                }
            }
            return fo[x][0];
        }

    };

    static Tree tree;

    int n, m, s;
    read(n), read(m), read(s);
    for(int i = 1; i < n; i++){
        static int u, v;
        read(u), read(v);
        tree.add_edge(u, v);
    }

    tree.pre_lca(s);

    for(int i = 1; i <= m; i++){
        static int u, v;
        read(u), read(v);
        printf("%d\n", tree.get_lca(u, v));
    }

}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
        if(c == '-'){
            w = -1;
        }
        c = getchar();
    }
    while('0' <= c && c <= '9'){
        s = s * 10 + c - '0';
        c = getchar();
    }
    x = s * w;
}s

*/