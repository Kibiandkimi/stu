//
// Created by kibi on 23-10-28.
//
#include <bits/stdc++.h>
using namespace std;

int main(){

    const int N = 1000000;

    class Tools{
    public:
        static int read_(bool *a){
            static auto judge = [](int c){return c == '0' || c == '1';};
            int c = getchar();
            while(!judge(c)){
                c = getchar();
            }
            int cnt = 0;
            while(judge(c)){
                a[cnt++] = (bool)(c - '0');
                c = getchar();
            }
            return cnt;
        }
    };

    bool data[N + 5];
    int n = Tools::read_(data);

    long long ans, base = 0;
    for(int i = 0; i < n - 1; i++){
        if(data[i] == data[i + 1]){
            base++;
        }
    }

    ans = (long long)n * (n + 1) / 2 * base;

    for(int i = 1; i < n - 1; i++){
        bool flag1 = (data[i] == data[i - 1]), flag2 = (data[i] == data[i + 1]);
        if(flag1){
            ans -= n - i;
        }else{
            ans += n - i;
        }

        if(flag2){
            ans -= i + 1;
        }else{
            ans += i + 1;
        }
    }
    if(n > 1) {
        if (data[0] == data[1]){
            ans -= 1;
        }else{
            ans += 1;
        }
        if(data[n - 1] == data[n - 2]){
            ans -= 1;
        }else{
            ans += 1;
        }
    }

    printf("%lld\n", ans);
}