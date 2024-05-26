//
// Created by kibi on 2021/8/16.
//
#include <bits/stdc++.h>
using namespace std;
int t;
int main() {
    cin >> t;
    while (t--) {
        long long n, a, b, c, d, e;
        scanf("%lld %lld %lld %lld %lld %lld", &n, &a, &b, &c, &d, &e);
        if (n == 1) {
            printf("%lld %lld\n", d > e ? a : (e > d ? b : c), d > e ? a : (e > d ? b : c));
        } else if (d == e && e == 0) {
            printf("%lld %lld\n", n * c, n * c);
        } else if (e == 0) {
            printf("%lld %lld\n", a * min(n, d) + (n > d ? n - d : 0) * c, a + b * min(n - 1, e) + (n > e + 1 ? n - e - 1 : 0) * c);
        } else if (d == 0) {
            printf("%lld %lld\n", b + (n - 1) * c, b * min(n, e) + (n > e ? n - e : 0) * c);
        } else if (e == d) {
            printf("%lld %lld\n", max(b + a * min(n - 1, d) + (n > d + 1 ? n - d - 1 : 0) * c, c * n), min(a + b * min(n - 1, e) + (n > e + 1 ? n - e - 1 : 0) * c, c * n));
        } else {
            if (d > e) {
                printf("%lld %lld\n", max(b + a * min(n - 1, d) + (n > d + 1 ? n - d - 1 : 0) * c, a * (min(d - e, n)) + c * (max(n - d + e, (long long) 0))), a + b * min(n - 1, e) + (n > e + 1 ? n - e - 1 : 0) * c);
            } else {
                printf("%lld %lld\n", b + a * min(n - 1, d) + (n > d + 1 ? n - d - 1 : 0) * c, min(a + b * min(n - 1, e) + (n > e + 1 ? n - e - 1 : 0) * c, b * (min(e - d, n)) + c * (max(n - e + d, (long long) 0))));
            }
        }
    }
}