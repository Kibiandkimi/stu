//
// Created by Kibi on 24-9-25.
//
// TODO WA 80pts
#include <cctype>
#include <cstdio>
#include <tuple>
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
    vector<tuple<int, int, int>> funcs;
};

double solve(const Config&);

int main() {
    auto T = read<uint>();
    while (T--) {
        const auto n = read<uint>();
        Config config{vector<tuple<int, int, int>>(n)};
        for (auto &i : config.funcs) {
            i = {read<int>(), read<int>(), read<int>()};
        }
        printf("%.4lf\n", solve(config));
    }
}

double f(double x, const tuple<int, int, int> &func) {
    return get<0>(func) * x * x + get<1>(func) * x + get<2>(func);
}

tuple<int, int, int> detect(double x, const vector<tuple<int, int, int>> &funcs) {
    auto res = funcs.front();
    double pre = f(x, funcs.front());
    for (auto &i : funcs) {
        if(pre < f(x, i)) {
            res = i;
            pre = f(x, i);
        }
    }
    return res;
}

double solve(const Config &config) {
    double step = -0.01;
    double x = 500;
    double sum = 0;
    for (uint i = 0; i < 100; i++) {
        auto [a, b, c] = detect(x, config.funcs);
        double dy = 2 * a * x + b;
        double u = x + step * ( dy + sum );
        sum += dy * 2;
        sum *= 0.9;
        u = min(1000.0, u);
        u = max(0.0, u);
        x = u;
    }
    step = -0.002;
    for (uint i = 0; i < 500; i++) {
        auto [a, b, c] = detect(x, config.funcs);
        double dy = 2 * a * x + b;
        double u = x + step * dy;
        u = min(1000.0, u);
        u = max(0.0, u);
        x = u;
    }
    step = -0.00002;
    for (uint i = 0; i < 1000; i++) {
        auto [a, b, c] = detect(x, config.funcs);
        double dy = 2 * a * x + b;
        double u = x + step * dy;
        u = min(1000.0, u);
        u = max(0.0, u);
        x = u;
    }
    step = -0.0000002;
    for (uint i = 0; i < 1000; i++) {
        auto [a, b, c] = detect(x, config.funcs);
        double dy = 2 * a * x + b;
        double u = x + step * dy;
        u = min(1000.0, u);
        u = max(0.0, u);
        x = u;
    }
    step = -0.000000002;
    for (uint i = 0; i < 1000; i++) {
        auto [a, b, c] = detect(x, config.funcs);
        double dy = 2 * a * x + b;
        double u = x + step * dy;
        u = min(1000.0, u);
        u = max(0.0, u);
        x = u;
    }
    step = -0.00000000002;
    for (uint i = 0; i < 1000; i++) {
        auto [a, b, c] = detect(x, config.funcs);
        double dy = 2 * a * x + b;
        double u = x + step * dy;
        u = min(1000.0, u);
        u = max(0.0, u);
        x = u;
    }
    step = -0.0000000000002;
    double res = 10000000.0;
    for (uint i = 0; i < 1000; i++) {
        auto [a, b, c] = detect(x, config.funcs);
        res = min(res, a * x * x + b * x + c);
        double dy = 2 * a * x + b;
        double u = x + step * dy;
        u = min(1000.0, u);
        u = max(0.0, u);
        x = u;
    }
    return res;
}