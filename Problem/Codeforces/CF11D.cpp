//
// Created by kibi on 23-11-8.
//
#include <bits/stdc++.h>
using namespace std;

int main() {
    auto read = [](initializer_list<int *> x) {
        auto read = [](int &x) {
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
        };

        for (auto &i : x) {
            read(*i);
        }
    };

    class Graph {
        class Edge {
        public:
            int v;
            Edge *nxt;
        };

        vector<Edge *> head;

    public:
        explicit Graph(int n) : head(n) {}

        void add_edge(int u, int v, bool flag = false) {
            head[u] = new Edge{v, head[u]};
            flag ? add_edge(v, u) : void(0);
        }

        Edge *begin(int u) {
            return head[u];
        }
    };

    int n, m;
    read({&n, &m});

    Graph graph(n);

    for (int i = 0; i < m; ++i) {
        int u, v;
        read({&u, &v});
        u--, v--;
        graph.add_edge(u, v, true);
    }

    long long f[1 << n][n];
    memset(f, 0, sizeof f);
    for (int i = 0; i < n; i++) {
        f[1 << i][i] = 1;
    }

    long long ans = 0;

    for (int i = 0; i < (1 << n); ++i) {
        for (int j = 0; j < n; j++) {
            if (!f[i][j]) {
                continue;
            }
            for (auto k = graph.begin(j); k; k = k->nxt) {
                int v = k->v;
                if ((i & -i) > (1 << v)) {
                    continue;
                }
                if ((1 << v) == (i & -i)) {
                    ans += f[i][j];
                } else if (!((1 << v) & i)) {
                    f[i ^ (1 << v)][v] += f[i][j];
                }
            }
        }
    }

    printf("%lld\n", (ans - m) / 2);
}