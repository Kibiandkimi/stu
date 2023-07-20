#include <bits/stdc++.h>
using namespace std;

const int N = 100000;
const int Mod = 1000000007;

void read(int&);

int main(){
    int n;
    static int a[N+5], b[N+5], sum_2[N+5], sum_3[N+5];

    read(n);
    for(int i = 1; i <= n; read(a[i++])){}
    for(int i = 0; i < n; read(b[i++])){}

    int t = (n-1)/2;

    sum_2[0] = a[1] * b[0];
    for(int i = 1; i <= t; (sum_2[i] = (sum_2[i-1] + a[1] * b[i]) % Mod), i++){}

    for(int i = 1; i <= n; i++){
        static int tt;
        static long long c;
        tt = i/2, c = 0;
        for(int j = 1; j <= tt; j++){
            c = (c + a[i/j] * b[i % j]) % Mod;
        }
        c = (c + sum_2[(i-1)/2]) % Mod;
//        printf("%lld\n", c);
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