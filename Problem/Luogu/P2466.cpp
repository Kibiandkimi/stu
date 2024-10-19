//
// Created by kibi on 24-9-7.
//
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <sys/types.h>
#include <tuple>
#include <vector>
using namespace std;

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

class Egg {
public:
    int x, y, v;
};

class Config {
public:
    int x;
    vector<Egg> eggs;
};

long long solve(const Config&);

int main() {
    const auto n = read<uint>();
    const auto x = read<int>();
    Config config{x, vector<Egg>(n)};
    for (auto &i : config.eggs) {
        i.x = read<int>();
    }
    for (auto &i : config.eggs) {
        i.y = read<int>();
    }
    for (auto &i : config.eggs) {
        i.v = read<int>();
    }

    const auto ans = solve(config);

    printf("%.3lf\n", ans / 1000.0);
}

template<typename T>
T abs(const T a, const T b) {
    return a < b ? b - a : a - b;
}

long long solve(const Config &config) {
    auto eggs = config.eggs;
    sort(eggs.begin(), eggs.end(), [](const auto &a, const auto &b) {return a.x < b.x;});
    vector<vector<tuple<long long, long long>>> f(eggs.size(), vector<tuple<long long, long long>>(eggs.size()));

    vector<long long> sum_v(eggs.size(), eggs.front().v);
    for (size_t i = 1; i < eggs.size(); i++) {
        sum_v[i] = sum_v[i - 1] + eggs[i].v;
    }

    auto get_v = [&sum_v](const uint l, const uint r) {
        return sum_v.back() - (sum_v[r] - (l > 0 ? sum_v[l - 1] : 0));
    };

    for (size_t i = 0; i < eggs.size(); i++) {
        f[i][i] = {eggs[i].y - abs(config.x, eggs[i].x) * sum_v.back(), eggs[i].y - abs(config.x, eggs[i].x) * sum_v.back()};
    }
    for (size_t len = 2; len <= eggs.size(); len++) {
        for (uint l = 0, r = len - 1; l <= eggs.size() - len; l++, r++) {
            f[l][r] = {
                max(get<0>(f[l + 1][r]) - abs(eggs[l + 1].x, eggs[l].x) * get_v(l + 1, r),
                    get<1>(f[l + 1][r]) - abs(eggs[r].x, eggs[l].x) * get_v(l + 1, r))
                + eggs[l].y,
                max(get<0>(f[l][r - 1]) - abs(eggs[l].x, eggs[r].x) * get_v(l, r - 1),
                    get<1>(f[l][r - 1]) - abs(eggs[r - 1].x, eggs[r].x) * get_v(l, r - 1))
                + eggs[r].y
            };
        }
    }

    return max(get<0>(f[0].back()), get<1>(f[0].back()));
}
