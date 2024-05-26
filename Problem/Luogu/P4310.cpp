//
// Created by kibi on 22-9-22.
//
#include <bits/stdc++.h>
using namespace std;
int n, d[35], ans = 1;
//vector<int> e[35];

void read(int &x);

int main(){
    read(n);
    for(int i = 1; i <= n; i++){
        int t, k = 1;
        read(t);
        for(int j = 0; j <= 33; j++){
            if((1<<j)&t) {
                k = max(k, d[j] + 1);
            }
        }
        for(int j = 0; j <= 33; j++){
            if((1<<j)&t){
                d[j] = max(k, d[j]);
                ans = max(ans, d[j]);
            }
        }
    }
    printf("%d", ans);
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
        if(c == '-'){
            w = -1;
        }
        c = getchar();
    }
    while('0'<=c && c<='9'){
        s = s*10 + c-'0';
        c = getchar();
    }
    x = s*w;
}