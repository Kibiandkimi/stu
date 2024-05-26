//
// Created by kibi on 23-8-26.
//
#include <bits/stdc++.h>
using namespace std;

int main(){

    const int Mod = 19260817;

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
                s = (s * 10 + c - '0') % Mod;
                c = getchar();
            }
            x = (s * w % Mod + Mod) % Mod;
        }

        static int exgcd(int a, int b, long long &x, long long &y){
            if(!b){
                x = 1, y = 0;
                return a;
            }
            int d = exgcd(b, a % b, x, y);
            long long t = x;
            x = y;
            y = t - a / b * y;
            return d;
        }
    };

    auto read = Tools::read;

    int a, b;
    read(a), read(b);

    if(!b){
        printf("Angry!\n");
        return 0;
    }

    long long x, y;
    Tools::exgcd(b, Mod, x, y);

    x = (x % Mod + Mod) % Mod;
    printf("%d\n", (int)(a * x % Mod));
}