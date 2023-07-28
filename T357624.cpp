//
// Created by kibi on 23-7-27.
//
#include <bits/stdc++.h>
using namespace std;

const int N = 10000000;

void read(int&);

int main(){
    static char s[N+5];
    int c = getchar(), cnt = 0;
    while(c != '\n'){
        s[++cnt] = char(c);
        c = getchar();
    }

    int m;
    read(m);

    static bool flag[N/2 + 5];
    for(int i = 1; i <= m; i++){
        int l, r;
        read(l), read(r);
        flag[l] ^= 1;
    }

    int b = 1;
    bool y = false;
    for(int i = 1; i <= cnt && i > 0; i+=b){
        if(!y && (i<=cnt/2 && flag[i] || i > cnt/2 && flag[cnt+1-i])){
            i = cnt+1-i;
            b*=-1;
        }
        printf("%c", s[i]);
        if(y && (i<=cnt/2 && flag[i] || i > cnt/2 && flag[cnt+1-i])){
            i = cnt + 1 - i;
            b *= -1;
        }
        if(i == (cnt/2 + cnt%2) || i == (cnt/2 + 1)){
            y = true;
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
    while('0' <= c && c <= '9'){
        s = s * 10 + c - '0';
        c = getchar();
    }
    x = s * w;
}