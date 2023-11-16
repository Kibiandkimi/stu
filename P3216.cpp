//
// Created by kibi on 23-11-15.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
    using ll = unsigned long long;
    static ll n, Mod;

    auto read_ll = [](initializer_list<ll*> x){
        auto read_ll = [](ll &x){
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
        };

        for(auto &i : x){
            read_ll(*i);
        }
    };

    static auto add = [](int &x, int y){
        x = (int)((x + y) % Mod);
    };

    static auto sub = [](int x, int y){
        return (int)((ll)x * y % Mod);
    };

    static auto pow = [](int a, int p){
        int res = 1;
        while(p){
            if(p & 1){
                res = sub(res, a);
            }
            a = sub(a, a);
            p >>= 1;
        }
        return res;
    };

    static auto nm_pow = [](ll a, ll p){
        ll res = 1;
        while(p){
            if(p & 1){
                res *= a;
            }
            a *= a;
            p >>= 1;
        }
        return res;
    };

    static auto abs = [](ll a){
        return (a + Mod) % Mod;
    };

    class Matrix{
        size_t n, m;
        vector<vector<int>> data;

    public:
        Matrix(size_t n, size_t m):n(n), m(m), data(n, vector<int>(m)){}
        explicit Matrix(size_t n):n(n), m(n), data(n, vector<int>(n)){
            for(int i = 0; i < n; i++){
                data[i][i] = 1;
            }
        }
        explicit Matrix(vector<vector<int>> &x):data(x), n(x.size()), m(x.front().size()){}

        Matrix operator * (const Matrix &b) const{
            if(m != b.n){
                throw runtime_error("Error sub Matrix with wrong length!");
            }
            Matrix res(n, b.m);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    for (int k = 0; k < m; k++) {
                        add(res.data[i][j], sub(data[i][k], b.data[k][j]));
                    }
                }
            }
            return res;
        }

        void operator *= (const Matrix &b){
            *this = (*this) * b;
        }

        pair<size_t, size_t> size(){
            return {n, m};
        }

        int& get(int x, int y){
            if(x >= n || y >= m || x < 0 || y < 0){
                throw runtime_error("Error with wrong index!");
            }
            return data[x][y];
        }
    };

    vector<vector<int>> raw_ans{{0}, {0}, {1}};
    static Matrix ans(raw_ans);

    auto calc = [](int p, ll b){
        vector<vector<int>> raw({{pow(10, p), 1, 1}, {0, 1, 1}, {0, 0, 1}});
        Matrix mat(raw), res(3);
        while(b){
            if(b & 1){
                res *= mat;
            }
            mat *= mat;
            b >>= 1;
        }
        return res;
    };

    read_ll({&n, &Mod});

    int i;
    for(i = 1; nm_pow(10, i) <= n; i++){
        ans = calc(i, nm_pow(10, i) - nm_pow(10, i - 1)) * ans;
    }

    ans = calc(i, n - nm_pow(10, i - 1) + 1) * ans;

    printf("%d\n", ans.get(0, 0));

}