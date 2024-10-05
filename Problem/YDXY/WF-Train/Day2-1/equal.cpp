//
// Created by kibi on 24-10-4.
//
#include <algorithm>
#include <cctype>
#include <cstdio>
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

class Config {
public:
    uint n, m;
    vector<tuple<uint, uint>> x, y;
};

vector<vector<uint>> solve(const Config&);

int main() {
    freopen("equal.in", "r", stdin);
    freopen("equal.out", "w", stdout);

    auto n = read<uint>(), m = read<uint>();
    Config config{n, m, vector<tuple<uint, uint>>(n), vector<tuple<uint, uint>>(n)};
    for_each(config.x.begin(), config.x.end(), [](auto& x) {x = {read<uint>(), read<uint>()};});
    for_each(config.y.begin(), config.y.end(), [](auto& y) {y = {read<uint>(), read<uint>()};});
    auto ans = solve(config);
    for (auto &x : ans) {
        for (auto &y : x) {
            printf("%u ", y);
        }
        printf("\n");
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}

uint calc(uint a, uint b, uint c, uint d) {
    if (b <= d) {
        if (a >= c) {
            return b - a + 1;
        }
        return b - c + 1;
    }
    return calc(c, d, a, b);
}

vector<vector<uint>> solve(const Config& config) {
    if (config.n == config.m && config.n == 1) {
        return {{calc(
            get<0>(config.x.front()),
            get<1>(config.x.front()),
            get<0>(config.y.front()),
            get<1>(config.y.front())
        )}};
    }
//    if (config.n == config.m && config.n == 2) {
//        uint res = 0;
//        for (uint i = get<0>(config.x[0]); i <= get<1>(config.x[0]); i++) {
//            for (uint j = get<0>(config.x[1]); j <= get<1>(config.x[1]); j++) {
//                for (uint k = get<0>(config.y[0]); k <= get<1>(config.y[0]); k++) {
//                    for (uint l = get<0>(config.y[1]); l <= get<1>(config.y[1]); l++) {
//                        if (i + j == k + l) {
//                            res++;
//                        }
//                    }
//                }
//            }
//        }
//        return {{},{res}};
//    }
}