//
// Created by kibi on 23-11-8.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
    static int Mod = 1000000007;
    using ll = long long;

    auto read = [](initializer_list<int*> x){
        auto read = [](int &x){
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
        };

        for(auto &i : x){
            read(*i);
        }
    };

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
        x = (x + y) >= Mod ? x + y - Mod : x + y;
    };

    static auto sub = [](int x, int y){
        return (int)((ll)x * y % Mod);
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

        Matrix operator * (const Matrix &b){
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

        pair<int, int> size(){
            return {n, m};
        }

        int get(int x, int y){
            if(x >= n || y >= m || x < 0 || y < 0){
                throw runtime_error("Error with wrong index!");
            }
            return data[x][y];
        }
    };

    auto pow = [](Matrix a, ll p){
        auto siz = a.size();
        if(siz.first != siz.second){
            throw runtime_error("Error pow a not square matrix!");
        }
        Matrix res(siz.first);
        while(p){
            if(p & 1){
                res = res * a;
            }
            a = a * a;
            p >>= 1;
        }
        return res;
    };

    ll n;
    int m, k;
    read_ll({&n});
    read({&m, &k});

    vector<vector<int>> raw(1 << m, vector<int>(1 << m));
    for (int i = 0, j; i < (1 << m); ++i) {
        if (__builtin_popcount(i) > k) {
            continue;
        }

        j = i >> 1;
        raw[j][i] = 1;
        j = (i >> 1) | (1 << (m - 1));
        if (__builtin_popcount(j) <= k){
            raw[j][i] = 1;
        }
    }

    int ans = 0;
    auto res = pow(Matrix(raw), n);
    for (int i = 0; i < (1 << m); ++i) {
        add(ans, res.get(i, i));
    }

    printf("%d\n", ans);

}