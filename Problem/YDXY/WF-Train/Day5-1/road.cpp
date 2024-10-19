//
// Created by kibi on 24-10-7.
//
#include <cctype>
#include <cstdio>
#include <map>
#include <queue>
#include <sys/types.h>
#include <tuple>
#include <vector>
using namespace std;

using ull = unsigned long long;

template<typename T>
T read () {
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

using Edge = tuple<uint, uint, uint>;

class Config {
public:
    uint n, m;
    vector<uint> x;
    vector<Edge> edges;
};

vector<uint> solve(const Config&);

int main () {
    freopen("road.in", "r", stdin);
    freopen("road.out", "w", stdout);

    auto n = read<uint>(), m = read<uint>();
    Config config{n, m, vector<uint>(m), vector<Edge>(m)};
    for (auto &i : config.x) {
        i = read<uint>();
    }
    for (auto &e : config.edges) {
        e = {read<uint>() - 1, read<uint>() - 1, read<uint>() - 1};
    }
    auto ans = solve(config);
    for (auto &i : ans) {
        printf("%u\n", i);
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}

class Graph {
    class Edge {
    public:
        uint v, w;
        Edge *nxt;
    };
    vector<Edge*> head;
public:
    explicit Graph(uint n) : head(n){}

    ~Graph() = default; // TODO

    void add_edge(uint u, uint v, uint w, bool flag = false) {
        head[u] = new Edge{v, w, head[u]};
        flag ? add_edge(v, u, w) : static_cast<void>(0);
    }

    const Edge* begin(uint u) const {
        return head[u];
    }
};

vector<uint> solve(const Config& config) {
    vector<uint> dis(config.n, 50);
    Graph graph(config.n);
    // calc direction
    // maybe useless
    {
        Graph temp_graph(config.n);
        for (auto &i : config.edges) {
            temp_graph.add_edge(get<0>(i), get<1>(i), get<2>(i),true);
        }
        vector<bool> vis(config.n);
        queue<uint> q;
        dis[0] = 0;
        q.push(0);
        while (!q.empty()) {
            auto u = q.front();
            q.pop();
            vis[u] = true;
            for (auto i = temp_graph.begin(u); i; i = i->nxt) {
                if (dis[i->v] > dis[u] + 1) {
                    q.push(i->v);
                    dis[i->v] = dis[u] + 1;
                }
                if (dis[i->v] >= dis[u] + 1) {
                    graph.add_edge(u, i->v, i->w);
                }
            }
        }
    }

    dis.clear();
    dis.resize(config.n, 1'000'000'000);
    dis[0] = 0;

    vector<uint> res = dis;
    vector<bool> vis(config.n);
    auto dfs = [&res, &dis, &graph, &config, &vis] (uint u, vector<uint> &times, auto &&dfs) -> void {
        res[u] = min(res[u], dis[u]);
        vis[u] = true;
        for (auto i = graph.begin(u); i; i = i->nxt) {
            if (vis[i->v]/* || times[i->w] * config.x[i->w] + dis[u] >= dis[i->v]*/) {
                continue;
            }
            dis[i->v] = times[i->w] * config.x[i->w] + dis[u];
            times[i->w]++;
            dfs(i->v, times, dfs);
            times[i->w]--;
        }
        vis[u] = false;
    };

    {
        vis[0] = true;
        vector<uint> temp(config.m, 1);
        dfs(0, temp, dfs);
    }

    return {res.begin() + 1, res.end()};
}