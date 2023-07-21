//
// Created by kibi on 23-7-21.
//
#include <bits/stdc++.h>
using namespace std;

const int N = 100000, SqrtN = (int)sqrt(N);
const int Mod = 1000000007;

void read(int&);

int main(){
    int n;
    static int a[N+5], b[N+5], sum[N+5][SqrtN+5];

    read(n);
    for(int i = 1; i <= n; read(a[i++])){}
    for(int i = 0; i < n; read(b[i++])){}

    for(int i = 1; i <= SqrtN; i++){
        for(int j = 0; j < i; j++){
            sum[j][i] = b[j];
            for(int k = j+i; k < n; k+=i){
                sum[k][i] = (sum[k-i][i] + b[k]) % Mod;
            }
        }
    }

    for(int i = 1; i <= n; i++){
        long long c = 0;
        int j;
        for(j = 1; j <= min(i, SqrtN); j++){
            c = (c + (long long)a[i/j] * b[i%j]) % Mod;
        }
        for(int r; j <= i; j = r+1){
            r = i / (i / j);
            c = (c + (long long)a[i/j] * sum[i%j][i/j]) % Mod;
        }
        printf("%lld\n", c);
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