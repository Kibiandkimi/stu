//
// Created by kibi on 2022/8/3.
//
#include <bits/stdc++.h>
using namespace std;
long long n, d[1000005], cnt[1000005];
char c[1000005];
const int mod = 19930726;
long long k;

long long ksm(long long r, long long s){
    long long a = 1, b = r;
    if(r == 1){
        return 1;
    }
    while(s){
        if(s%2){
            a = a*b%mod;
            s--;
        }else {
            b = b * b % mod;
            s /= 2;
        }
    }
    return (a%mod);
}

int main() {
    scanf("%lld %lld %s", &n, &k, c + 1);
    int l = 0, r = -1;
    for (int i = 1; i <= n; i++) {
        if (i > r) {
            int j = 0;
            while (c[i - j] == c[i + j] && c[i + j] != 0) {
                j++;
            }
            j--;
            if (j >= 0) {
                l = i - j;
                r = i + j;
            }
            d[i] = j + 1;
        } else {
            if (d[l + r - i] + i > r) {
                int j = 0;
                while (c[r + j] == c[i - (r - i) - j] && c[r + j] != 0) {
                    j++;
                }
                j--;
                d[i] = r + j - i + 1;
                if (j > 0) {
                    l = i - (r - i) - j;
                    r += j;
                }
            } else {
                d[i] = d[l + r - i];
                if (i + d[i] > n) {
                    d[i] = n - i;
                }
            }
        }
        cnt[d[i]*2-1]++;
    }
    long long sum = 0, ans = 1;
    for(int i = (int)n; i >= 1; --i){
        if(!(i%2)){
            continue;
        }
        sum += cnt[i];
        if(k >= sum){
            ans = (ans * ksm(i, sum))%mod;
            k -= sum;
        }else{
            ans = (ans * ksm(i, k))%mod;
            k -= k;
            break;
        }
    }
    if(k > 0){
        ans = -1;
    }
    printf("%lld", ans);
}