//
// Created by kibi on 22-10-6.
//
//TODO why use "Edge *r" will cause runtime error
#include <bits/stdc++.h>
namespace raw{
    using namespace std;
    static const int To = 804;
    struct Edge {
        Edge(int v, Edge *r, int s) {
            this->v = v, this->r = r, this->s = s;
        }
        int v, s;
        Edge *r;
    };
    vector<Edge> g[805];

    void read(int &x);
    void addEdge(int u, int v);
    bool bfs();
    int dfs(int u = 0, int flow = 1e9);


    int main() {
        int T;
        read(T);
        while (T--) {
            static int n, ans;
            read(n);
            for (auto &i : g) {
                i.clear();
            }
            for (int i = 1; i <= n; i++) {
                //            g[i].clear();
                //            g[i].reserve(405);
                for (int j = 1; j <= n; j++) {
                    int tem;
                    read(tem);
                    if (tem) {
                        addEdge(i, j + n);
                    }
                }
                addEdge(0, i);
                addEdge(i + n, To);
            }
            ans = 0;
            while (bfs()) {
                ans += dfs();
            }
            ans == n ? printf("Yes\n") : printf("No\n");
        }
    }
    void addEdge(int u, int v) {
        g[u].emplace_back(v, nullptr, 1);
        g[v].emplace_back(u, &g[u].back(), 0);
        g[u].back().r = &g[v].back();
    }

    void read(int &x) {
        int s = 0, w = 1, c = getchar();
        while (c < '0' || '9' < c) {
            if (c == '-') {
                w = -1;
            }
            c = getchar();
        }
        while ('0' <= c && c <= '9') {
            s = s * 10 + c - '0';
            c = getchar();
        }
        x = s * w;
    }

    int dep[805], cur[805];

    bool bfs() {
        //    static int vis[405];
        memset(dep, -1, sizeof dep);
        static queue<int> q;
        q.push(0);
        dep[0] = 0, cur[0] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto &i : g[u]) {
                if (dep[i.v] == -1 && i.s) {
                    dep[i.v] = dep[u] + 1;
                    cur[i.v] = 0;
                    //                vis[i.v] = true;
                    q.push(i.v);
                }
            }
        }
        return dep[To] != -1;
    }

    int dfs(int u, int flow) {
        if (u == To) {
            return flow;
        }
        int rest = flow, k;
        for (int i = cur[u], mxi = g[u].size(); i < mxi; i++) {
            Edge *now = &g[u][i];
            cur[u] = i;
            if (dep[now->v] == dep[u] + 1 && now->s) {
                k = dfs(now->v, min(rest, now->s));
                if (!k) {
                    dep[now->v] = 0;
                }
                rest -= k;
                now->s -= k;
                now->r->s += k;
                if (rest == 0) {
                    return flow;
                }
            }
        }
        return flow - rest;
    }
}

namespace final{
//    当前弧没优化所以给删了

    using namespace std;
    static const int To = 804;
    struct Edge {
        Edge(int v, int r, int s) {
            this->v = v, this->r = r, this->s = s;
        }
        int v, s;
        int r;
    };
    vector<Edge> g[805];

    void read(int &x);
    void addEdge(int u, int v);
    bool bfs();
    int dfs(int u = 0, int flow = 1e9);


    int main() {
        int T;
        read(T);
        while (T--) {
            static int n, ans;
            read(n);
            for (auto &i : g) {
                i.clear();
            }
            for (int i = 1; i <= n; i++) {
                //            g[i].clear();
                //            g[i].reserve(405);
                for (int j = 1; j <= n; j++) {
                    int tem;
                    read(tem);
                    if (tem) {
                        addEdge(i, j + n);
                    }
                }
                addEdge(0, i);
                addEdge(i + n, To);
            }
            ans = 0;
            while (bfs()) {
                ans += dfs();
            }
            ans == n ? printf("Yes\n") : printf("No\n");
        }
    }
    void addEdge(int u, int v) {
        g[u].emplace_back(v, g[v].size(), 1);
        g[v].emplace_back(u, g[u].size()-1, 0);
        // g[u].back().r = &g[v].back();
    }

    void read(int &x) {
        int s = 0, w = 1, c = getchar();
        while (c < '0' || '9' < c) {
            if (c == '-') {
                w = -1;
            }
            c = getchar();
        }
        while ('0' <= c && c <= '9') {
            s = s * 10 + c - '0';
            c = getchar();
        }
        x = s * w;
    }

    int dep[805];

    bool bfs() {
        //    static int vis[405];
        memset(dep, -1, sizeof dep);
        static queue<int> q;
        q.push(0);
        dep[0] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto &i : g[u]) {
                if (dep[i.v] == -1 && i.s) {
                    dep[i.v] = dep[u] + 1;
                    //                vis[i.v] = true;
                    q.push(i.v);
                }
            }
        }
        return dep[To] != -1;
    }

    int dfs(int u, int flow) {
        if (u == To) {
            return flow;
        }
        int rest = flow, k;
        for (int i = 0, mxi = g[u].size(); i < mxi; i++) {
            Edge *now = &g[u][i];
            if (dep[now->v] == dep[u] + 1 && now->s) {
                k = dfs(now->v, min(rest, now->s));
                if (!k) {
                    dep[now->v] = 0;
                }
                rest -= k;
                now->s -= k;
                g[now->v][now->r].s += k;
                if (rest == 0) {
                    return flow;
                }
            }
        }
        return flow - rest;
    }
}