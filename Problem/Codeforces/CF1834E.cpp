//
// Created by kibi on 23-10-5.
//
#include <bits/stdc++.h>
using namespace std;

int main(){

    using ll = long long;

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

        static void read_ll(ll &x){
            ll s = 0, w = 1, c = getchar();
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

        static ll gcd(ll a, ll b){
            if(!b){
                return a;
            }
            return gcd(b, a % b);
        }

        static ll lcm(ll a, ll b){
            return a / gcd(a, b) * b;
        }

    };

    auto read = Tools::read;
    auto read_ll = Tools::read_ll;
    auto gcd = Tools::gcd;
    auto lcm = Tools::lcm;

    int T;
    read(T);

    while(T--){
        int n;
        read(n);

        ll a[n];
        for(ll &i : a){
            read_ll(i);
        }

        set<ll> now, last, res;
        for(int i = n - 1; i >= 0; i--){
            swap(now, last);
            now.clear();
            for(ll j : last){
                ll r = lcm(j, a[i]);
                if(r < (ll)1e9){
                    now.insert(r);
                }
            }
            now.insert(a[i]);
            for(ll j : now){
                res.insert(j);
            }
        }

        ll ans = 0, lst = 0;
        for(ll i : res){
            if(i > lst + 1){
                ans = lst + 1;
                break;
            }else{
                lst = i;
            }
        }
        printf("%lld\n", ans ? ans : lst + 1);
    }
}