//
// Created by kibi on 24-10-8.
//
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <sys/types.h>
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

class Config {
public:
    uint n, m;
    vector<uint> arr;
};

uint solve(const Config&);

int main() {
    freopen("xor.in", "r", stdin);
    freopen("xor.out", "w", stdout);

    auto n = read<uint>(), m = read<uint>();
    Config config{n, m, vector<uint>(n)};
    for (auto &i : config.arr) {
        i = read<uint>();
    }
    printf("%u\n", solve(config));

    fclose(stdin);
    fclose(stdout);
    return 0;
}

uint solve(const Config& config) {
    if (true || config.n <= 500) {
        auto arr = config.arr;
        sort(arr.begin(), arr.end());
        uint res = 0;
        for (uint i = 0; i < config.n; i++) {
            for (uint j = i + 1; j < config.n; j++) {
                for (uint k = j + 1; k < config.n; k++) {
                    auto dest = *lower_bound(arr.begin() + k, arr.end(), arr[i] ^ arr[j] ^ arr[k]);
                    if (dest == (arr[i] ^ arr[j] ^ arr[k])) {
                        res++;
                    }
                }
                if (res > config.m) {
                    return config.m;
                }
            }
        }
        return res;
    }
}