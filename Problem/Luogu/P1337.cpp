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