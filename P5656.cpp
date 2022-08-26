//
// Created by kibi on 22-8-25.
//
#include <bits/stdc++.h>
using namespace std;
int T;
//long long a, b, c, x, y;

long long exgcd(long long a, long long b, long long &x, long long &y){
    long long d = a;
    if(b==0){
        x = 1, y = 0;
    }else{
        d = exgcd(b, a%b, y, x);
        y -= a/b*x;
    }
    return d;
}

int main(){
    scanf("%d", &T);
    while(T--) {
        long long a, b, c, x, y;
        scanf("%lld %lld %lld", &a, &b, &c);
        long long d = exgcd(a, b, x, y);
        if(c%d!=0){
            printf("-1\n");
        }else{
            x *= c/d, y *= c/d;
            long long p = b/d, q = a/d, k;
            if(x < 0){
                k = ceil((1.0-x)/p), x += p*k, y -= q*k;
            }else if(x >= 0){
                k = (x-1)/p, x -= p*k, y += q*k;
            }
            if(y > 0){
                printf("%lld %lld %lld %lld %lld\n", (y-1)/q+1, x, (y-1)%q+1, x+(y-1)/q*p, y);
            }else{
                printf("%lld %lld\n", x, y+q*(long long)ceil((1.0-y)/q));
            }
        }
    }
}