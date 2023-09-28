//
// Created by kibi on 23-9-28.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
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

    int n, q;
    read(n), read(q);

    static int prime[6000005], cnt;
    static bool not_prime[100000000 + 5];

    for(int i = 2; i <= n; i++){
        if(!not_prime[i]){
            prime[++cnt] = i;
        }
        for(int j = 1; j <= cnt; j++){
            if((long long)i * prime[j] > n){
                break;
            }
            not_prime[i * prime[j]] = true;
            if(i % prime[j] == 0){
                break;
            }
        }
    }

    for(int i = 1; i <= q; i++){
        int x;
        read(x);
        printf("%d\n", prime[x]);
    }
}