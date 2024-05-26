//
// Created by kibi on 23-10-1.
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

        using ll = long long;

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

        static vector<int> check(ll x, bool init = false){
            static bool base[60];
            if(init){
                int cnt = 0;
                while(x){
                    if(cnt == 60){
                        throw exception();
                    }
                    base[cnt++] = x & 1;
                    x >>= 1;
                }
                return {cnt};
            }

            static bool res[60];
            for(bool & re : res){
                re = x & 1;
                x >>= 1;
            }

            vector<int> ret;
            for(int i = 59; i >= 0; i--){
                if(res[i] > base[i]){
                    ret.emplace_back(i + 1);
                }else if(res[i] < base[i]){
                    return ret;
                }
            }
            ret.emplace_back(0);
            return ret;
        }
    };

    class Bcj{
    public:
        explicit Bcj(int id = 0):id(id), fa(this){}
        Bcj(int id, Bcj *fa):id(id), fa(fa){}

        int id;
        Bcj *fa;

        Bcj* find(){
            if(this != fa){
                fa = fa->find();
            }
            return fa;
        }
    };

    auto read = Tools::read;
    auto check = Tools::check;
    using ll = long long;

    int n, m, q;
    ll V;
    read(n), read(m), read(q), Tools::read_ll(V);

    Bcj bcj[n * 61];

    for(int i = 0; i < 61; i++){
        for(int j = 0; j < n; j++){
            bcj[i * n + j] = (Bcj){j + 1, bcj[i * n + j].fa};
        }
    }

    check(V, true);
    for(int i = 0; i < m; i++){
        static int u, v;
        static long long w;
        read(u), read(v), Tools::read_ll(w);
        auto res = Tools::check(w);
        for(auto j : res) {
            bcj[j * n + u - 1].find()->fa = bcj[j * n + v - 1].find();
        }
    }

    while(q--){
        static int u, v;
        static bool flag;
        read(u), read(v);
        flag = false;
        for(int i = 0; i < 61; i++){
            if(bcj[i * n + u - 1].find() == bcj[i * n + v - 1].find()){
                flag = true;
                printf("Yes\n");
                break;
            }
        }
        if(flag){
            continue;
        }
        printf("No\n");
    }
}