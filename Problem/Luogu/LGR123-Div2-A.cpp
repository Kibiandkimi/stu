//
// Created by kibi on 2022/10/15.
//
#include <bits/stdc++.h>
using namespace std;

void read(int &x);

int main(){
    static int T, raw[2000005], sum[1000005];
    sum[0] = 0;
    read(T);
    int pos = 1;
    while(pos <= 1000000){
        static int num = 1, i = 1, times, tem;
        times = (int)log10(num) + 1;
        tem = num;
        while(times--){
            raw[pos + times] = tem % 10;
            tem /= 10;
        }
        pos = pos + (int)log10(num) + 1;
        i++;
        if(i > num){
            i = 1, num++;
        }
    }
    for(int i = 1; i <= 1000000; i++){
        sum[i] = sum[i-1] + raw[i];
    }
    while(T--){
        static int l, r;
        read(l), read(r);
        printf("%d\n", sum[r]-sum[l-1]);
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