//
// Created by Kibi on 24-9-29.
//
#include <cctype>
#include <cstdio>
#include <sys/types.h>
#include <vector>
using namespace std;

using uint = unsigned int;

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
    uint n, h;
    vector<int> f, d, t;
};

uint solve(const Config&);

int main() {
    auto n = read<uint>(), h = read<uint>();
    Config config{n, h, vector<int>(n), vector<int>(n), vector<int>(n - 1)};
    for (auto &i : config.f) {
        i = read<int>();
    }
    for (auto &i : config.d) {
        i = read<int>();
    }
    for (auto &i : config.t) {
        i = read<int>();
    }
    printf("%u\n", solve(config));
}

uint solve(const Config &config) {
    vector<vector<int>> dp(config.n + 1, vector<int>(config.h * 12 + 1, -1e9));
    vector<uint> t = {0};
    dp[0][0] = 0;
    t.insert(t.end(), config.t.begin(), config.t.end());
    int res = 0;
    for (int i = 1; i <= config.n; ++i) {
        for (int pre = t[i - 1]; pre <= config.h * 12; ++pre) {
            for (int j = 0; j <= config.h * 12 - pre; ++j) {
                if ((1 + (j - 1)) * (j - 1) * config.d[i - 1] / 2 <= j * config.f[i - 1]) {
                    dp[i][j + pre] = max(
                        dp[i][j + pre],
                        dp[i - 1][pre - t[i - 1]] + j * config.f[i - 1] - (1 + (j - 1)) * (j - 1) * config.d[i - 1] / 2
                        );
                }
                res = max(res, dp[i][j + pre]);
                // if ((1 + (j - t[i - 1] - 1)) * (j - t[i - 1] - 1) * config.d[i - 1] / 2 > (j - t[i - 1]) * config.f[i - 1]) {
                //     dp[i][j] = dp[i][j - 1];
                // }else {
                //     dp[i][j] = dp[i - 1][j - t[i - 1]] + (j - t[i - 1]) * config.f[i - 1] - (1 + (j - t[i - 1] - 1)) * (j - t[i - 1] - 1) * config.d[i - 1] / 2;
                //     res = max(res, dp[i][j]);
                // }
            }
        }
    }
    return res;
}
