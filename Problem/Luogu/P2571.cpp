//
// Created by Kibi on 24-9-24.
//
// TODO WA 80pts
#include <cctype>
#include <cmath>
#include <cstdio>
#include <future>
#include <sys/types.h>
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
    uint ax, ay, bx, by, cx, cy, dx, dy;
    uint p, q, r;
};

double solve(const Config &);

int main() {
    Config config{read<uint>(), read<uint>(), read<uint>(), read<uint>(), read<uint>(), read<uint>(), read<uint>(), read<uint>(), read<uint>(), read<uint>(), read<uint>()};
    auto ans = solve(config);
    printf("%.2lf\n", ans);
    return 0;
}

double solve(const Config &config) {
    auto [ax, ay, bx, by, cx, cy, dx, dy, p, q, r] = config;
    double a = (double)bx - ax, b = (double)by - ay, c = (double)dx - cx, d = (double)dy - cy;
    double lambda = 0.5, mu = 0.5;
    double step = -0.000001;
    double res = lambda * sqrt(pow(a, 2) + pow(b, 2)) / p +
        sqrt(pow(ax + lambda * a - cx - mu * c, 2) + pow(ay + lambda * b - cy - mu * d, 2)) / r +
            (1 - mu) * sqrt(pow(c, 2) + pow(d, 2)) / q;
    for (uint i = 0; i < 10000000; i++) {
        double du = sqrt(pow(a, 2) + pow(b, 2)) / p +
                           1.0 / (r * sqrt(pow(ax + lambda * a - cx - mu * c, 2) + pow(ay + lambda * b - cy - mu * d, 2))) *
                                   (2 * a * (ax + lambda * a - cx - mu * c) + 2 * b * (ay + lambda * b - cy - mu * d));
        double u = lambda + step * du;
        double dv = sqrt(pow(c, 2) + pow(d, 2)) / (mu - 1) / q +
                           1.0 / (r * sqrt(pow(ax + lambda * a - cx - mu * c, 2) + pow(ay + lambda * b - cy - mu * d, 2))) *
                                  (-2 * c * (ax + lambda * a - cx - mu * c) - 2 * d * (ay + lambda * b - cy - mu * d));
        double v = mu + step * dv;
        u = max(0.0, u);
        u = min(1.0, u);
        v = max(0.0, v);
        v = min(1.0, v);
        swap(u, lambda);
        swap(v, mu);
        res = min(res, lambda * sqrt(pow(a, 2) + pow(b, 2)) / p +
        sqrt(pow(ax + lambda * a - cx - mu * c, 2) + pow(ay + lambda * b - cy - mu * d, 2)) / r +
            (1 - mu) * sqrt(pow(c, 2) + pow(d, 2)) / q);
    }
    return res;
}
