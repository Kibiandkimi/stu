//
// Created by kibi on 23-7-20.
//
#include <bits/stdc++.h>
using namespace std;

const int N = 1000000, Mod = 1000000007;

void read(int&);
void read(bool&);
long long pow_2(int);

int main(){
    int n, k;
    static bool a[N+5], b[N+5];

    read(n), read(k);

    for(int i = 1; i <= n; i++){
        read(a[i]);
    }

    int s = 0;

    for(int i = n; i >= 1; i--){
        if(a[i]){
            s++;
        }else{
            s--;
        }
        if(s>k){
            b[i] = true;
            s -= 2;
        }
        if(s < 0){
            s = 0;
        }
    }

    long long ans = 0, last = 1;
    int cnt = 0;

    for(int i = 1; i <= n; i++){
        if(b[i]){
            last = (pow_2(i-cnt) * last) % Mod;
            cnt = i;
            ans = (ans + last) % Mod;
        }
    }

    printf("%lld\n", ans);

}

long long pow_2(int p){
    long long res = 1;
    while(p--){
        res = (res * 2) % Mod;
    }
    return res;
}

void read(bool &x){
    int c = getchar();
    while(c != 'A' && c != 'B'){
        c = getchar();
    }
    x = (c == 'B');
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