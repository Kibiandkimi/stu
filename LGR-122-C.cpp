//
// Created by kibi on 2022/10/3.
//
#include <bits/stdc++.h>
using namespace std;
long long T;
long long sub6;

void read(long long &x);

int main(){
    vector<long long> v;
    //    int a[105];
    read(T);
    while(T--){
        long long m, q;
        read(m), read(q);
        sub6 = 0;
        v.reserve(m+4);
        long long now = 0;
        for(int i = 1; i <= m; i++){
            long long t;
            read(t);
            sub6 += (t==1);
            v.push_back(t);
            now += t;
        }
        sort(v.begin(), v.end());
        long long Q[105], mx = 0;
        for(int i = 1; i <= q; i++){
            read(Q[i]);
            mx = max(mx, Q[i]);
        }
        while(v.back() < mx){
            v.push_back(now);
            now = now - v[v.size()-(m+1)] + now;
        }
        long long d[mx+5];
        d[0] = 1, d[1] = sub6;
        for(int i = 2; i <= mx; i++){
            d[i] = 0;
            for(auto &j : v){
                if(j > i){
                    break;
                }
                d[i] += d[i-j];
            }
        }
        for(int i = 1; i <= q; i++){
            long long x = Q[i];
            //            read(x);
            if(x == 1) {
                printf("%lld\n", sub6);
                continue;
            }else{
                printf("%lld\n", d[x]);
            }
        }
        vector<long long>().swap(v);
    }
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