//
// Created by kibi on 24-10-6.
//
#include <bits/stdc++.h>
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

class Config {
public:
    uint n, w;
    vector<uint> arr;
};

uint solve(const Config&);

int main() {
    auto n = read<uint>(), w = read<uint>();

    Config config{n , w, vector<uint>(13)};

    vector<uint> arr(n);

    uint mx = 0;

    for (auto &i : arr) {
        i = read<uint>();
        config.arr[i - 1]++;
        mx = max(i, mx);
    }

    config.n = mx;

    printf("%u\n", solve(config));
    return 0;
}

void update(uint &a, uint b) {
    a = a == -1 ? b : max(a, b);
}

uint solve(const Config& config) {
    vector<vector<uint>> f(config.n + 1, vector<uint>(1 << config.n, -1));
    f[0][0] = 0;
    for (uint i = 1; i <= config.n; i++) {
        f[i][0] = config.w;
    }
    for (uint i = 1; i <= config.n; ++i) {
        for (uint j = 0; j < (1 << config.n); j++) {
            if (f[i - 1][j] != -1) {
                update(f[i][j], f[i - 1][j]);
            }
            for (uint k = 0; k < config.n; k++) {
                if (j & (1 << k)) {
                    if (f[i][j ^ (1 << k)] != -1 && f[i][j ^ (1 << k)] >= config.arr[k]) {
                        update(f[i][j], f[i][j ^ (1 << k)] - config.arr[k]);
                    }
                    if (f[i - 1][j ^ (1 << k)] != -1) {
                        update(f[i][j], config.w - config.arr[k]);
                    }
                }
            }
        }
        if (f[i][(1 << config.n) - 1] != -1) {
            return i;
        }
    }
}