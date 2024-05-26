//
// Created by kibi on 23-8-13.
//
#include <bits/stdc++.h>
using namespace std;

int main(){

    const int MaxT = 1000, N = 10000000;

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

        static void calc_phi(int n, bool *not_prime, int *phi, int *prime){
            memset(not_prime, 0, sizeof (bool)*n);
            memset(phi, 0, sizeof (int)*n);
            not_prime = not_prime -1;
            phi = phi-1;
            prime = prime-1;
            int cnt = 0;
            not_prime[1] = true;
            phi[1] = 1;
            for(int i = 2; i <= n; i++){
                if(!not_prime[i]){
                    prime[++cnt] = i;
                    phi[i] = i-1;
                }
                for(int j = 1; j <= cnt && i * prime[j] <= n; j++){
                    not_prime[i * prime[j]] = true;
                    if(i % prime[j]){
                        phi[i * prime[j]] = phi[i] * phi[prime[j]];
                    }else{
                        phi[i * prime[j]] = phi[i] * prime[j];
                        break;
                    }
                }
            }
        }

        static int pow(int a, int p, int mod){
            int res = 1;
            while(p){
                if(p & 1){
                    res = (int)(((long long)res * a) % mod);
                }
                a = (int)(((long long)a * a) % mod);
                p >>= 1;
            }
            return res;
        }

        static int solve(int mod, const int *phi){
            if(mod == 1){
                return 0;
            }
            return pow(2, solve(phi[mod], phi)+phi[mod], mod);
        }
    };

    auto read = Tools::read;

    int T;

    read(T);

    int mxn = 0;
    static int question[MaxT + 5];

    for(int i = 1; i <= T; i++){
        read(question[i]);
        mxn = max(question[i], mxn);
    }

    static int phi[N+5], prime[N+5];
    static bool not_prime[N + 5];
    Tools::calc_phi(mxn, not_prime, phi, prime);

    for(int i = 1; i <= T; i++){
        printf("%d\n", Tools::solve(question[i], phi-1));
    }

}