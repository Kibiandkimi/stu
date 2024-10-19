//
// Created by Kibi on 24-10-17.
//
//
// Created by Kibi on 24-10-16.
//
//
// Created by Kibi on 24-10-16.
//
// TODO
// the wrong solution
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

using Equip = tuple<uint, uint>;

class Config {
public:
    uint n;
    vec<Equip> equips;
};

uint solve(const Config &);

int main() {
    auto n = read<uint>();
    Config config{n, .equips{n, {0, 0}}};
    for (auto &i : config.equips) {
        i = {read<uint>(), read<uint>()};
    }
    auto ans = solve(config);
    printf("%u\n", ans);
    return 0;
}

class DSUNode{
    DSUNode *fa;
public:
    explicit DSUNode(uint val):fa(this), val(val){}
    uint val;

    DSUNode* find(){
        return fa == this ? this : fa->find();
    }

    void merge(DSUNode *v){
        fa = v;
    }
};

uint solve(const Config &config) {
    vec<DSUNode*> nodes;
    nodes.reserve(config.n);
    for (uint i = 0; i < config.n; i++) {
        nodes.push_back(new DSUNode(i));
    }
    vec<bool> vis(config.n);
    for (auto &i : config.equips) {
        auto [a, b] = i;
        if (a == b) {
            vis[nodes[a - 1]->find()->val] = true;
            continue;
        }
        if (a > b) {
            swap(a, b);
        }
        vis[a] = true;
        nodes[a]->find()->merge(nodes[b]);
    }

    for (auto &i : nodes) {

    }
}
