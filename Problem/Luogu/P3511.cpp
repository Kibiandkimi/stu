//
// Created by kibi on 24-10-26.
//
// TODO
#include <cctype>
#include <cstdio>
#include <sys/types.h>
#include <tuple>
#include <vector>

using uint = unsigned int;
template<typename T>
using vec = std::vector<T>;

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
    uint n, m;
    vec<Edge> edges;
};

std::tuple<uint, vec<uint>> solve(const Config&);

int main() {
    auto n = read<uint>(), m = read<uint>();
    Config config{n, m};
    config.edges.reserve(2 * m);
    for (uint i = 0; i < m; i++) {
        auto u = read<uint>(), v = read<uint>(), w1 = read<uint>(), w2 = read<uint>();
        config.edges.emplace_back(u, v, w1);
        config.edges.emplace_back(v, u, w2);
    }
    auto [ans, path] = solve(config);
    printf("%u\n", ans);
    for (auto &i : path) {
        printf("%u ", i);
    }
    printf("\n");
    return 0;
}

class Graph {
    class Node {
    public:
        uint v, w;
        Node *nxt;
    };
    vec<Node*> head;

public:
    explicit Graph(uint n) : head(n) {}

    void add_edge(uint u, uint v, uint w, bool flag = false) {
        head[u] = new Node {v, w, head[u]};
        flag ? add_edge(v, u, w) : static_cast<void>(0);
    }

    Node* begin(uint u) {
        return head[u];
    }
};

std::tuple<uint, vec<uint>> solve(const Config& config) {
    Graph graph(n);

    for (auto &i : config.edges) {
        auto [u, v, w] = i;
        graph.add_edge(u, v, w);
    }

    for (uint i = 0; i < config.n; i++) {

    }
}