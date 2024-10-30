//
// Created by kibi on 2022/11/6.
//
#include <bits/stdc++.h>
using namespace std;

class Point{
public:
    double s[2], d;
    static const int w = 2;
    static int n;
    static Point add(const Point &A, const Point &B){
        Point res{};
        for(int i = 0; i < w; i++){
            res.s[i] = A.s[i] + B.s[i];
        }
        return res;
    }
    static Point del(const Point &A, const Point &B){
        Point res{};
        for(int i = 0; i < w; i++){
            res.s[i] = A.s[i] - B.s[i];
        }
        return res;
    }
    void operator /= (const int &x){
        for(double & i : s){
            i /= x;
        }
    }
}pos[1005], ans;

double sin(double dis1, double dis2){
    return dis2!=0?dis1/sqrt(dis1*dis1 + dis2*dis2):1;
}

const double ST = 1000, delT =0.9995, eps = 1e-6;
const int Tim = 5000;

void SA(){
    static const int n = Point::n;
    static const int w = Point::w;
    static double v[2];
    static double t;
    t = ST;
    while(t > eps){
        for(int i = 0; i < w; i++){
            v[i] = 0;
            for(int j = 0; j < n; j++){
                v[i] += sin(pos[j].s[i] - ans.s[i], pos[j].s[!i] - ans.s[!i]) * pos[j].d;
            }
            //            v[i] /= n;
        }
        for(int i = 0; i < w; i++){
            ans.s[i] += t*v[i];
        }
        t *= delT;
    }
    for(int tim = 0; tim < Tim; tim++){
        for(int i = 0; i < w; i++){
            v[i] = 0;
            for(int j = 0; j < n; j++){
                v[i] += sin(pos[j].s[i] - ans.s[i], pos[j].s[!i] - ans.s[!i]) * pos[j].d;
            }
            //            v[i] /= n;
        }
        for(int i = 0; i < w; i++){
            ans.s[i] += t * v[i];
        }
    }
}

int Point::n;

int main(){
    static int n;
    scanf("%d", &n);
    Point::n = n;
    for(int i = 0; i < n; i++){
        static int t1, t2, t3;
        scanf("%d %d %d", &t1, &t2, &t3);
        pos[i].s[0] = t1, pos[i].s[1] = t2, pos[i].d = t3;
        ans = Point::add(ans, pos[i]);
    }
    ans /= n;
    SA();
    for(double i : ans.s){
        printf("%.3lf ", i);
    }

}

// 24-10-26
// gradient-descent

/*

#include <cctype>
#include <cmath>
#include <cstdio>
#include <sys/types.h>
#include <tuple>
#include <vector>

template<typename T>
using vec = std::vector<T>;

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

using Ball = std::tuple<double, double, uint>;

class Config {
public:
    uint n;
    vec<Ball> balls;
};

std::tuple<double, double> solve(const Config&);

int main() {
    auto n = read<uint>();
    Config config{n};
    config.balls.reserve(n);
    for (uint i = 0; i < n; i++) {
        auto x = read<int>(), y = read<int>();
        auto w = read<uint>();
        config.balls.emplace_back(x, y, w);
    }
    auto [x, y] = solve(config);
    printf("%.3lf %.3lf\n", x, y);
}

std::tuple<double, double> solve(const Config& config) {
    double now_x = 0.0, now_y = 0.0, step = 1000.0, dx = 1000.0, dy = 1000.0;
    while (fabs(dx) > 0.0001 || fabs(dy) > 0.0001) {
        dx = 0, dy = 0;
        for (auto &i : config.balls) {
            auto [x, y, w] = i;
            if (now_x == x && now_y == y) {
                continue;
            }
            dx += (x - now_x) / (sqrt(pow(fabs(x - now_x), 2) + pow(fabs(y - now_y), 2))) * w;
            dy += (y - now_y) / (sqrt(pow(fabs(x - now_x), 2) + pow(fabs(y - now_y), 2))) * w;
        }
        // printf("{%lf, %lf}, {%lf, %lf}\n", now_x, dx, now_y, dy);
        now_x += dx * step;
        now_y += dy * step;
        step *= 0.999;
    }
    return {now_x, now_y};
}

 */