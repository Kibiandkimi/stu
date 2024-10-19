//
// Created by kibi on 24-10-9.
//
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <numeric>
#include <set>
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

using Query = tuple<uint, uint>;

class Config {
public:
    uint n, q;
    vector<uint> h;
    vector<Query> queries;
};

vector<uint> solve(const Config &);

int main() {
    freopen("jump.in", "r", stdin);
    freopen("jump.out", "w", stdout);

    auto n = read<uint>();
    vector<uint> h(n);
    for (auto &i : h) {
        i = read<uint>();
    }
    auto q = read<uint>();
    vector<Query> queries(q);
    for (auto &i : queries) {
        i = {read<uint>() - 1, read<uint>() - 1};
    }
    Config config{n, q, move(h), move(queries)};
    auto ans = solve(config);
    for (auto &i : ans) {
        printf("%u\n", i);
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}

vector<uint> solve(const Config &config) {
    vector<uint> res;
    res.reserve(config.queries.size());
    for (auto &i : config.queries) {
        auto [l, r] = i;
        res.emplace_back(3);
        for (uint b = l + 1; b < r; b++) {
            for (uint c = b + 1; c <= r; c++) {
                for (uint a = b - 1; a != -1 && a >= l && b - a <= c - b; a--) {
                    res.back() = max(res.back(), config.h[a] + config.h[b] + config.h[c]);
                }
            }
        }
    }
    return res;
}

