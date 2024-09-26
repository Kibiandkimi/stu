//
// Created by Kibi on 24-9-26.
//
#include <assert.h>
#include <cctype>
#include <cstdio>
#include <random>
#include <stack>
#include <sys/types.h>
#include <system_error>
#include <tuple>
#include <vector>
using namespace std;

using uint = unsigned int;

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

class Config {
public:
    uint n, s;
    vector<tuple<uint, uint, uint>> edges;
};

uint solve(const Config&);

int main() {
    auto n = read<uint>(), s = read<uint>();
    Config config{n, s, vector<tuple<uint, uint, uint>>(n - 1)};
    for (auto &i : config.edges) {
        auto u = read<uint>() - 1, v = read<uint>() - 1, w = read<uint>();
        i = {u, v, w};
    }
    printf("%u\n", solve(config));
    return 0;
}

class Graph {
    class Edge {
    public:
        uint v, w;
        Edge* nxt;
    };
    vector<Edge*> head;

public:
    explicit Graph(const uint n):head(n){}

    void add_edge(const uint u, const uint v, const uint w, const bool flag = false) {
        head[u] = new Edge {v, w, head[u]};
        flag ? add_edge(v, u, w) : static_cast<void>(0);
    }

    const Edge* begin(const uint u) const {
        return head[u];
    }
};

mt19937 rnd(random_device{}());

uint solve(const Config& config) {
    Graph graph(config.n);
    for (auto &i : config.edges) {
        graph.add_edge(get<0>(i), get<1>(i), get<2>(i), true);
    }
    uint rt = rnd() % config.n;

    vector<uint> single(config.n), both(config.n), st(config.n), ed(config.n);

    auto dfs = [&graph, &single, &both, &st, &ed](const uint u, const uint fa, auto && dfs) -> void {
        uint mx0 = 0, mx1 = 0;
        st[u] = ed[u] = u;
        for (auto i = graph.begin(u); i; i = i->nxt) {
            if (i->v != fa) {
                dfs(i->v, u, dfs);
                if (single[i->v] + i->w > mx0) {
                    mx1 = mx0;
                    mx0 = single[i->v] + i->w;
                    ed[u] = st[u];
                    st[u] = st[i->v];
                }else if (single[i->v] + i->w > mx1) {
                    mx1 = single[i->v] + i->w;
                    ed[u] = st[i->v];
                }
            }
        }
        single[u] = mx0;
        both[u] = mx0 + mx1;
    };

    dfs(rt, -1, dfs);

    uint res_st = 0, res_ed = 0, res_length = 0;
    for (uint i = 0; i < config.n; i++) {
        if (res_length < both[i]) {
            res_st = st[i];
            res_ed = ed[i];
            res_length = both[i];
        }
    }

    stack<tuple<uint, uint, uint, decltype(graph.begin(rt))>> stk;
    stk.emplace(res_st, 0, -1, graph.begin(res_st));
    while (!stk.empty()) {
        auto [u, step, fa, i] = stk.top();
        if (u == res_ed) {
            break;
        }
        switch (step) {
            case 0:
                if(i->nxt == nullptr) {
                    get<1>(stk.top())++;
                }else {
                    get<3>(stk.top()) = get<3>(stk.top())->nxt;
                }
                if (i->v != fa) {
                    stk.emplace(i->v, 0, u, graph.begin(i->v));
                }
            break;
            case 1:
                stk.pop();
            break;
            default:
                throw runtime_error("Unexpected Step!");
        }
    }

    assert(!stk.empty());

    vector<uint> path;
    while (!stk.empty()) {
        path.push_back(get<0>(stk.top()));
        stk.pop();
    }

    vector<uint> dis(path.size() - 1);
    [&graph, &dis, &path] {
        for (uint i = 0; i < dis.size(); i++) {
            for (auto j = graph.begin(path[i]); j; j = j->nxt) {
                if (j->v == path[i + 1]) {
                    dis[i] = j->w;
                    break;
                }
            }
        }
    }();

    // assert(res_length > config.s);

    uint l = 0, r = path.size() - 1;
    uint l_len = 0, r_len = 0, len = res_length;
    while (l < r && len > config.s) {
        if (l_len + dis[l] <= r_len + dis[r - 1]) {
            l_len += dis[l];
            len -= dis[l];
            l++;
        }else {
            r_len += dis[r - 1];
            len -= dis[r - 1];
            r--;
        }
    }

    vector<bool> flag(config.n);
    for (uint i = l; i <= r; i++) {
        flag[path[i]] = true;
    }

    uint res = max(l_len, r_len);

    auto dfs2 = [&graph, &flag, &res] (const uint u, const uint fa, const uint dis, auto && dfs2) -> void {
        for(auto i = graph.begin(u); i; i = i->nxt) {
            if (i->v != fa && !flag[i->v]) {
                dfs2(i->v, u, dis + i->w, dfs2);
            }
        }
        res = max(res, dis);
    };

    for (uint i = l; i <= r; i++) {
        dfs2(path[i], -1, 0, dfs2);
    }

    return res;
}
