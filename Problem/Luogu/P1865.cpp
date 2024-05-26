//
// Created by kibi on 23-8-9.
//
#include <bits/stdc++.h>
using namespace std;

int main(){

    const int M = 1000000;

    class Tools{
    public:
        static void read(int &x){
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
    };

    auto read = Tools::read;

    int n, m;

    read(n), read(m);

    static bool flag[M + 5];

    for(int i = 2; i <= m; i++){
        if(!flag[i]){
            int now = 2;
            while(i * now <= m){
                flag[i * now] = true;
                now++;
            }
        }
    }

    static int sum[M + 5];

    for(int i = 2; i <= m; i++){
        sum[i] = sum[i-1] + (!flag[i]);
    }

    while(n--){
        int l, r;
        read(l), read(r);
        if(l >= 1 && r <= m){
            printf("%d\n", sum[r]-sum[l-1]);
        }else{
            printf("Crossing the line\n");
        }
    }
}