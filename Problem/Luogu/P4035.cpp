//
// Created by kibi on 2022/11/6.
//
#include <bits/stdc++.h>
using namespace std;

class Point{
public:
    double s[10];
    static int w;
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
        for(int i = 0; i < w; i++){
            s[i] /= x;
        }
    }
}pos[11], ans;

double abs(const Point &u){
    static const int n = Point::w;
    double res = 0;
    for(int i = 0; i < n; i++){
        res += u.s[i] * u.s[i];
    }
    return sqrt(res);
}

double dis(const Point &u){
    static const int n = Point::w;
    double res = 0;
    for(int i = 0; i <= n; i++){
        res += abs(Point::del(u, pos[i]));
    }
    return res;
}

const double ST = 5000, delT =0.99995, eps = 1e-5;
const int Tim = 250000;

void SA(){
    static const int n = Point::w;
    static double v[15];
    static double t;
    t = ST;
    while(t > eps){
        static double avg;
        avg = dis(ans) / (n+1);
        for(int i = 0; i < n; i++){
            v[i] = 0;
            for(int j = 0; j <= n; j++){
                v[i] += (abs(Point::del(ans, pos[j])) - avg) * (pos[j].s[i] - ans.s[i]);
            }
            v[i] /= n+1;
        }
        for(int i = 0; i < n; i++){
            ans.s[i] += t*v[i];
        }
        t *= delT;
    }
    for(int tim = 0; tim < Tim; tim++){
        static double avg;
        avg = dis(ans) / (n+1);
        for(int i = 0; i < n; i++){
            v[i] = 0;
            for(int j = 0; j <= n; j++){
                v[i] += (abs(Point::del(ans, pos[j])) - avg) * (pos[j].s[i] - ans.s[i]);
            }
            v[i] /= n+1;
        }
        for(int i = 0; i < n; i++){
            ans.s[i] += t * v[i];
        }
    }
}

int Point::w;

int main(){
    static int n;
    scanf("%d", &n);
    Point::w = n;
    for(int i = 0; i <= n; i++){
        for(int j = 0; j < n; j++){
            scanf("%lf", &pos[i].s[j]);
        }
        ans = Point::add(ans, pos[i]);
    }
    ans /= n+1;
    SA();
    for(int i = 0; i < n; i++){
        printf("%.3lf", ans.s[i]);
        i == n-1 ? printf("\n") : printf(" ");
    }

}