//
// Created by kibi on 23-9-28.
//
#include <bits/stdc++.h>
using namespace std;

int main(){

    const int Max = 1000000000;

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

        static int pow(int a, int b){
            int res = 1;
            while(b){
                if(b & 1){
                    if((long long)res * a > Max){
                        return -1;
                    }else{
                        res *= a;
                    }
                }
                b >>= 1;
                if(!b){
                    break;
                }else{
                    if((long long)a * a > Max){
                        return -1;
                    }else{
                        a = a * a;
                    }
                }
            }
            return res;
        }
    };

    auto read = Tools::read;

    int a, b;
    read(a), read(b);

    printf("%d\n", Tools::pow(a, b));
}