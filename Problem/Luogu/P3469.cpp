//
// Created by kibi on 2022/7/21.
//
#include <bits/stdc++.h>
using namespace std;
int n, m;
vector<int> g[100005];
int dfn[100005], low[100005], cnt;
long long ans[100005], size[100005];
bool c[100005];

void tarjan(int u, int fa){
    low[u] = dfn[u] = ++cnt;
    size[u] = 1;
    int flag = 0, sum = 0;
    int sg = g[u].size();
    for(int i = 0; i < sg; i++){
        if(g[u][i] == fa){
            continue ;
        }
        if(!dfn[g[u][i]]){
            tarjan(g[u][i], u);
            size[u] += size[g[u][i]];
            low[u] = min(low[u], low[g[u][i]]);
            if(low[g[u][i]] >= dfn[u]){
                ans[u] += size[g[u][i]] * (n-size[g[u][i]]);
                sum += size[g[u][i]];
                flag++;
                if(u!=1||flag>1){
                    c[u] = true;
                }
            }
        }else{
            low[u] = min(low[u], dfn[g[u][i]]);
        }
    }
    if(!c[u]){
        ans[u] = 2*(n-1);
    }else{
        ans[u] += (n-1)+(long long)(n-sum-1)*(sum+1);
    }
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= m; i++){
        int x, y;
        scanf("%d %d", &x, &y);
        g[x].push_back(y);
        g[y].push_back(x);
    }

    tarjan(1, 0);

    for(int i = 1; i <= n; i++){
        printf("%lld\n", ans[i]);
    }

}

/*

#include <bits/stdc++.h>
using namespace std;

const int N = 100000, M = 500000;

void read(int&);

int main(){

    class Graph{
        int head[N + 5], nxt[2 * M + 5], to[2 * M + 5], cnt, n;

    public:

        long long ans[N + 5];

        void add_edge(int u, int v){
            to[++cnt] = v;
            nxt[cnt] = head[u];
            head[u] = cnt;

            to[++cnt] = u;
            nxt[cnt] = head[v];
            head[v] = cnt;
        }

        void pre(int n){
            this -> n = n;
        }

        void tarjan(int x){
            static int dfn[N + 5], low[N + 5], size[N + 5], tot;
            static bool cut[N + 5];

            dfn[x] = low[x] = ++tot;
            size[x] = 1;

            int num = 0, sum = 0;
            for(int i = head[x]; i; i = nxt[i]){
                int v = to[i];
                if(!dfn[v]){
                    tarjan(v);
                    size[x] += size[v];
                    low[x] = min(low[x], low[v]);
                    if(low[v] >= dfn[x]){
                        ans[x] += (long long)size[v] * (n-size[v]);
                        sum += size[v];
                        num++;
                        if(x != 1 || num > 1){
                            cut[x] = true;
                        }
                    }
                }else{
                    low[x] = min(low[x], dfn[v]);
                }
            }

            if(!cut[x]){
                ans[x] = 2 * (n-1);
            }else{
                ans[x] += (long long)(n-sum-1) * (sum+1) + (n-1);
            }
        }

    };

    static Graph graph;
    int n, m;

    read(n), read(m);

    for(int i = 1; i <= m; i++){
        int u, v;
        read(u), read(v);
        graph.add_edge(u, v);
    }

    graph.pre(n);

    graph.tarjan(1);

    for(int i = 1; i <= n; i++){
        printf("%lld\n", graph.ans[i]);
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
}

*/

/*

#include <bits/stdc++.h>
using namespace std;

const int N = 100000, M = 500000;

void read(int&);

int main(){

    class Graph{
        int head[N + 5], nxt[2 * M + 5], to[2 * M + 5], cnt, n;

    public:

        long long ans[N + 5];

        void add_edge(int u, int v){
            to[++cnt] = v;
            nxt[cnt] = head[u];
            head[u] = cnt;

            to[++cnt] = u;
            nxt[cnt] = head[v];
            head[v] = cnt;
        }

        void pre(int n){
            this -> n = n;
        }

        void tarjan(int x){
            static int dfn[N + 5], low[N + 5], size[N + 5], tot;
            static bool cut[N + 5];

            dfn[x] = low[x] = ++tot;
            size[x] = 1;

            int num = 0, sum = 0;
            for(int i = head[x]; i; i = nxt[i]){
                int v = to[i];
                if(!dfn[v]){
                    tarjan(v);
                    size[x] += size[v];
                    low[x] = min(low[x], low[v]);
                    if(low[v] >= dfn[x]){
                        ans[x] += (long long)size[v] * (n-size[v]);
                        sum += size[v];
                        num++;
                        if(x != 1 || num > 1){
                            cut[x] = true;
                        }
                    }
                }else{
                    low[x] = min(low[x], dfn[v]);
                }
            }

            if(!cut[x]){
                ans[x] = 2 * (n-1);
            }else{
                ans[x] += (long long)(n-sum-1) * (sum+1) + (n-1);
            }
        }

    };

    static Graph graph;
    int n, m;

    read(n), read(m);

    for(int i = 1; i <= m; i++){
        int u, v;
        read(u), read(v);
        graph.add_edge(u, v);
    }

    graph.pre(n);

    graph.tarjan(1);

    for(int i = 1; i <= n; i++){
        printf("%lld\n", graph.ans[i]);
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
}

*/