//
// Created by kibi on 24-10-7.
//
#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

template<typename T>
T read () {
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
    ull n, k;
};

ull solve(const Config&);

int main () {
    freopen("math.in", "r", stdin);
    freopen("math.out", "w", stdout);

    // printf("%llu\n", 998244353ull * 998244353ull);

    auto n = read<ull>(), k = read<ull>();
    auto res = solve({n, k});
    printf("%llu\n", res);

    fclose(stdin);
    fclose(stdout);
    return 0;
}

ull solve(const Config& config) {
    if (config.k == 1) {
        return config.n;
    }
    if (config.n > 1'000'000 && config.k == 2) {
        auto n = config.n;
        ull res = 1;
        {
            auto x = sqrt(n);
            auto y = static_cast<ull>(x);
            if ((1 + y) * (1 + y) == config.n) {
                return res * (y + 1);
            }
            if (y * y == config.n) {
                return res * y;
            }
            if (n <= 1) {
                return res;
            }
        }
        for (ull i = 2; i <= 100'000'000; i++) {
            while (n % (i * i) == 0){
                res *= i;
                n /= (i * i);
            }
            if (n % i == 0) {
                n /= i;
            }
            auto x = sqrt(n);
            auto y = static_cast<ull>(x);
            if ((1 + y) * (1 + y) == config.n) {
                return res * (y + 1);
            }
            if (y * y == config.n) {
                return res * y;
            }
            if (i > n) {
                return res;
            }
        }
    }
    if (config.k >= 60) {
        return 1;
    }

    auto pow = [](ull a, ull p) {
        ull res = 1;
        while (p) {
            if (p & 1) {
                res *= a;
            }
            a *= a;
            p >>= 1;
        }
        return res;
    };

    constexpr uint mxp[8] = {59, 37, 29, 25, 23, 21, 19, 18}; // 2~9

    ull res = 1;

    for (ull i = 2; i < 10; i++) {
        if (config.k > mxp[i - 2]) {
            return res;
        }
        if (config.n % pow(i, config.k) == 0) {
            res = i;
        }
    }

    constexpr ull MAX = 1'000'000'000'000'000'000ull;

    for (ull i = 10; i <= 1'000'000; i++) {
        if (pow(i, config.k) > MAX || pow(i, config.k) > config.n) {
            return res;
        }
        if (config.n % pow(i, config.k) == 0) {
            res = i;
        }
    }
    return res;
}