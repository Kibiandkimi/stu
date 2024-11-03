//
// Created by kibi on 24-11-3.
//
#include <cctype>
#include <cstdio>
#include <queue>
#include <sys/types.h>
#include <tuple>
#include <vector>

template<typename T>
using vec = std::vector<T>;
using u32 = const unsigned int;
using u64 = const unsigned long long;
using ull = unsigned long long;

template<typename T>
T read() {
    T s = 0, w = 1, c = getchar();
    while (!isdigit(c)) {
        if (c == '-') {
            w = -1;
        }
        c = getchar();
    }
    while (isdigit(c)) {
        s = s * 10 + c - '0';
        c = getchar();
    }
    return s * w;
}

using Edge = std::tuple<uint, uint, uint>;

class Config {
public:
    u32 n, m, k, p;
    vec<Edge> edges;
};

uint solve(const Config&);

int main() {
    uint T = read<uint>();
    while (T--) {
        u32 n = read<uint>(), m = read<uint>(), k = read<uint>(), p = read<uint>();
        Config config{n, m, k, p, vec<Edge>(m)};
        for (auto &i : config.edges) {
            u32 u = read<uint>(), v = read<uint>(), w = read<uint>();
            i = {u, v, w};
        }
        auto res = solve(config);
        printf("%d\n", res == -1 ? -1 : static_cast<int>(res));
    }
}

class Cmp {
public:
    bool operator () (const std::tuple<uint, uint> &a, const std::tuple<uint, uint> &b) const {
        return std::get<0>(a) > std::get<0>(b);
    }
};

class Graph {
    class Node {
    public:
        uint v, w;
        Node *nxt;
    };

    vec<Node*> head;

public:
    explicit Graph(u32 n) : head(n){}

    void add_edge(u32 u, u32 v, u32 w, bool flag = false) {
        head[u] = new Node{v, w, head[u]};
        flag ? add_edge(v, u, w) : static_cast<void>(0);
    }

    Node* begin(u32 u) {
        return head[u];
    }
};

uint solve(const Config &config) {
    auto add = [&config](uint &a, u32 b) {
        a = a + b >= config.p ? a + b - config.p : a + b;
    };

    Graph graph(config.n);

    for (auto &i : config.edges) {
        auto [u, v, w] = i;
        graph.add_edge(u - 1, v - 1, w);
    }

    vec<uint> d(config.n, -1);
    vec<bool> vis(config.n);
    std::priority_queue<std::tuple<uint, uint>, vec<std::tuple<uint, uint>>, Cmp> pq;
    pq.emplace(0, 0);
    d[0] = 0;
    while (!pq.empty()) {
        auto [dis, id] = pq.top();
        pq.pop();
        if (vis[id]) {
            continue;
        }
        vis[id] = true;
        for (auto i = graph.begin(id); i; i = i->nxt) {
            if (d[i->v] > d[id] + i->w) {
                d[i->v] = d[id] + i->w;
                pq.emplace(d[i->v], i->v);
            }
        }
    }

    vec<uint> res(config.n, 0);
    res[0] = 1;
    for (uint i = 0; i < config.n; i++) {
        pq.emplace(d[i], i);
    }
    while (!pq.empty()) {
        auto [dis, id] = pq.top();
        pq.pop();
        for (auto i = graph.begin(id); i; i = i->nxt) {
            if (d[i->v] == d[id] + i->w) {
                add(res[i->v], res[id]);
            }
        }
    }

    return res.back();
}