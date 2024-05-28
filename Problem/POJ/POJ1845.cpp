//
// Created by Kibi on 24-5-28.
//
#include <tuple>
#include <cstdio>
#include <vector>
using namespace std;

int main(){
    auto read = [](int &x){
        int s = 0, w = 1, c = getchar();
        while(c < '0' || '9' < c){
            if(c == '-'){
                w = -1;
            }
            c = getchar();
        }
        while ('0' <= c && c <= '9'){
            s = s * 10 + c - '0';
            c = getchar();
        }
        x = s * w;
    };
    static int a, b;
    read(a), read(b);

    static vector<int> prime;
    static vector<bool> is_prime(a + 1, true);

    for(int i = 2; i <= a; i++){
        if(is_prime[i]){
            prime.emplace_back(i);
        }
        for(auto &j : prime){
            if(i * j > a){
                break;
            }
            is_prime[i * j] = false;
            if(i % j == 0){
                break;
            }
        }
    }

    static vector<tuple<int, int>> prime_factor;
    for(auto &i : prime){
        static int res;
        res = 0;
        while(a % i == 0){
            a /= i;
            res++;
        }
        res ? prime_factor.emplace_back(i, res) : void();
    }

    static const int Mod = 9901;

    static int ans = 1;

    for(auto [i, j] : prime_factor){
        static auto pow = [](int a, int p){
            int res = 1;
            a %= Mod;
            while(p){
                if (p & 1){
                    res = res * a % Mod;
                }
                p >>= 1;
                a = a * a % Mod;
            }
            return res;
        };

        ans = ans * (pow(i, j * b + 1) - 1) * pow(i - 1, Mod - 2) % Mod;
    }

    printf("%d\n", ans);

}