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