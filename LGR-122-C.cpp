//
// Created by kibi on 2022/10/3.
//
#include <bits/stdc++.h>

namespace raw {
    using namespace std;
    long long T;
    long long sub6;

    void read(long long &x);

    int main() {
        vector<long long> v;
        //    int a[105];
        read(T);
        while (T--) {
            long long m, q;
            read(m), read(q);
            sub6 = 0;
            v.reserve(m + 4);
            long long now = 0;
            for (int i = 1; i <= m; i++) {
                long long t;
                read(t);
                sub6 += (t == 1);
                v.push_back(t);
                now += t;
            }
            sort(v.begin(), v.end());
            long long Q[105], mx = 0;
            for (int i = 1; i <= q; i++) {
                read(Q[i]);
                mx = max(mx, Q[i]);
            }
            while (v.back() < mx) {
                v.push_back(now);
                now = now - v[v.size() - (m + 1)] + now;
            }
            long long d[mx + 5];
            d[0] = 1, d[1] = sub6;
            for (int i = 2; i <= mx; i++) {
                d[i] = 0;
                for (auto &j : v) {
                    if (j > i) {
                        break;
                    }
                    d[i] += d[i - j];
                }
            }
            for (int i = 1; i <= q; i++) {
                long long x = Q[i];
                //            read(x);
                if (x == 1) {
                    printf("%lld\n", sub6);
                    continue;
                } else {
                    printf("%lld\n", d[x]);
                }
            }
            vector<long long>().swap(v);
        }
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
}

namespace final{
//#include <bits/stdc++.h>
//    TODO unstable, need to opti
    using namespace std;
    const int mod = 998244353;
    unordered_map<long long, long long> f[1005];
    long long a[1005], sum[1005];

    void read(int &x);
    void read(long long &x);
    long long dfs(long long n, int m);

    int main(){

        int T;
        //    sum[0] = 0;
        read(T);
        while(T--){
            static int Q, n, cnt;
            read(n), read(Q);
            for(int i = 1; i <= n; i++){
                read(a[i]);
                sum[i] = sum[i-1] + a[i];
            }
            for(cnt = n+1; ; cnt++){
                a[cnt] = 0;
                for(int i = 1; i <= n; i++){
                    a[cnt] = a[cnt] + a[cnt - i];
                }
                sum[cnt] = sum[cnt - 1] + a[cnt];
                if(sum[cnt] < 0){
                    break;
                }
            }
            cnt--;
            while(Q--){
                static long long x;
                read(x);
                printf("%lld\n", dfs(x, cnt));
                for(int i = 1; i <= cnt; i++){
                    //                unordered_map<long long, long long> ().swap(f[i]);
                    f[i].clear();
                }
            }
        }
    }

    void read(int &x){
        int s = 0, w = 1, c = getchar();
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

    long long dfs(long long n, int m){
        if(n < 0 || n > sum[m]){
            return 0;
        }
        if(!(m && n)){
            return !n ? 1 : 0;
        }
        if(f[m].count(n)){
            return f[m][n];
        }
        return f[m][n] = (dfs(n, m-1) + dfs(n - a[m], m - 1)) % mod;
    }
}