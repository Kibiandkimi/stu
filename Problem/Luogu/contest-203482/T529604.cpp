//
// Created by Kibi on 24-10-20.
//
#include <cctype>
#include <cstdio>
#include <sys/types.h>
#include <tuple>
#include <vector>

using ull = unsigned long long;
using ll = long long;
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

using Query = std::tuple<uint, uint, ll>;

class Config {
public:
    uint n, q;
    ll W;
    vec<ll> a; // attack
    vec<Query> queries;
};

vec<ull> solve(const Config&);

int main() {
    // freopen(R"(C:\Users\Lenovo\AppData\Local\Temp\wxyt4.in)", "r", stdin);

    auto n = read<uint>(), q = read<uint>();
    auto W = read<ll>();
    Config config{n, q, W /*, vec<ll>(n), vec<Query>(q)*/};
    config.a.reserve(n), config.queries.reserve(q);
    for (uint i = 0; i < n; i++) {
        config.a.push_back(read<ll>());
    }
    for (uint i = 0; i < q; i++) {
        auto l = read<uint>(), r = read<uint>();
        auto d = read<ll>();
        config.queries.emplace_back(l, r, d);
    }
    auto ans = solve(config);
    for (auto &i : ans) {
        printf("%llu\n", i);
    }
    return 0;
}

class SegTree {
    class Node {
    public:
        uint l, r;
        Node *ls, *rs;
        ll val, tag;

        void modify(ll t_val) {
            val += (r - l + 1) * t_val;
            tag += t_val;
        }

        void update() {
            val = ls->val + rs->val + tag * (r - l + 1);
        }

        /*void push_down() {
            ls->modify(tag);
            rs->modify(tag);
            tag = 0;
        }*/
    };

    Node *rt;

    template<typename It>
    void build (Node *u, uint l, uint r, It &it) {
        u->l = l, u->r = r, u->tag = 0;
        if (l == r) {
            u->val = *it++;
            return;
        }

        uint mid = (l + r) / 2;
        u->ls = new Node, u->rs = new Node;
        build (u->ls, l, mid, it);
        build (u->rs, mid + 1, r, it);
        u->update();
    }

    static void modify (Node *u, uint l, uint r, ll val) {
        if (l <= u->l && u->r <= r) {
            u->modify(val);
            return;
        }

        // u->push_down();

        uint mid = (u->l + u->r) / 2;

        if (l <= mid) {
            modify(u->ls, l, r, val);
        }
        if (r > mid) {
            modify(u->rs, l, r, val);
        }

        u->update();
    }

    static ll query (const Node *u, uint l, uint r) {
        if (l <= u->l && u->r <= r) {
            return u->val;
        }

        uint mid = (u->l + u->r) / 2;
        ll ans = u->tag * (std::min(r, u->r) - std::max(l, u->l) + 1);
        // if (l <= mid) {
        ans += query(u->ls, l, r)/* + (mid - std::max(l, u->l) + 1) * u->tag*/;
        // }
        if (r > mid) {
            ans += query(u->rs, l, r)/* + (std::min(r, u->r) - mid) * u->tag*/;
        }

        return ans;
    }

public:
    template<typename It>
    SegTree(uint siz, It it) {
        build(rt = new Node, 1, siz, it);
    }

    void modify(uint l, uint r, ll val) const {
        modify(rt, l, r, val);
    }

    ll query(uint l, uint r) const {
        return query(rt, l, r);
    }
};

vec<ull> solve(const Config &config) {

    SegTree seg_tree(config.n, config.a.begin());

    vec<ull> ans;
    ans.reserve(config.q);

    for (auto &i : config.queries) {
        auto [l, r, d] = i;
        seg_tree.modify(l, r, d);
        auto res = seg_tree.query(1, config.n);
        auto W = config.W;
        uint cnt = 0;
        while (W > res) {
            W -= res;
            res *= 2;
            cnt++;
        }
        ll temp_res = cnt * config.n;

        auto check = [&seg_tree, cnt, W](uint k) {
            return seg_tree.query(1, k) * (1ll << cnt) < W;
        };

        l = 1, r = config.n;
        while (l <= r) {
            const uint mid = (l + r) >> 1;
            if (check(mid)) {
                l = mid + 1;
            }else {
                r = mid - 1;
            }
        }

        temp_res += l - 1;
        ans.push_back(temp_res);
    }

    return ans;
}
