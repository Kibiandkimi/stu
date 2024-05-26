//
// Created by kibi on 2022/10/22.
//
#include <bits/stdc++.h>
using namespace std;

void read(int &x);

int main(){
    int l, s, t, m;
    read(l), read(s), read(t), read(m);
    if(s == t){
        int sum = 0;
        for(int i = 1; i <= m; i++){
            static int t;
            read(t);
            if(t % s == 0){
                sum++;
            }
        }
        printf("%d", sum);
        return 0;
    }
    static int raw[105], stone[105], d[20005];
    for(int i = 1; i <= m; i++){
        read(raw[i]);
    }
    sort(raw+1, raw+1+m);
    for(int i = 1; i <= m; i++){
        if(raw[i] - raw[i-1] > 90){
            stone[i] = stone[i-1]+90;
        }else{
            stone[i] = stone[i-1] + raw[i] - raw[i-1];
        }
    }
    if(l-raw[m] > 90){
        l = stone[m] + 90;
    }else{
        l = stone[m] + l - raw[m];
    }
    memset(d, 0x3f, sizeof d);
    d[0] = 0;
    for(int i = 1; i <= l+10; i++){
        static int pos = 1;
        while(i > stone[pos] && pos <= m){
            pos++;
        }
        for(int j = s; j <= t; j++){
            int pre = i-j;
            if(pre < 0){
                break;
            }
            d[i] = min(d[pre], d[i]);
        }
        d[i] += (stone[pos] == i);
    }
    int ans = 1e9;
    for(int i = 1; i <= 10; i++){
        ans = min(ans, d[i+l]);
    }
    printf("%d", ans);
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
        if(c == '-'){
            w=  -1;
        }
        c = getchar();
    }
    while('0' <= c && c <= '9'){
        s = s * 10 + c - '0';
        c = getchar();
    }
    x = s * w;
}