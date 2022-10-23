//
// Created by kibi on 2022/10/21.
//
#include <bits/stdc++.h>
using namespace std;

void read(int &x);

int main(){
    static int T;
    read(T);
    while(T--){
        static unordered_map<int, bool> h;
        h.clear();
        static int n;
        read(n);
        while(n--){
            static int t;
            read(t);
            if(!h[t]){
                printf("%d ", t);
                h[t] = true;
            }

        }
        printf("\n");
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