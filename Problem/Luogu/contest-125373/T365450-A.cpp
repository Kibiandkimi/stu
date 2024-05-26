//
// Created by kibi on 23-8-13.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
    const int N = 1000000;

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

    int T;
    read(T);

    while(T--){
        int cnt_of_type;

        read(cnt_of_type);

        static int num_of_type[N + 5];

        for(int i = 1; i <= cnt_of_type; i++){

            read(num_of_type[i]);
        }

        long long ans = 0, now = num_of_type[1], pre_last = 0;

        for(int i = 2; i <= cnt_of_type; i++){
            if(now >= num_of_type[i]){
                ans += num_of_type[i];
                now -= num_of_type[i];
            }else{
                pre_last = ans; // 20pts -> 100pts
                ans += now;
                now = num_of_type[i] - now;
            }
        }

        now /= 2;

        ans += min(pre_last, now);

        printf("%lld\n", ans);
    }
}