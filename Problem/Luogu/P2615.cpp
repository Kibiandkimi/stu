//
// Created by kibi on 24-11-3.
//
#include <cctype>
#include <cstdio>
#include <sys/types.h>
#include <vector>

template<typename T>
using vec = std::vector<T>;
using u32 = const unsigned int;

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
    uint n;
};

vec<vec<uint>> solve(const Config &);

int main() {
    auto ans = solve({read<uint>()});
    for (auto &i : ans) {
        for (auto &j : i) {
            printf("%u ", j);
        }
        printf("\n");
    }
    return 0;
}

vec<vec<uint>> solve(const Config &config) {
    uint x = 0, y = config.n / 2;
    vec<vec<uint>> ans(config.n, vec<uint>(config.n));
    ans[x][y] = 1;
    for (uint i = 1; i < config.n * config.n; i++) {
        if (x == 0 && y != config.n - 1) {
            x = config.n - 1;
            y++;
        } else if (x != 0 && y == config.n - 1) {
            y = 0;
            x--;
        } else if (x == 0 && y == config.n - 1) {
            x++;
        } else if (!ans[x - 1][y + 1]) {
            x--;
            y++;
        } else {
            x++;
        }
        ans[x][y] = i + 1;
    }
    return ans;
}
