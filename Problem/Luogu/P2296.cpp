//
// Created by Kibi on 24-10-17.
//
// TODO
//
// Created by Kibi on 24-10-16.
//
//
// Created by Kibi on 24-10-16.
//
#include <algorithm>
#include <array>
#include <cctype>
#include <cstdio>
#include <queue>
#include <stack>
#include <sys/types.h>
#include <tuple>
#include <vector>
using namespace std;

using uint = unsigned int;

template<typename T>
using vec = vector<T>;

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

using Edge = tuple<uint, uint>;

class Config {
public:
    uint n, m, s, t;
    vec<Edge> edges;
};

int solve(const Config &);

int main() {
    Config config;
    config.n = read<uint>();
    config.m = read<uint>();
    config.edges = vec<Edge>(config.n);
    for (auto &i : config.edges) {
        i = {read<uint>(), read<uint>()};
    }
    config.s = read<uint>();
    config.t = read<uint>();
    printf("%d\n", solve(config));
    return 0;
}

class Graph{
    class Edge{
    public:
        int v;
        Edge *nxt;
    };

    std::vector<Edge*> head;

public:
    explicit Graph(int n):head(n + 1, nullptr){}

    void add_edge(int u, int v, bool flag = false){
        head[u] = new Edge{v, head[u]};

        flag ? add_edge(v, u) : (void)0;
    }

    Edge* begin(int u){
        return head[u];
    }
};

int solve(const Config &config) {
    Graph graph(config.n);
    for (auto &i : config.edges) {
        graph.add_edge(get<0>(i), get<1>(i));
    }

    vec<bool> flag(config.n), vis(config.n);
    auto dfs = [&](uint u, auto &&dfs) -> void {

    };
}
