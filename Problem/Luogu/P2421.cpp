//
// Created by kibi on 23-8-11.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
    const int N = 15;

    class Tools{
    public:
        static void read(int &x){
            int s = 0, w = 1, c = getchar();
            while(c < '0' || '9' < c){
                if(c == '-'){[[unlikely]]
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

        static int exgcd(int a, int b, int &x, int &y){
            if(b == 0){
                x = 1, y = 0;
                return a;
            }
            int d = exgcd(b, a % b, x, y);
            int t = x;
            x = y;
            y = t - a/b * y;
            return d;
        }
    };

    class Data{
    public:
        int n{}, mn_ans;
        int c[N + 5]{}, p[N + 5]{}, l[N + 5]{};
        Data(){
            auto read = Tools::read;
            read(n);
            mn_ans = 0;
            for(int i = 1; i <= n; i++){
                read(c[i]), read(p[i]), read(l[i]);
                mn_ans = max(mn_ans, c[i]);
            }
        }
    };

    Data data;

    for(int ans = data.mn_ans; ans <= 1000000; ans++){
        bool flag = true;
        for(int i = 1; i < data.n; i++){
            for(int j = i+1; j <= data.n; j++){
                int a = data.p[i] - data.p[j], b = ans, c = data.c[j] - data.c[i], x, y;
                int d = Tools::exgcd(a, b, x, y);
                if(c % d){
                    continue;
                }
                b /= d, c /= d;
                b = abs(b);
                x = (x * c % b + b) % b;
                if(x <= data.l[i] && x <= data.l[j]){
                    flag = false;
                    break;
                }
            }
            if(!flag){
                break;
            }
        }
        if(flag){
            printf("%d\n", ans);
            break;
        }
    }
}