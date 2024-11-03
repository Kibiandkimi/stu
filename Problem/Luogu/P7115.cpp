//
// Created by kibi on 24-11-2.
//
// TODO
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <stack>
#include <sys/types.h>
#include <tuple>
#include <vector>

template<typename T>
using vec = std::vector<T>;
using u32 = const unsigned int;
using u64 = const unsigned long long;
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

class Config {
public:
    u32 n, m;
    vec<vec<uint>> col;
};

using OptList = vec<std::tuple<uint, uint>>;

OptList solve(const Config &);

int main() {
    u32 n = read<uint>(), m = read<uint>();
    Config config{n, m, .col{n, vec<uint>(m)}};
    for (auto &i : config.col) {
        i.reserve(m);
        for (auto &j : i) {
            j = read<uint>();
        }
    }
    auto opts = solve(config);
    printf("%lu\n", opts.size());
    for (auto &i : opts) {
        printf("%u %u\n", std::get<0>(i) + 1, std::get<1>(i) + 1);
    }
    return 0;
}

OptList get_up(vec<uint> &x, u32 y, u32 current, u32 full, u32 empty) {
    OptList res;
    std::stack<uint> stk;
    uint cnt = 0;
    for (auto &i : x) {
        i == y ? cnt++ : cnt;
    }
    for (uint i = 0; i < cnt; i++) {
        res.emplace_back(full, empty);
    }
    uint pos = 0;
    for (uint i = 0; i < cnt; i++) {
        while (*(x.end() - pos - 1) != y) {
            res.emplace_back(current, empty);
            pos++;
            stk.push(*(x.end() - pos));
        }
        res.emplace_back(current, full);
        pos++;
    }
    while (pos != cnt) {
        *(x.end() - pos) = stk.top();
        stk.pop();
        res.emplace_back(empty, current);
        pos--;
    }
    for (uint i = 0; i < cnt; i++) {
        res.emplace_back(full, current);
    }
    for (uint i = 0; i < cnt; i++) {
        *(x.end() - pos) = y;
        pos--;
        res.emplace_back(empty, full);
    }

    return move(res);
}

OptList get_all(const vec<vec<uint>> &stks, u32 y, u32 empty) {
    OptList res;
    for (uint i = 0; i < stks.size(); i++) {
        if (i == empty) {
            continue;
        }
        for (auto j = stks[i].rbegin(); j != stks[i].rend(); ++j) {
            if (*j == y) {
                res.emplace_back(i, empty);
            } else {
                break;
            }
        }
    }
    return move(res);
}

OptList make_empty(vec<vec<uint>> &stks, u32 y, u32 to_empty) {
    OptList res;

    uint pos = stks[to_empty].size() - 1;
    while (pos != -1 && stks[to_empty][pos] == y) {
        pos--;
    }
    if (pos == -1) {
        return res;
    }

    for (uint i = 0; i < stks.size(); i++) {
        if (i == to_empty) {
            continue;
        }
        std::stack<uint> stk;
        for (auto j = stks[i].rbegin(); j != stks[i].rend(); ++j) {
            if (*j == y) {
                res.emplace_back(to_empty, i);
                // *j = stks[to_empty][pos--];
                stk.push(stks[to_empty][pos--]);
            } else {
                break;
            }
        }
        for (auto j = stks[i].rbegin(); !stk.empty(); ++j) {
            *j = stk.top();
            stk.pop();
        }
    }

    return move(res);
}

OptList solve(const Config &config) {
    OptList opts;

    vec<vec<uint>> stks = config.col;

    auto add = [](OptList &opts, OptList opt) {
        opts.insert(opts.end(), opt.begin(), opt.end());
    };

    for (uint empty = config.n; empty > 1; empty--) {
        for (uint i = 0; i < empty; i++) {
            add(opts, get_up(stks[i], empty, i, i == 0 ? empty == config.n ? config.n - 1 : config.n : 0, empty));
            // opts.emplace_back(0, 0);
        }
        add(opts, get_all(stks, empty, empty));
        // opts.emplace_back(0, 0);
        add(opts, make_empty(stks, empty, empty - 1));
        // opts.emplace_back(0, 0);
        stks.pop_back();
    }

    return opts;
}
