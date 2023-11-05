//
// Created by kibi on 23-11-4.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
    auto read = [](int &x){
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
    };

    int n, mod;
    read(n), read(mod);

    int raw_f1[n + 1], raw_f2[n + 1];
    int *f1 = raw_f1, *f2 = raw_f2;
    f1[0] = f1[1] = 0;
    f1[2] = 1;
    f2[0] = f2[1] = f2[2] = 0;
    for(int i = 3; i <= n; i++){
        swap(f1, f2);
        for(int j = 2; j <= i; j++){
            f1[j] = (f1[j - 1] + f2[i - j + 1]) % mod;
        }
    }

    int res = 0;
    for(int i = 0; i <= n; i++){
        res = (res + f1[i]) % mod;
    }

    res = (res << 1) % mod;

    printf("%d\n", res);
}