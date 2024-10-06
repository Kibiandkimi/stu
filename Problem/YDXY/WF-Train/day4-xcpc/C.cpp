//
// Created by kibi on 24-10-6.
//
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
    uint n, m;
    vector<uint> a, b;
};

unsigned long long solve(const Config&);

int main() {
    auto n = read<uint>(), m = read<uint>() ;
    Config config{n, m, vector<uint>(n), vector<uint>(m)};
    for (uint i = 0; i < n; i++) {
        config.a[i] = read<uint>();
    }
    for (uint i = 0; i < m; i++) {
        config.b[i] = read<uint>();
    }
    printf("%llu\n", solve(config));

    return 0;
}

unsigned long long solve(const Config& config) {
    unsigned long long res = 0;
    for (uint i = 0; i < config.n - 1; i++) {
        if (config.a[i] > config.a[i + 1]) {
            res += config.a[i] - config.a[i + 1];
        }else {
            res += config.a[i + 1] - config.a[i];
        }
    }
    for (uint i = 0; i < config.m - 1; i++) {
        if (config.b[i] > config.b[i + 1]) {
            res += config.b[i] - config.b[i + 1];
        }else {
            res += config.b[i + 1] - config.b[i];
        }
    }
    return res;
}
