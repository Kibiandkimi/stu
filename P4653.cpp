//
// Created by kibi on 23-9-28.
//
#include <bits/stdc++.h>
using namespace std;

int main(){

    const int N = 100000;

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

        static void read_double(double &x){
            double s = 0, w = 1, c = getchar();
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
            if(c == '.'){
                double cnt = 0.1;
                c = getchar();
                while('0' <= c && c <= '9'){
                    s = s + (c - '0') * cnt;
                    c = getchar();
                    cnt *= 0.1;
                }
            }
            x = s * w;
        }
    };

    auto read = Tools::read;
    auto readD = Tools::read_double;

    int n;
    read(n);

    static double a[N + 5], b[N + 5];
    for(int i = 1; i <= n; i++){
        readD(a[i]), readD(b[i]);
    }

    sort(a + 1, a + 1 + n, greater<>{});
    sort(b + 1, b + 1 + n, greater<>{});

    static double ans;

    static bool visA[N + 5], visB[N + 5];
    for(int i = 1, j = 1; i <= n && j <= n; ){
        static double now_a, now_b;

        if(!visA[i]){
            now_a += a[i];
            visA[i] = true;
        }

        if(!visB[j]){
            now_b += b[j];
            visB[j] = true;
        }

        ans = max(ans, min(now_a, now_b) - (i + j));

        if(now_a > now_b){
            j++;
        }else{
            i++;
        }
    }

    printf("%.4lf", ans);
}