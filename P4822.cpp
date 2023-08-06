//
// Created by kibi on 2022/8/1.
//
#include <bits/stdc++.h>
using namespace std;
int n, m, k;
int dp_dis[55][55];
struct node{
    int v, w;
};
vector<node> g[55];
//bool vis[55];

//void f(int u){
//    int sg = g[u].size();
//    for(int i = 0; i < sg; i++){
//        if(vis[g[u][i].v]){
//            continue;
//        }
//        int to = g[u][i].v, wei = g[u][i].w;
//        dp_dis[to][0] = min(dp_dis[to][0], dp_dis[u][0]+wei);
//        for(int i = 1; i <= k; i++){
//            dp_dis[to][i] = min(dp_dis[to][i], min(dp_dis[u][i-1]+wei/2, dp_dis[u][i]+wei));
//        }
//        vis[to] = true;
//        f(to);
//        vis[to] = false;
//    }
//}

int main(){
    scanf("%d %d %d", &n, &m, &k);
    for(int i = 1; i <= m; i++){
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    memset(dp_dis, 0x3f, sizeof dp_dis);
    dp_dis[1][0] = 0;

    queue<node> q;
    q.push({1, 0});
    while(!q.empty()){
        node t = q.front();
        q.pop();
        int u = t.v, l = t.w;
        int sg = g[u].size();
        for(int i = 0; i < sg; i++){
            int v = g[u][i].v, wei = g[u][i].w;
            if(dp_dis[v][l] > dp_dis[u][l]+wei){
                dp_dis[v][l] = dp_dis[u][l]+wei;
                q.push({v, l});
            }
            if(l+1<=k && dp_dis[v][l+1] > dp_dis[u][l] + wei/2){
                dp_dis[v][l+1] = dp_dis[u][l] + wei/2;
                q.push({v, l+1});
            }
        }
    }

    //    f(1);
    int ans = 1e9;
    for(int i = 0; i <= k; i++){
        ans = min(ans, dp_dis[n][i]);
    }
    printf("%d", ans);
}

/*

#include <bits/stdc++.h>
using namespace std;

const int N = 50, M = 1000, K = 50;

void read(int&);

int main(){
    
    class Graph{
        int head[N + 5], nxt[2 * M + 5], to[2 * M + 5], time[M + 5], cnt;
    
    public:

        void add_edge(int u, int v, int w){
            to[++cnt] = v;
            nxt[cnt] = head[u];
            head[u] = cnt;

            to[++cnt] = u;
            nxt[cnt] = head[v];
            head[v] = cnt;

            time[cnt/2] = w;
        }

        int begin(int x){
            return head[x];
        }

        int next(int x){
            return nxt[x];
        }

        int get(int x){
            return to[x];
        }

        int get_time(int x){
            return time[x/2+x%2];
        }
    };

    static Graph graph;

    int n, m, k;
    read(n), read(m), read(k);

    for(int i = 1; i <= m; i++){
        int u, v, w;
        read(u), read(v), read(w);
        graph.add_edge(u, v, w);
    }

    int f[N + 5][K + 5];
    bool vis[N + 5][K + 5];

    memset(f, 0x3f, sizeof f);

    f[1][0] = 0;

    queue<pair<int, int> > q; // first:id second: K-times
    q.emplace(1, 0);

    while(!q.empty()){
        auto data = q.front();
        q.pop();

        auto [u, _k] = data;

        for(int i = graph.begin(u); i; i = graph.next(i)){
            int v = graph.get(i), w = graph.get_time(i);

            if(f[v][_k] > f[u][_k] + w){
                f[v][_k] = f[u][_k] + w;
                if(!vis[v][_k]){
                    q.emplace(v, _k);
                    vis[v][_k] = true;
                }
            }

            if( _k < k && f[v][_k+1] > f[u][_k] + w/2 ){
                f[v][_k+1] = f[u][_k] + w/2;
                if(!vis[v][_k+1]){
                    q.emplace(v, _k+1);
                    vis[v][_k] = true;
                }
            }
        }
    }

    int ans = 1e9;

    for(int i = 0; i <= k; i++){
        ans = min(ans, f[n][i]);
    }

    printf("%d\n", ans);

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

const int N = 50, M = 1000, K = 50;

void read(int&);

int main(){
    
    class Graph{
        int head[N + 5], nxt[2 * M + 5], to[2 * M + 5], time[M + 5], cnt;
    
    public:

        void add_edge(int u, int v, int w){
            to[++cnt] = v;
            nxt[cnt] = head[u];
            head[u] = cnt;

            to[++cnt] = u;
            nxt[cnt] = head[v];
            head[v] = cnt;

            time[cnt/2] = w;
        }

        int begin(int x){
            return head[x];
        }

        int next(int x){
            return nxt[x];
        }

        int get(int x){
            return to[x];
        }

        int get_time(int x){
            return time[x/2+x%2];
        }
    };

    static Graph graph;

    int n, m, k;
    read(n), read(m), read(k);

    for(int i = 1; i <= m; i++){
        int u, v, w;
        read(u), read(v), read(w);
        graph.add_edge(u, v, w);
    }

    int f[N + 5][K + 5];
    bool vis[N + 5][K + 5];

    memset(f, 0x3f, sizeof f);

    f[1][0] = 0;

    queue<pair<int, int> > q; // first:id second: K-times
    q.emplace(1, 0);

    while(!q.empty()){
        auto data = q.front();
        q.pop();

        auto [u, _k] = data;

        for(int i = graph.begin(u); i; i = graph.next(i)){
            int v = graph.get(i), w = graph.get_time(i);

            if(f[v][_k] > f[u][_k] + w){
                f[v][_k] = f[u][_k] + w;
                if(!vis[v][_k]){
                    q.emplace(v, _k);
                    vis[v][_k] = true;
                }
            }

            if( _k < k && f[v][_k+1] > f[u][_k] + w/2 ){
                f[v][_k+1] = f[u][_k] + w/2;
                if(!vis[v][_k+1]){
                    q.emplace(v, _k+1);
                    vis[v][_k] = true;
                }
            }
        }
    }

    int ans = 1e9;

    for(int i = 0; i <= k; i++){
        ans = min(ans, f[n][i]);
    }

    printf("%d\n", ans);

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