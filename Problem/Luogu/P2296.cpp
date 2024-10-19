//
// Created by Kibi on 24-10-17.
//
#include <algorithm>
#include <array>
#include <cctype>
#include <cstdio>
#include <queue>
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
    config.edges = vec<Edge>(config.m);
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
        uint v;
        Edge *nxt;
    };

    class Iterator {
        Edge *nxt;
    public:
        explicit Iterator(Edge *nxt) :nxt(nxt) {}

        bool operator != (const Iterator &other) const {
            return nxt != other.nxt;
        }

        uint operator * () const {
            return nxt->v;
        }

        const Iterator &operator++ () {
            nxt = nxt->nxt;
            return *this;
        }

    };

    class MyList {
        Edge *head;

    public:
        MyList() : head {nullptr} {}
        explicit MyList(Edge* head) : head(head) {}

        ~MyList() = default; // TODO

        Iterator begin() const {
            return Iterator(head);
        }

        static Iterator end() {
            return Iterator(nullptr);
        }
    };

    vec<Edge*> head;

public:
    explicit Graph(size_t n):head(n, nullptr){}

    void add_edge(uint u, uint v, bool flag = false){
        head[u] = new Edge{v, head[u]};

        flag ? add_edge(v, u) : static_cast<void>(0);
    }

    MyList begin(uint u){
        return MyList{head[u]};
    }
};

int solve(const Config &config) {
    Graph graph(config.n);
    for (auto &i : config.edges) {
        graph.add_edge(get<0>(i) - 1, get<1>(i) - 1);
    }

    // a terrible impl
    /*

    vec<bool>
        flag1(config.n), // able to get to
        flag2(config.n, true), // able to be chosen as path
        in_stk(config.n), // in the current path
        vis(config.n);
    vec<uint> step(config.n); // depth in current path
    auto dfs = [&](uint u, auto &&dfs) -> void {
        in_stk[u] = true;
        for (auto i = graph.begin(u); i; i = i->nxt) {
            if (!vis[i->v]) {
                step[i->v] = step[u] + 1;
                dfs(i->v, dfs);
                step[i->v] = -1;
            }else {
                if (in_stk[i->v]) {
                    if (step[i->v] < step[u]) {
                        dfs(i->v, dfs);
                    }else {
                        continue;
                    }
                }
                if (!flag1[i->v]) {
                    flag2[u] = false;
                }else {
                    flag1[u] = true;
                }
            }
        }
        in_stk[u] = false;
        vis[u] = true;
    };

    */

    vec<bool>
        flag1(config.n), // able to get
        flag2(config.n, true); // able to be chosen in the path

    // calc flag1 with bfs and reversed graph
    {
        Graph rgraph(config.n);
        for (auto &i : config.edges) {
            rgraph.add_edge(get<1>(i) - 1, get<0>(i) - 1);
        }
        queue<uint> q;
        flag1[config.t - 1] = true;
        q.emplace(config.t - 1);
        while (!q.empty()) {
            auto u = q.front();
            q.pop();
            for (auto i : rgraph.begin(u)) {
                if (!flag1[i]) {
                    flag1[i] = true;
                    q.emplace(i);
                }
            }
        }
    }

    // calc flag2
    for (uint i = 0; i < config.n; i++) {
        for (auto v : graph.begin(i)) {
            if (!flag1[v]) {
                flag2[i] = false;
                break;
            }
        }
    }

    if (!flag2[config.s - 1]) {
        return -1;
    }

    // calc ans
    vec<uint> dis(config.n, -1);
    queue<uint> q;
    dis[config.s - 1] = 0;
    q.emplace(config.s - 1);
    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        for (auto v : graph.begin(u)) {
            if (flag2[v] && dis[v] == -1) {
                dis[v] = dis[u] + 1;
                q.emplace(v);
            }
        }
    }

    return dis[config.t - 1] == -1 ? -1 : static_cast<int>(dis[config.t - 1]);
}
