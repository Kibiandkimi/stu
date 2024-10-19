//
// Created by kibi on 24-10-3.
//
#include <algorithm>
#include <array>
#include <bitset>
#include <cctype>
#include <cstdio>
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
    vector<ull> arr;
};

uint solve(const Config &);

int main() {
    freopen("divide.in", "r", stdin);
    freopen("divide.out", "w", stdout);

    auto n = read<uint>();
    Config config{n, vector<ull>(n)};
    for (auto &i : config.arr) {
        i = read<ull>();
    }
    printf("%u\n", solve(config));

    fclose(stdin);
    fclose(stdout);

    return 0;
}

uint solve(const Config &config) {
    constexpr uint MOD = 1'000'000'007;

    if (config.n <= 15) {
        auto pow = [](uint a, uint p) {
            uint res = 1;
            while (p--) {
                res *= a;
            }
            return res;
        };
        uint res = 0;
        for (uint i = 0, mxi = pow(2, config.n - 1); i < mxi; i++) {
            ull now = 1, pre = config.arr.front(), temp = i;
            for (uint j = 1; j < config.arr.size(); j++) {
                if (temp & 1) {
                    now = pre % MOD * now % MOD;
                    pre = config.arr[j];
                } else {
                    pre ^= config.arr[j];
                }
                temp >>= 1;
            }
            now = pre % MOD * now % MOD;
            res = static_cast<uint>((now + res) % MOD);
        }
        return res;
    }
    if (config.n <= 1000) {
        vector<ull> sub(config.n);
        vector<uint> f(config.n);
        sub[0] = config.arr.front();
        for (uint i = 1; i < config.n; i++) {
            sub[i] = sub[i - 1] ^ config.arr[i];
        }
        f[0] = config.arr.front() % MOD;
        for (uint i = 1; i < config.n; i++) {
            for (uint j = 1; j <= i; j++) {
                f[i] = (f[i] + (sub[i] ^ sub[j - 1]) % MOD * f[j - 1] % MOD) % MOD;
            }
            f[i] = (f[i] + sub[i]) % MOD;
        }
        return f.back();
    }
    if (all_of(config.arr.begin(), config.arr.end(), [](const ull &x) { return x == 0 || x == 1;})) {
        vector<array<ull, 2>> f(config.n, array<ull, 2>());
        f.front() = config.arr.front() ? array<ull, 2>{0, 1} : array<ull, 2>{1, 0};// 0 => 1 * 0   1 => 1 * 1
        for (uint i = 1; i < config.n; i++) {
            if (config.arr[i] == 0) {
                f[i] = {(f[i - 1][1] + f[i - 1][0]) % MOD, f[i - 1][1]};
            } else {
                f[i] = {f[i - 1][1], (f[i - 1][0] + f[i - 1][1]) % MOD};
            }
        }
        return f.back().back();
    }
    // ai * bi
    // a, b

    vector<ull> pw2(60);
    pw2[0] = 1;
    for (uint i = 1; i < 60; i++) {
        pw2[i] = pw2[i - 1] * 2 % MOD;
    }

    vector<ull> sum(config.n);
    sum.front() = config.arr.front();
    for (uint i = 1; i < config.n; i++) {
       sum[i] = sum[i - 1] ^ config.arr[i];
    }

    vector<ull> f(config.n);
    vector<array<array<ull, 60>, 2>> f2(config.n);
    f[0] = config.arr.front() % MOD;
    for (ull j = 0, temp = config.arr.front(); j < 60; j++) { // which bit
        f2[0][1][j] = (temp & 1 ? f[0] : 0) % MOD;
        f2[0][0][j] = (temp & 1 ^ 1 ? f[0] : 0) % MOD;
        temp >>= 1;
    }
    for (uint i = 1; i < config.n; i++) { // i
        ull temp = sum[i];
        f[i] = sum[i] % MOD;
        for (uint j = 0; j < 60; j++) {
            f[i] = (f[i] + f2[i - 1][!(temp & 1)][j] * pw2[j]) % MOD;
            temp >>= 1;
        }
        temp = sum[i];
        for (uint j = 0; j < 60; j++) { // which bit
            f2[i][1][j] = (f2[i - 1][1][j] + (temp & 1 ? f[i] : 0)) % MOD;
            f2[i][0][j] = (f2[i - 1][0][j] + (temp & 1 ^ 1 ? f[i] : 0)) % MOD;
            temp >>= 1;
        }
    }

    return f.back();
}