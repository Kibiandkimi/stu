//
// Created by kibi on 24-11-2.
//
// TODO

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <sys/types.h>
#include <tuple>
#include <vector>

template<typename T>
using vec = std::vector<T>;
using i32 = const int;
using u32 = const unsigned int;
using u64 = const unsigned long long;
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

using Step = tuple<uint, bool>;

class Config {
public:
    u32 n, k;
    vec<uint> siz;
    vec<Step> steps;
};

i32 solve(const Config &);

int main() {
    u32 n = read<uint>(), k = read<uint>();
    Config config{n, k, vec<uint>(k), vec<tuple<uint, bool>>(n)};
    for (auto &i : config.siz) {
        i = read<uint>();
    }
    for (auto &i : config.steps) {
        u32 x = read<uint>();
        int y = read<int>();
        i = {x, y == 1};
    }
    auto ans = solve(config);
    printf("%d\n", ans);

    return 0;
}

using std::get;

constexpr uint MOD = 1'000'000'007;

void add(uint &a, const uint b) {
    a = a + b >= MOD ? a + b - MOD : a + b;
}

int trans(const bool flag) {
    return flag ? 1 : -1;
}

uint quick_pow(uint base, uint exp) {
    uint res = 1;
    while (exp) {
        if (exp & 1) {
            res *= base;
        }
        base *= base;
        exp >>= 1;
    }
    return res;
}

i32 solve(const Config &config) {
    uint res = 0;

    vec<int> mx_moving(config.k), mn_moving(config.k);
    vec<int> moving(config.k);

    for (auto &step : config.steps) {
        moving[get<0>(step) - 1] += trans(get<1>(step));
        mx_moving[get<0>(step) - 1] = std::max(mx_moving[get<0>(step) - 1], moving[get<0>(step) - 1]);
        mn_moving[get<0>(step) - 1] = std::min(mn_moving[get<0>(step) - 1], moving[get<0>(step) - 1]);
    }

    // judge of -1
    if (std::all_of(moving.begin(), moving.end(), [](auto &v) {return v == 0;})) {
        bool flag = true;
        for (uint i = 0; i < config.k; ++i) {
            if (mx_moving[i] - mn_moving[i] >= config.siz[i]) {
                flag = false;
                break;
            }
        }
        if (flag) {
            return -1;
        }
    }

    // enum the beginning point and calc the step

    auto check = [&mx_moving, &mn_moving, &config](const vec<uint> &pos) {
      for (uint i = 0; i < pos.size(); ++i) {
            if (static_cast<int>(pos[i]) + mn_moving[i] < 0 || pos[i] + mx_moving[i] >= config.siz[i]) {
                return false;
            }
        }
        return true;
    };

    uint mxi = 1;
    for (auto &i : config.siz) {
        mxi *= i;
    }

    for (uint i = 0; i < mxi; i++) {
        vec<uint> pos;
        uint temp = i;
        for (auto &j : config.siz) {
            pos.push_back(temp % j);
            temp /= j;
        }
        uint temp_res = 0;
        while (check(pos)) {
            for (uint j = 0; j < config.k; ++j) {
                pos[j] += moving[j];
            }
            add(temp_res, config.n);
        }
        for (auto &j : config.steps) {
            if (pos[get<0>(j) - 1] + trans(get<1>(j)) >= config.siz[get<0>(j) - 1]) { // (0 - 1) -> MAX_UINT >= siz
                break;
            }
            add(temp_res, 1);
            pos[get<0>(j) - 1] += trans(get<1>(j));
        }
        add(res, temp_res);
    }

    add(res, mxi);

    return static_cast<int>(res);
}
