//
// Created by kibi on 22-8-25.
//
#include <bits/stdc++.h>
using namespace std;
int T;
//long long a, b, c, x, y;

long long exgcd(long long a, long long b, long long &x, long long &y){
    long long d = a;
    if(b==0){
        x = 1, y = 0;
    }else{
        d = exgcd(b, a%b, y, x);
        y -= a/b*x;
    }
    return d;
}

int main(){
    scanf("%d", &T);
    while(T--) {
        long long a, b, c, x, y;
        scanf("%lld %lld %lld", &a, &b, &c);
        long long d = exgcd(a, b, x, y);
        if(c%d!=0){
            printf("-1\n");
        }else{
            x *= c/d, y *= c/d;
            long long p = b/d, q = a/d, k;
            if(x < 0){
                k = ceil((1.0-x)/p), x += p*k, y -= q*k;
            }else if(x >= 0){
                k = (x-1)/p, x -= p*k, y += q*k;
            }
            if(y > 0){
                printf("%lld %lld %lld %lld %lld\n", (y-1)/q+1, x, (y-1)%q+1, x+(y-1)/q*p, y);
            }else{
                printf("%lld %lld\n", x, y+q*(long long)ceil((1.0-y)/q));
            }
        }
    }
}

// 2023/8/9

/*

#include <bits/stdc++.h>
using namespace std;

int main(){
    class Tools{
    public:
        static void read(int &x){
            int s = 0, w = 1, c = getchar();
            while(c < '0' || '9' < c){
                if (c == '-'){
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

        static int gcd(int a, int b){
            if(b == 0){
                return a;
            }
            return gcd(b, a % b);
        }

        static int exgcd(int a, int b, long long &x, long long &y){
            if(!b){
                x = 1, y = 0;
                return a;
            }

            int d = exgcd(b, a % b, x, y);
            long long t = x;
            x = y;
            y = t - (a / b) * y;
            return d;
        }
    };

    auto read = Tools::read;

    int T;
    read(T);

    while(T--){
        int a, b, c;
        read(a), read(b), read(c);
        long long _x, _y; // x_1, y_1
        int gcd = Tools::exgcd(a, b, _x, _y);
        if(c % gcd != 0){
            printf("-1\n");
            continue;
        }

        long long x = _x * c / gcd, y = _y * c / gcd;

        long long d_x = b/gcd, d_y = a/gcd;

        long long l = ceil(((double)(1-x)/d_x)), r = floor((double)(y-1)/d_y);

        // x = x_1 + s * d_x
        // y = y_1 + s * d_y
        // l <= s <= r

        if(l > r){
            printf("%lld %lld\n", x + l * d_x, y - r * d_y);
        }else{
            printf("%lld %lld %lld %lld %lld\n", (r-l+1),
                   x + l * d_x,
                   y - r * d_y,
                   x + r * d_x,
                   y - l * d_y);
        }
    }
}

 * */