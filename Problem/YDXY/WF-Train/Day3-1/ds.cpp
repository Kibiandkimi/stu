//
// Created by kibi on 24-10-5.
//
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <memory>
#include <set>
#include <stdexcept>
#include <sys/types.h>
#include <tuple>
#include <vector>
using namespace std;

using ull = unsigned long long;

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

class Opt {
public:
    enum Type {
        insert = 1,
        erase = 2,
        query = 3,
    };

    Type type;
    uint u, v, x;
};

class Config {
public:
    uint n, m;
    vector<Opt> opts;
};

vector<bool> solve(const Config&);

int main() {
    freopen("ds.in", "r", stdin);
    freopen("ds.out", "w", stdout);

    auto n = read<uint>(), m = read<uint>();
    Config config{n, m, vector<Opt>(m)};
    for (auto& opt : config.opts) {
        auto type = read<uint>(), u = read<uint>(), v = read<uint>();
        switch (type) {
            case 1:
                opt = {Opt::insert, u, v, read<uint>()};
            break;
            case 2:
                opt = {Opt::erase, u, v, read<uint>()};
            break;
            case 3:
                opt = {Opt::query, u, v};
            break;
            default:
                throw runtime_error("invalid operation!");
        }
    }
    auto ans = solve(config);
    for (auto i : ans) {
        printf(i ? "YES\n" : "NO\n");
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}

template <typename Data>
class SegTree {
    /*
    * impl operator +, +=, -= for Data
    * use .clear() instead of -=
    * */

    class Node {
    public:
        Node() : ls(nullptr), rs(nullptr), l(0), r(0), val(Data()){}

        Node *ls, *rs;
        size_t l, r;
        Data val;

        void update() {
            val = ls->val + rs->val;
        }

        void push_down() {
            ls->val += val;
            rs->val += val;
            // val -= Data();
            val.clear();
        }
    };

    template <typename Iterator>
    static void build(Node *u, size_t l, size_t r, Iterator it) {
        u->l = l, u->r = r;
        if (l == r) {
            u->val = move(*(it + l));
            return;
        }
        size_t mid = (l + r) / 2;
        u->ls = new Node(), u->rs = new Node();
        build(u->ls, l, mid, it);
        build(u->rs, mid + 1, r, it);
        u->update();
    }

    template <typename Modifier>
    void modify(Node *u, size_t l, size_t r, Modifier modifier) {
        if (l <= u->l && u->r <= r) {
            modifier(u->val);
            return;
        }

        u->push_down();

        auto mid = (u->l + u->r) / 2;

        if (l <= mid) {
            modify(u->ls, l, r, modifier);
        }
        if (r > mid) {
            modify(u->rs, l, r, modifier);
        }
        u->update();
    }

    const Data& query(Node *u, size_t pos) {
        if (u->l == u->r) {
            return u->val;
        }

        u->push_down();

        size_t mid = (u->l + u->r) / 2;
        if (pos <= mid) {
            return query(u->ls, pos);
        }
        return query(u->rs, pos);
    }

    Node *rt;

    static void destroy (Node *u){
        u->ls ? destroy(u->ls) : static_cast<void>(0);
        u->rs ? destroy(u->rs) : static_cast<void>(0);
        delete u;
    }

public:
    template <typename Iterator>
    SegTree(uint n, Iterator it) {
        build(rt = new Node(), 0, n - 1, it);
    }

    ~SegTree() {
        destroy(rt);
    }

    template <typename Modifier>
    void modify(size_t l, size_t r, Modifier modifier) {
        modify(rt, l, r, modifier);
    }

    const Data& query(size_t pos) {
        return query(rt, pos);
    }
};

class MySet {
public:
    MySet():st(new set<uint>()), st2(new set<uint>()){}
    // ~MySet(){
    //     delete st;
    //     delete st2;
    // }

    // set<uint> *st, *st2;
    unique_ptr<set<uint>> st, st2;

    MySet operator + (const MySet &other) const {
        return {};
    }

    void operator += (const MySet & other) const {
        // if (!other.st->empty()) {
        for (auto &i : *other.st) {
            st->insert(i);
        }
        // }
        // if (!other.st2->empty()) {
        for (auto &i : *other.st2) {
            st->erase(i);
        }
        // }
    }

    void operator -= (const MySet & other) const {
        st->clear();
        st2->clear();
    }

    void clear() const {
        st->clear();
        st2->clear();
    }
};

vector<bool> solve(const Config& config) {
    if (config.n <= 2'000 && config.m <= 2'000) {
        vector<bool> res;
        vector<set<uint>> st_list(config.n);
        for (auto &i : config.opts) {
            switch (i.type) {
                case Opt::insert:
                    for (uint j = i.u - 1; j < i.v; ++j) {
                        st_list[j].insert(i.x);
                    }
                break;
                case Opt::erase:
                    for (uint j = i.u - 1; j < i.v; ++j) {
                        st_list[j].erase(i.x);
                    }
                break;
                case Opt::query: {
                    bool flag = true;
                    for (auto &j : st_list[i.u - 1]) {
                        if (st_list[i.v - 1].find(j) == st_list[i.v - 1].end()) {
                            flag = false;
                            break;
                        }
                    }
                    res.push_back(flag);
                }
            }
        }
        return res;
    }
    if (true || all_of(config.opts.begin(), config.opts.end(), [](auto &opt){
        return opt.type == Opt::query || opt.x <= 10;
    })) {
        vector<bool> res;
        SegTree<MySet> seg_tree(config.n, vector<MySet>(config.n).begin());
        for (auto &i : config.opts) {
            switch (i.type) {
                case Opt::insert:
                    seg_tree.modify(i.u - 1, i.v - 1, [&i](const MySet &u){
                        u.st->insert(i.x);
                    });
                break;
                case Opt::erase:
                    seg_tree.modify(i.u - 1, i.v - 1, [&i](const MySet &u) {
                        u.st2->insert(i.x);
                    });
                break;
                case Opt::query: {
                    bool flag = true;
                    auto &u = seg_tree.query(i.u - 1), &v = seg_tree.query(i.v - 1);
                    for (auto &j : *u.st) {
                        if (v.st->find(j) == v.st->end()) {
                            flag = false;
                            break;
                        }
                    }
                    res.push_back(flag);
                }
            }
        }
        return res;
    }
}