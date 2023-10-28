//
// Created by kibi on 23-10-28.
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

        static int pow(int a, int p){
            int res = 1;
            while(p){
                if(p & 1){
                    res *= a;
                }
                a *= a;
                p >>= 1;
            }
            return res;
        }
    };

    auto read = Tools::read;

    int n;
    read(n);

    int stus[n][5];
    for(auto &i : stus){
        for(auto &j : i){
            read(j);
        }
    }

    int new_stus[n];
    for(int i = 0; i < n; i++){
        new_stus[i] = 0;
        for(int j = 0; j < 5; j++){
            new_stus[i] += (stus[i][j]) * Tools::pow(10, j);
        }
    }

    static map<int, int> mp;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 5; j++){
            int now = (new_stus[i] / Tools::pow(10, j)) % 10;
            for(int k = 0; k < 10; k++){
                if(now != k){
                    mp[new_stus[i] - now * Tools::pow(10, j) + k * Tools::pow(10, j)]++;
                    // printf("%d\n", new_stus[i] - now * Tools::pow(10, j) + k * Tools::pow(10, j));
                }
            }
        }
        // printf("%d\n", mp.size());
        for(int j = 1; j < 5; j++){
            int now = (new_stus[i] / Tools::pow(10, j - 1)) % 100;
            int l = now % 10, r = now / 10;
            for(int k = 1; k < 10; k++){
                int tl = (l + k) % 10, tr = (r + k) % 10;
                mp[new_stus[i] - now * pow(10, j - 1) + (tr * 10 + tl) * pow(10, j - 1)]++;
            }
        }
        // printf("%d\n", mp.size());
    }

    int ans = 0;
    for(auto &i : mp){
        if(i.second == n){
            ans++;
        }
    }

    printf("%d\n", ans);

}
