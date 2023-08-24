//
// Created by kibi on 23-8-24.
//
#include <bits/stdc++.h>
using namespace std;

int main() {

    static const int N = 5000, M = 5000;

    class Tools {
    public:
        static void read(int &x) {
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
    };

    class Graph {
        class Edge {
        public:
            int w, to;
            Edge *nxt;
        };
        Edge *head[N + 5]{};
        Edge edge[M + 5]{};
        int cnt;

        void dfs(int u, int *in, bool *vis) {
            vis[u] = true;
            for (auto i = head[u]; i != nullptr; i = i->nxt) {
                in[i->to]++;
                if (!vis[i->to]) {
                    dfs(i->to, in, vis);
                }
            }
        }

    public:
        explicit Graph(int n = 5000, int m = 5000) { // TODO why can't n = N, m = M

            cnt = 0;

            for (int i = 1; i <= n; i++) {
                head[i] = nullptr;
            }

            for (int i = 1; i <= m; i++) {
                edge[i].nxt = nullptr;
            }
        }

        void add_edge(int u, int v, int w, bool flag = false) {
            edge[++cnt] = {w, v, head[u]};
            head[u] = &edge[cnt];

            if (!flag) {
                return;
            }

            add_edge(v, u, w);
        }

        void init(int u, int *in, bool *vis) {
            dfs(u, in, vis);
        }

        Edge *begin(int x) {
            return head[x];
        }
    };

    auto read = Tools::read;

    int n, m, k;
    read(n), read(m), read(k);

    static Graph graph;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        read(u), read(v), read(w);
        graph.add_edge(u, v, w);
    }

    static bool vis[N + 5];
    static int in[N + 5];
    graph.init(1, in, vis);

    static queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (vis[i] && !in[i]) {
            q.push(i);
        }
    }

    static int f[N + 5][N + 5];
    static int pre[N + 5][N + 5];
    memset(f, 0x3f, sizeof f);
    f[1][1] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto i = graph.begin(u); i != nullptr; i = i->nxt) {
            for (int j = 2; j <= n; j++) {
                if((long long)f[u][j-1] + i->w > k){
                    continue;
                }
                f[i->to][j] = min(f[i->to][j], f[u][j - 1] + i->w);
                if (f[i->to][j] == f[u][j - 1] + i->w) {
                    pre[i->to][j] = u;
                }
            }
            in[i->to]--;
            if (!in[i->to]) {
                q.push(i->to);
            }
        }
    }

    int ans = 0;
    for (int i = n; i >= 1; i--) {
        if (f[n][i] <= k) {
            ans = i;
            break;
        }
    }

    printf("%d\n", ans);
    int now = n, cnt = ans, res[N + 5];
    while(now){
        res[cnt - 1] = pre[now][cnt];
        now = pre[now][cnt];
        cnt--;
    }
    for(int i = 1; i < ans; i++){
        printf("%d ", res[i]);
    }
    printf("%d\n", n);
}