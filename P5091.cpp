//
// Created by kibi on 22-8-25.
//
#include <bits/stdc++.h>
using namespace std;
long long a, m, b;

int main(){
    long long p;
    char c;
    bool flag = false;
    scanf("%lld %lld", &a, &m);
//    p = phi(m)
    long long t = p = m;
    for(int i = 2; i*i <= m; i++){
        if(t%i==0){
            p = p-p/i;
            while(t%i==0){
                t/=i;
            }
        }
    }
    if(t>1){
        p = p-p/t;
    }

//  b = input()
    while(!isdigit(c=getchar()));
    for(; isdigit(c);c=getchar()){
        b=b*10+c-'0';
        if(b >= p){
            flag = true;
            b %= p;
        }
    }
    if(flag){
        b+=p;
    }


    long long ans = 1;
//    int aa = 1;
    for(; b; b>>=1, a = a*a%m){
        if(b&1){
            ans = ans*a%m;
        }
    }
    printf("%lld", ans);

}