//
// Created by kibi on 22-8-28.
//
#include <bits/stdc++.h>
using namespace std;
int Q, a, b/*, k*/;
long long k;

bool getBoolean(int c) { return c < '0' || '9' < c; }

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(getBoolean(c)){
        if(c == '-'){
            w *= -1;
        }
        c = getchar();
    }
    while(!getBoolean(c)){
        s = s*10 + c-'0';
        c = getchar();
    }
    x = s*w;
}

//void read_k(int &x){
//    int s = 0, w = 1, c = getchar();
//    while(getBoolean(c)){
//        if(c == '-'){
//            w *= -1;
//        }
//        c = getchar();
//    }
//    while(!getBoolean(c)){
//        s = s*10 + c-'0';
//        c = getchar();
//        if(s>3){
//            x = 4;
//            while (!getBoolean(c)){
//                c = getchar();
//            }
//            return;
//        }
//    }
//
//    x = s*w;
//}

int gcd(int a, int b){
    if(a < b){
        swap(a, b);
    }
    while(a%b){
        int r = a%b;
        a = b, b = r;
//        r = a%b;
    }
    return b;
}

int main(){
    read(Q);
    while(Q--){
        read(a);
        read(b);
//        read_k(k);
        scanf("%lld", &k);
        if(k == 1){
            printf("%d\n", a);
        }else if(k == 2){
            printf("%d\n", b);
        }else {
            int r = gcd(a, b);
            if (a % 2 != b % 2) {
                long long s = (long long)a / r * b;
                if (s % 2 != b % 2) {
                    printf("%lld\n", s);
                }else{
                    printf("%lld\n", k==3?s:(long long)b);
                }
            }else{
                if(r % 2 != b % 2){
                    printf("%d\n", k==3?r:b);
                }else{
                    printf("%d\n", r);
                }
            }
        }
    }
}