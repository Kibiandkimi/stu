//
// Created by Kibi on 24-9-22.
//
#include <algorithm>
#include <cctype>
#include <cmath>
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
    uint n;
};

uint solve(const Config&);

// n = x * log_10(x) + 1

int main() {
    auto n = read<uint>();
    Config config{n};
    printf("%d\n", solve(config));
    return 0;
}

uint solve(const Config &config) {
    auto n = config.n;

    auto check = [n](uint x) {
        return x * log10(x) + 1 >= n;
    };

    uint l = 1, r = config.n;
    while (l < r) {
        uint mid = (l + r) / 2;
        if (check(mid)) {
            r = mid;
        }else {
            l = mid + 1;
        }
    }
    return l;
}
