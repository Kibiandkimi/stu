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
    uint n, a;
    vector<bool> arr;
};

uint solve(const Config&);

int main() {
    auto n = read<uint>(), a = read<uint>() ;
    Config config{n, a, vector<bool>(n)};
    for (uint i = 0; i < n; i++) {
        auto temp = read<uint>();
        config.arr[i] = temp ? true : false;
    }
    printf("%u\n", solve(config));

    return 0;
}

uint solve(const Config& config) {
    vector<uint> sum(4);
    for (uint i = 0; i + 2 < config.n; i++) {
        sum[config.arr[i] + config.arr[i + 1] + config.arr[i + 2]]++;
    }
    sum[config.arr[config.n - 2] + config.arr[config.n - 1] + config.arr[0]]++;
    sum[config.arr[config.n - 1] + config.arr[0] + config.arr[1]]++;
    uint res = config.n * 3;
    uint temp = config.a;
    reverse(sum.begin(), sum.end());
    for (uint i = 0; i < 4; i++) {
        if (temp > 0) {
            res -= min(temp, sum[i]) * i;
            temp -= min(temp, sum[i]);
        }
    }
    return res;
}
