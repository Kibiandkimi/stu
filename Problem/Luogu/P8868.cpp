//
// Created by kibi on 24-10-31.
//
// TODO not finish (begin)
#include <cctype>
#include <cstdio>
#include <stack>
#include <sys/types.h>
#include <tuple>
#include <vector>

template<typename T>
using vec = std::vector<T>;
using ull = unsigned long long;
using std::tuple;

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

using Query = std::tuple<uint, uint>;

class Config {
public:
    uint T, n, Q;
    vec<uint> a, b;
    vec<Query> queries;
};

vec<ull> solve(const Config&);

int main() {
    auto T = read<uint>(), n = read<uint>();
    Config config{T, n};
    config.a.reserve(n), config.b.reserve(n);
    for (uint i = 0; i < n; i++) {
        config.a.emplace_back(read<uint>());
    }
    for (uint i = 0; i < n; i++) {
        config.b.emplace_back(read<uint>());
    }
    config.Q = read<uint>();
    config.queries.reserve(config.Q);
    for (uint i = 0; i < config.Q; i++) {
        auto l = read<uint>(), r = read<uint>();
        config.queries.emplace_back(l, r);
    }
    auto res = solve(config);
    for (auto &i : res) {
        printf("%llu\n", i);
    }
    return 0;
}

vec<ull> solve(const Config &config) {
    ull res = 0;

    /*auto calc = [&](uint l, uint r, auto &&calc) -> void {
        using std::get;
        if (l != r) {
            auto mid = (l + r) >> 1;
            calc(l, mid, calc), calc(mid + 1, r, calc);
            std::stack<tuple<uint, uint>> stk1, stk2;
            for (uint i = l; i <= mid; i++) {
                while (!stk1.empty() && get<0>(stk1.top()) < config.a[i]) {
                    stk1.pop();
                }
            }
        } else {
            res += 1ull * config.a[l] * config.b[l];
        }
    };*/

    for (auto &i : config.queries) {
        auto [l, r] = i;


    }
}
