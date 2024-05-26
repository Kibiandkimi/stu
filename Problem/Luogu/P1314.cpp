//
// Created by kibi on 2022/10/22.
//
#include <bits/stdc++.h>
using namespace std;

void read(int &x);
void read(long long &x);

int main() {
    static int n, m, w[200005], v[200005], sec[200005][2], mn = INT_MAX, mx;
    static long long s;
    read(n), read(m), read(s);
    for (int i = 1; i <= n; i++) {
        read(w[i]), read(v[i]);
        mn = min(mn, w[i]), mx = max(mx, w[i]);
    }
    for (int i = 1; i <= m; i++) {
        read(sec[i][0]), read(sec[i][1]);
    }
    static int l = mn - 1, r = mx + 2;
    static long long ans = LONG_LONG_MAX;
    while (l <= r) {
        static int mid, bol[200005];
        static long long sum[200005], res;
        mid = (l + r) / 2;
        for (int i = 1; i <= n; i++) {
            sum[i] = ((bol[i] = bol[i - 1] + (w[i] >= mid)) == bol[i - 1] ? 0 : v[i]) + sum[i - 1];
            //            (w[i] >= mid) ? (sum[i] = sum[i-1] + v[i], bol[i] = bol[i-1] + 1) : (sum[i] = sum[i-1], bol[i] = bol[i-1]);
        }
        res = 0;
        for (int i = 1; i <= m; i++) {
            static int secL, secR;
            secL = sec[i][0], secR = sec[i][1];
            res += (sum[secR] - sum[secL - 1]) * (bol[secR] - bol[secL - 1]);
        }
        if (res > s) {
            l = mid + 1;
            res -= s;
        } else {
            r = mid - 1;
            res = s - res;
        }
        ans = min(res, ans);
    }
    printf("%lld", ans);
}

void read(int &x) {
    int s = 0, w = 1, c = getchar();
    while (c < '0' || '9' < c) {
        if (c == '-') {
            w = -1;
        }
        c = getchar();
    }
    while ('0' <= c && c <= '9') {
        s = s * 10 + c - '0';
        c = getchar();
    }
    x = s * w;
}

void read(long long &x) {
    long long s = 0, w = 1, c = getchar();
    while (c < '0' || '9' < c) {
        if (c == '-') {
            w = -1;
        }
        c = getchar();
    }
    while ('0' <= c && c <= '9') {
        s = s * 10 + c - '0';
        c = getchar();
    }
    x = s * w;
}


//2023/7/19

/*
 *
 * #include <bits/stdc++.h>
using namespace std;

const int N = 200000, M = 200000, W = 1000000;

void read(int&);
void read(long long&);

int main(){

    int n, m;
    long long s;
    read(n), read(m), read(s);

    class Mine{

        class Segment{
        public:
            int l, r;
        };

        int w[N+5], v[N+5], n, m;
        Segment seg[M + 5];

    public:
        void init(int _n, int _m){
            n = _n, m = _m;
            for(int i = 1; i <= _n; i++){
                read(w[i]), read(v[i]);
            }
            for(int i = 1; i <= _m; i++){
                read(seg[i].l), read(seg[i].r);
            }
        }

        long long check(int _w){
            static long long sum_v[N+5], sum_num[N+5];
            sum_v[0] = sum_num[0] = 0;
            for(int i = 1; i <= n; i++){
                if(w[i] < _w){
                    sum_v[i] = sum_v[i-1];
                    sum_num[i] = sum_num[i-1];
                }else{
                    sum_v[i] = sum_v[i-1] + v[i];
                    sum_num[i] = sum_num[i-1] + 1;
                }
            }
            long long res = 0;
            for(int i = 1; i <= m; i++){
                res += (sum_v[seg[i].r] - sum_v[seg[i].l-1]) * (sum_num[seg[i].r] - sum_num[seg[i].l-1]);
            }
            return res;
        }


    };

    static Mine mine;

    mine.init(n, m);

    int l = 0, r = W + 5;
    long long ans = 0;

    while(l <= r){
        int mid = (l+r)/2;
        long long res = mine.check(mid);
        if(res < s){
            r = mid-1;
        }else if(res > s){
            l = mid+1;
        }else{
            ans = res;
            break;
        }
        ans = abs(res-s) < abs(ans-s) ? res : ans;
    }

    printf("%lld", abs(s-ans));
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
        c = getchar();
    }
    while('0' <= c && c <= '9'){
        s = s * 10 + c - '0';
        c = getchar();
    }
    x = s * w;
}

void read(long long &x){
    long long s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
        if(c == '-'){
            w = -1;
        }
        c = getchar();
    }
    while('0' <= c && c <= '9'){
        s = s * 10 + c - '0';
        c = getchar();
    }
    x = s * w;
}
 *
 * */