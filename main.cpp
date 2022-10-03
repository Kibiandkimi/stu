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
//            now
        }

        while(q--){
            long long x;
            read(x);
            printf("%lld\n", sub6);
        }
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