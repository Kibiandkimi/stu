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
#include <sys/types.h>
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
    uint n, m;
    vector<uint> val;
};

int solve(const Config &);

int main() {
    auto n = read<uint>(), m = read<uint>();
    Config config{n, m, vector<uint>(n)};
    for (auto &i : config.val) {
        i = read<int>();
    }
    auto ans = solve(config);
    ans != -1 ? printf("%d\n", ans) : printf("Error!");
    return 0;
}

class Node {
public:
    Node *pre, *suc;
    uint id;
    int val;
};

class Cmp {
public:
    bool operator()(const tuple<uint, int> &x, const tuple<uint, int> &y) const {
        return get<1>(x) < get<1>(y);
    }
};

int solve(const Config &config) {
    if (config.n / 2 < config.m) {
        return -1;
    }

    vector<Node*> nodes(config.n, nullptr);
    uint cnt = 0;
    for (auto &i : nodes) {
        i = new Node {nullptr, nullptr, cnt++};
        i->val = config.val[cnt - 1];
        if (cnt != 1) {
            i->pre = nodes[cnt - 2];
            nodes[cnt - 2]->suc = i;
        }
    }
    nodes.front()->pre = nodes.back();
    nodes.back()->suc = nodes.front();
    priority_queue<tuple<uint, int>, vector<tuple<uint, int>>, Cmp> pq;

    cnt = 0;
    for (auto &i : nodes) {
        auto temp = make_tuple<uint, int>(0, 0);
        get<1>(temp) = config.val[cnt];
        get<0>(temp) = cnt++;
        pq.emplace(temp);
    }

    vector<bool> vis(config.n);
    int res = 0;
    for (uint i = 0; i < config.m; i++) {
        while (vis[get<0>(pq.top())]) {
            pq.pop();
        }
        auto [id, val] = pq.top();
        pq.pop();
        res += val;
        vis[nodes[id]->pre->id] = vis[nodes[id]->suc->id] = true;
        nodes[id]->val = nodes[id]->pre->val + nodes[id]->suc->val - nodes[id]->val;
        pq.emplace(id, nodes[id]->val);
        nodes[id]->pre = nodes[id]->pre->pre;
        nodes[id]->suc = nodes[id]->suc->suc;
        nodes[id]->pre->suc = nodes[id];
        nodes[id]->suc->pre = nodes[id];
    }
    return res;
}

