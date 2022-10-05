#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;
unordered_map<long long, long long> f[1005];
long long a[1005], sum[1005];

void read(int &x);
void read(long long &x);
long long dfs(long long n, int m);

int main(){

    int T;
    sum[0] = 0;
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
            for(int i = 1; i <= n && a[cnt] <= (long long)1e18 && a[cnt] > 0; i++){
                a[cnt] = a[cnt] + a[cnt - i];
            }
            sum[cnt] = sum[cnt - 1] + a[cnt];
            if(sum[cnt] <= (long long)1e18 && sum[cnt] > 0){
                break;
            }
        }
        cnt--;
        while(Q--){
            static long long x;
            read(x);
            printf("%lld\n", dfs(x, cnt));
            for(int i = 1; i <= cnt; i++){
                unordered_map<long long, long long> ().swap(f[i]);
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
        return !n;
    }
    if(f[m].count(n)){
        return f[m][n];
    }
    return f[m][n] = (dfs(n, m-1), + dfs(n - a[m], m - 1)) % mod;
}