//
// Created by kibi on 24-10-4.
//
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <numeric>
#include <sys/types.h>
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
    uint n;
    vector<uint> arr;
};

ull solve(const Config&);

int main() {
    freopen("merge.in", "r", stdin);
    freopen("merge.out", "w", stdout);

    auto T = read<uint>();
    while (T--) {
        auto n = read<uint>();
        Config config{n, vector<uint>(n)};
        for_each(config.arr.begin(), config.arr.end(), [](uint &x) {x = read<uint>();});
        printf("%llu\n", solve(config));
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}

ull solve(const Config& config) {
    if (config.n == 2) {
        return min(config.arr.front(), config.arr.back());
    }
    if (config.n == 3) {
        uint l = min(config.arr[0], config.arr[1]), ls = config.arr[0] + config.arr[1];
        uint r = min(config.arr[1], config.arr[2]), rs = config.arr[1] + config.arr[2];
        return min(l + min(ls, config.arr[2]), r + min(rs, config.arr[0]));
    }
    if (config.n <= 7) {
        vector<vector<ull>> f(config.n, vector<ull>(config.n));
        vector<ull> sum(config.n);
        partial_sum(config.arr.begin(), config.arr.end(), sum.begin());
        auto s = [&sum](const uint l, const uint r) {
            return l == 0 ? sum[r] : sum[r] - sum[l - 1];
        };
        for (uint len = 2; len <= config.n; ++len) {
            for (uint l = 0; l + len <= config.n; ++l) {
                f[l][l + len - 1] = 1e18;
                for (uint mid = l + 1; mid < l + len; ++mid) {
                    f[l][l + len - 1] = min(
                        f[l][l + len - 1],
                        f[l][mid - 1] + f[mid][l + len - 1] + min(
                            s(l, mid - 1), s(mid, l + len - 1)
                    ));
                }
            }
        }
        return f.front().back();
    }
    if (all_of(config.arr.begin(), config.arr.end(), [](auto x) {return x == 0 || x == 1;})) {
        uint res = -1;
        for_each(config.arr.begin(), config.arr.end(), [&res](auto x) {res += x;});
        return res == -1 ? 0 : res;
    }
    ull res = 0, mx = 0;
    for_each(config.arr.begin(), config.arr.end(), [&res, &mx](auto x) {
        res += x;
        mx = max(mx, static_cast<ull>(x));
    });
    return res - mx;
}