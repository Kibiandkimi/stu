//
// Created by kibi on 2022/7/22.
//
#include <bits/stdc++.h>
using namespace std;
long long p, k, s;
char c[1000005];
long long r[26];
int main(){
    scanf("%d %d", &p, &k);
    scanf("%s", c+1);
    s = p-k+1;
    for(int i = 1; i <= p; i++){
        int fi = i + p - 1;
        if(fi > p){
            fi -= p;
            r[c[fi]-'A'] += s;
        }
    }
    for(int i = 0; i <= 25; i++){
        printf("%lld\n", r[i]);
    }
}