//
// Created by kibi on 2022/10/16.
//
#include <bits/stdc++.h>
using namespace std;

void read(int &x);
void readStr(char *c);

int main(){
    freopen("t.in", "r", stdin);
    static int n, nxt[1000005];
    static char c[1000005];
    read(n);
    readStr(c);
    nxt[1] = nxt[2] = 1;
    for(int i = 2; i <= n; i++){
        static int j = 1;
        while(j!=1 && (c[i] != c[j])){
            j = nxt[j];
        }
        j += (c[i] == c[j]);
        nxt[i+1] = j;
    }
    long long ans = 0;
    for(int i = 2; i <= n+1; i++){
        static int j;
        j = i;
        while(nxt[j] != 1){
            j = nxt[j];
        }
        if(nxt[i] != 1){
            nxt[i] = j;
        }
        ans += i - j;
    }
    printf("%lld", ans);
    fclose(stdin);
}

void readStr(char *c){
    int tem, i = 1;
    tem = getchar();
    while (tem < 'a' || tem > 'z') {
        tem = getchar();
    }
    while(tem != EOF) {
        c[i++] = (char) tem;
        tem = getchar();
    }
}

void read(int &x){
    int s = 0, c = getchar();
    while(c < '0' || '9' < c){
        c = getchar();
    }
    while('0' <= c && c <= '9'){
        s = s * 10 + c - '0';
        c = getchar();
    }
    x = s;
}