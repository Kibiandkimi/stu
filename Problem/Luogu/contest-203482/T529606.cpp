//
// Created by Kibi on 24-10-20.
//
#include <cctype>
#include <cstdio>
#include <numeric>
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

enum QueryType {
    modify = 1,
    query = 2,
};

using Opt = std::tuple<QueryType, uint, uint>;

class Config {
public:
    uint n, q, c1, c2, w1, w2;
    vec<ull> a;
    vec<Opt> opts;
};

vec<bool> solve(const Config &);

int main() {
    // freopen(R"(C:\Users\Lenovo\AppData\Local\Temp\seq5.in)", "r", stdin);

    auto
            n = read<uint>(),
            q = read<uint>(),
            c1 = read<uint>(),
            c2 = read<uint>(),
            w1 = read<uint>(),
            w2 = read<uint>();
    Config config{n, q, c1, c2, w1, w2};
    config.a.reserve(n), config.opts.reserve(q);
    for (uint i = 0; i < n; i++) {
        config.a.emplace_back(read<ull>());
    }
    for (uint i = 0; i < q; i++) {
        auto type = read<uint>(), x = read<uint>(), y = read<uint>();
        config.opts.emplace_back(type == 1 ? modify : query, x, y);
    }
    auto ans = solve(config);
    for (auto i : ans) {
        printf(i ? "cont\n" : "tetris\n");
    }

    return 0;
}

vec<bool> solve(const Config &config) {
    auto a = config.a;
    vec<bool> res;
    vec<uint> red, blue;
    for (auto &i : config.opts) {
        auto [type, x, y] = i;
        switch (type) {
            case modify:
                a[x - 1] += y;
                break;
            case query: {
                vec<ull> sum(y - x + 1);
                std::partial_sum(a.begin() + x - 1, a.begin() + y, sum.begin());

                auto get = [&sum](uint begin, uint len) {
                    return begin == 0 ? sum[len - 1] : sum[begin + len - 1] - sum[begin - 1];
                };

                auto check_blue = [&](uint l, uint r) { // please confirm the range yourself
                    return get(l - x, r - l + 1) >= config.w2;
                };

                auto check_red = [&](uint l, uint r) { // please confirm the range yourself
                    return get(l - x, r - l + 1) <= config.w1;
                };

                auto check = [&] {
                    ull mx = 0;
                    for (uint j = x; j <= y; j++) {
                        mx = std::max(mx, a[j - 1]);
                    }
                    return mx <= config.w1;
                };

                if (y - x + 1 <= config.c2) {
                    if (check_blue(x, y)) {
                        res.push_back((y - x + 1 <= config.c1) && check_red(x, y) && check());
                    } else {
                        res.push_back(check());
                    }
                } else {
                    uint blue_l = -1, blue_r;
                    for (uint j = x + config.c2 - 1; j <= y; j++) {
                        if (check_blue(j + 1 - config.c2, j)) {
                            if (blue_l == -1) {
                                blue_l = j + 1 - config.c2;
                            }
                            blue_r = j;
                        }
                    }
                    if (blue_l == -1) {
                        res.push_back(check());
                    } else {
                        res.push_back((blue_r - blue_l + 1 <= config.c1) && check_red(blue_l, blue_r) && check());
                    }
                }
            }
        }
    }

    return res;
}
