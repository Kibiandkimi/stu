//
// Created by Kibi on 24-9-22.
//
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <random>
#include <sys/types.h>
#include <tuple>
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
    vector<tuple<double, double>> points;
};

double solve(const Config&);

int main() {
    auto n = read<uint>();
    Config config{vector<tuple<double, double>>(n)};\
    for_each(config.points.begin(), config.points.end(), [](auto &p) {p = {read<int>(), read<int>()};});
    printf("%.4lf\n", solve(config));
}

mt19937 rnd(random_device{}());

double dis(tuple<double, double> a, tuple<double, double> b) {
    return sqrt(pow(get<0>(a) - get<0>(b), 2) + pow(get<1>(a) - get<1>(b), 2));
}

double calc(vector<tuple<double, double>> points) {
    auto c = rnd();
    for_each(points.begin(), points.end(), [c](auto &p) {p = {
        get<0>(p) * cos(c) - get<1>(p) * sin(c),
        get<0>(p) * sin(c) + get<1>(p) * cos(c),
    };});
    sort(points.begin(), points.end(), [](auto &p1, auto &p2) {return get<0>(p1) < get<0>(p2);});
    tuple<double, double> lst = make_tuple(rnd(), rnd());
    double dist = 1e9;
    for (auto &p : points) {
        dist = min(dist, dis(lst, p));
        lst = p;
    }
    return dist;
}

double solve(const Config& config) {
    double result = calc(config.points);
    for (auto i = 0; i < 10; i++) {
        result = min(result, calc(config.points));
    }
    return result;
}
