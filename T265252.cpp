//
// Created by kibi on 2022/9/10.
//
#include <bits/stdc++.h>
using namespace std;
long long a, b, c;

long long f(long long k, long long x);

int main(){
    scanf("%lld %lld %lld", &a, &b, &c);
    if(a%2 && c%2==0){
        printf("1");
        return 0;
    }
    long long x = f(b, a);
    x = x&-x;
    printf("%lld", x);
}

long long f(long long k, long long x){
    if(k == 1){
        return (long long)pow(x, 2*c)^c;
    }
    long long t = (long long)pow(x, 2*c)^c;
    x = t&-t;
    return f(k-1, x);
}