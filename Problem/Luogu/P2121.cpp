//
// Created by kibi on 24-10-19.
//
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <sys/types.h>
#include <tuple>
#include <vector>

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
    uint n, m, K;
    vec<Edge> edges;
};

uint solve(const Config&);

int main() {
    auto n = read<uint>(), m = read<uint>(), K = read<uint>();
    Config config{n, m, K/*, .edges{m, {0, 0, 0}}*/};
    config.edges.reserve(m);
    for (uint i = 0; i < m; i++) {
        uint u = read<uint>(), v = read<uint>(), w = read<uint>();
        config.edges.emplace_back(u, v, w);
    }
    auto ans = solve(config);
    printf("%u\n", ans);
    return 0;
}

class DSUNode{
    DSUNode *fa;
public:
    explicit DSUNode(int val):fa(this), val(val){}
    int val;

    DSUNode* find(){
        return fa == this ? this : fa->find();
    }

    void merge(DSUNode *v){
        fa = v;
    }
};

uint solve(const Config& config) {
    vec<DSUNode*> nodes;
    nodes.reserve(config.n);
    for (int i = 0; i < config.n; i++) {
        nodes.emplace_back(new DSUNode{i});
    }

    using std::get, std::sort;

    auto edges = config.edges;
    sort(edges.begin(), edges.end(), [](const auto &a, const auto &b){return get<2>(a) > get<2>(b);});
    uint cnt = 0, res = 0;
    for (auto &i : edges) {
        auto [u, v, w] = i;
        u--, v--;
        if (nodes[u]->find() != nodes[v]->find()) {
            nodes[u]->find()->merge(nodes[v]->find());
            cnt++;
            res += w;
            if (cnt == config.K) {
                break;
            }
        }
    }

    return res;
}