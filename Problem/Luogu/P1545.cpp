//
// Created by Kibi on 24-10-17.
//
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

using rng = tuple<uint, uint>; // range -> l, r

class Config {
public:
    uint n, l, a, b;
    vec<rng> rngs;
};

int solve(const Config &);

int main() {
    auto n = read<uint>(), l = read<uint>(), a = read<uint>(), b = read<uint>();
    Config config{n, l, a, b, .rngs{n, {0, 0}}};
    for (auto &i : config.rngs) {
        i = {read<uint>(), read<uint>()};
    }
    auto ans = solve(config);
    printf("%d\n", ans);
    return 0;
}

class SegTree {
    class Node {
    public:
        uint l, r;
        Node *ls{nullptr}, *rs{nullptr};
        uint val;

        void update() {
            val = min(ls->val, rs->val);
        }
    };

    Node *rt;

    template<typename Iterator>
    void build(Node *u, uint l, uint r, Iterator &it) {
        u->l = l, u->r = r;
        if (l == r) {
            u->val = *it++;
            return;
        }

        uint mid = (l + r) / 2;
        u->ls = new Node, u->rs = new Node;
        build(u->ls, l, mid, it);
        build(u->rs, mid + 1, r, it);
        u->update();
    }

    uint query(Node *u, uint l, uint r) {
        if (l <= u->l && u->r <= r) {
            return u->val;
        }

        uint mid = (u->l + u->r) / 2;
        uint res = 1e9;
        if (l <= mid) {
            res = min(res, query(u->ls, l, r));
        }
        if (r > mid) {
            res = min(res, query(u->rs, l, r));
        }
        return res;
    }

public:
    template<typename Iterator>
    SegTree(uint n, Iterator it) {
        build(rt = new Node, 0, n - 1, it);
    }

    ~SegTree() = default; // TODO

    void modify(uint pos, uint val) {
        auto now = rt;
        stack<Node*> stk;
        while (now->l != now->r) {
            stk.push(now);
            now = pos <= (now->l + now->r) / 2 ? now->ls : now->rs;
        }
        now->val = val;
        while (!stk.empty()) {
            stk.top()->update();
            stk.pop();
        }
    }

    uint query(uint l, uint r) {
        return query(rt, l, r);
    }
};


int solve(const Config &config) {
    vec<int> cnt(config.l + 1);
    vec<bool> flag(config.l + 1);
    for (auto &i : config.rngs) {
        cnt[get<0>(i) + 1]++;
        cnt[get<1>(i)]--;
    }
    for (uint i = 0, temp = 0; i <= config.l; i++) {
        temp += cnt[i];
        flag[i] = temp == 0;
    }

    vec<uint> f(config.l + 1, 1e9);
    auto temp = vec<uint>(config.l + 1, 1e9);
    SegTree seg_tree(config.l + 1, temp.begin());
    // delete &temp;
    seg_tree.modify(0, 0);
    f[0] = 0;
    for (int i = config.a * 2; i <= config.l; i += 2) {
        if (!flag[i]) {
            continue;
        }
        int l = max(0, i - 2 * static_cast<int>(config.b)), r = static_cast<int>(i - 2 * config.a);
        f[i] = seg_tree.query(l, r) + 1;
        seg_tree.modify(i, f[i]);
    }

    auto res = f[config.l];
    return res >= 1e9 ? -1 : static_cast<int>(res);
}
