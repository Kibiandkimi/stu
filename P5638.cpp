//
// Created by kibi on 23-7-7.
//
#include <bits/stdc++.h>
using namespace std;

void read(int &x);
void read(long long &x);

int main(){
    int n, k;
    long long now = 0, s = 0, p = 1, all = 0;
    queue<long long> q;
    read(n), read(k);
    for(int i = 1; i <= k; i++){
        long long t;
        read(t);
        all += t;
        q.push(t);
        s += t;
    }
    now = s;
    for(int i = k+1; i < n; i++){
        long long t;
        read(t);
        all += t;
        now += t;
        q.push(t);
        now -= q.front();
        q.pop();
        s = max(s, now);
    }
    printf("%lld", (all-s));
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