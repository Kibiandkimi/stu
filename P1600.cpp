//
// Created by kibi on 2022/10/16.
//
#include <bits/stdc++.h>
using namespace std;
static const int Size = 600010;
class Graph {
    int head[Size / 2], nxt[Size], to[Size], tot;

public:
    Graph() {
//         are these necessary?
        memset(head, 0, sizeof head);
        memset(to, 0, sizeof to);
        memset(nxt, 0, sizeof nxt);
        tot = 0;
    }
    void addEdge(int u, int v, bool flag = true) {
        to[++tot] = v, nxt[tot] = head[u], head[u] = tot;
        if (!flag) {
            return;
        }
        to[++tot] = u, nxt[tot] = head[v], head[v] = tot;
    }
    int begin(int x) {
        return head[x];
    }
    int next(int x) {
        return nxt[x];
    }
    int get(int x) {
        return to[x];
    }
};

class Lca {
    int fa[Size][20]{}, dep[Size]{};
    Graph *g;
    void f(int u) {
        for (int i = 1; (1 << i) <= dep[u]; i++) {
            fa[u][i] = fa[fa[u][i - 1]][i - 1];
        }
        for (int i = g->begin(u); i; i = g->next(i)) {
            static int v;
            v = g->get(i);
            if (v != fa[u][0]) {
                fa[v][0] = u;
                dep[v] = dep[u] + 1;
                f(v);
            }
        }
    }

public:
    explicit Lca(Graph *gT, int u = 1) {
        dep[u] = 1, fa[u][0] = 1;
        g = gT;
        f(u);
    }
    int getLca(int x, int y) {
        if (x == y) {
            return x;
        }
        if (dep[x] < dep[y]) {
            swap(x, y);
        }

        for (int i = log(dep[x] - dep[y]) / log(2); i >= 0; i--) {
            if (dep[fa[x][i]] >= dep[y]) {
                x = fa[x][i];
            }
            if (x == y) {
                return x;
            }
        }
        for (int i = log(dep[x]) / log(2); i >= 0; i--) {
            if (fa[x][i] != fa[y][i]) {
                x = fa[x][i], y = fa[y][i];
            }
        }
        return fa[x][0];
    }
    int getDis(int u, int v, int lca = -1) {
        if (lca == -1) {
            lca = getLca(u, v);
        }
        return dep[u] + dep[v] - 2 * dep[lca];
    }
    int getFa(int x) {
        return fa[x][0];
    }
    int _getDep(int x) {
        return dep[x];
    }
};

void read(int &x);

class Solution {
    const int size = Size / 2;
    int dis[Size / 2]{}, js[Size / 2]{}, w[Size / 2]{}, b1[Size]{}, b2[Size]{}, s[Size / 2]{}, t[Size / 2]{};
    Lca *lca;
    Graph *g;
    Graph g1, g2;
    void f(int u) {
        int t1 = b1[w[u] + lca->_getDep(u)], t2 = b2[w[u] - lca->_getDep(u) + size];
        for (int i = g->begin(u); i; i = g->next(i)) {
            static int v;
            v = g->get(i);
            if (v != lca->getFa(u)) {
                f(v);
            }
        }
        b1[lca->_getDep(u)] += js[u];
        for (int i = g1.begin(u); i; i = g1.next(i)) {
            static int v;
            v = g1.get(i);
            b2[dis[v] - lca->_getDep(t[v]) + size]++;
        }

        ans[u] += b1[w[u] + lca->_getDep(u)] - t1 + b2[w[u] - lca->_getDep(u) + size] - t2;

        for (int i = g2.begin(u); i; i = g2.next(i)) {
            static int v;
            v = g2.get(i);
            b1[lca->_getDep(s[v])]--;
            b2[dis[v] - lca->_getDep(t[v]) + size]--;
        }
    }

public:
    int ans[Size / 2]{};
    Solution(int n, int m, Lca *lcaT, Graph *gT) {
        lca = lcaT;
        g = gT;
        for (int i = 1; i <= n; i++) {
            read(w[i]);
        }
        for (int i = 1; i <= m; i++) {
            static int stLca;
            read(s[i]), read(t[i]);
            stLca = lca->getLca(s[i], t[i]);
            dis[i] = lca->getDis(s[i], t[i], stLca);
            js[s[i]]++;
            g1.addEdge(t[i], i, false);
            g2.addEdge(stLca, i, false);
            if (lca->_getDep(stLca) + w[stLca] == lca->_getDep(s[i])) {
                ans[stLca]--;
            }
        }
        f(1);
    }
};

int main() {
    static int n, m;
    read(n), read(m);
    static Graph g;
    for (int i = 1; i < n; i++) {
        static int u, v;
        read(u), read(v);
        g.addEdge(u, v);
    }
    static Lca lca(&g, 1);
    static Solution solve(n, m, &lca, &g);
    for (int i = 1; i <= n; i++) {
        printf("%d ", solve.ans[i]);
    }

    return 0;
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