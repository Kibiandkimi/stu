//
// Created by kibi on 2022/9/23.
//
#include <bits/stdc++.h>
using namespace std;
int T, n;
void read(int &x);

int main(){
    read(T);
    while(T--){
        read(n);
        printf("1\n");
        if(n == 1){
            continue;
        }
        for(int i = 2; i <= n; i++){
            printf("1 ");
            for(int j = 3; j <= i; j++){
                printf("0 ");
            }
            printf("1\n");
        }
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
    while('0'<=c && c<='9'){
        s = s*10 + c-'0';
        c = getchar();
    }
    x = s*w;
}