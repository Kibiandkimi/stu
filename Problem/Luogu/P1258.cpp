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
    uint s, a, b;
};

double solve(const Config&);

int main() {
    auto s = read<uint>(), a = read<uint>(), b = read<uint>();
    printf("%lf\n", solve({s, a, b}));
}

/*
 * (a + b) * (t1) = 2*(s1)
 *
 */

// TODO the calc is wrong
double solve(const Config &config) {
    auto t2 = 1.0 * config.s * config.b / (config.b * config.b + (config.b - config.a) * config.a);
    auto t1 = (config.s - config.b * t2) / config.a;
    return t1 * t2;
}
