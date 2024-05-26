//
// Created by kibi on 23-7-28.
//
#include <bits/stdc++.h>
using namespace std;

const int Mod = 998244353, M = 1000000;

template<typename F>

void read(F&);

int main(){

    class Matrix{
    public:
        int x, y;
        vector<vector<int>> a;

        Matrix(const int x, const int y) : x(x), y(y) {
            a = vector<vector<int>>(x, vector<int>(y));
        }

        Matrix(const int x, const int y, const int *raw): x(x), y(y){
            a = vector<vector<int>>(x, vector<int>(y));
            for(int i = 0; i < x; i++){
                for(int j = 0; j < y; j++){
                    a[i][j] = raw[i*y+j];
                }
            }
        }

        Matrix operator*(const Matrix &b) const{
            Matrix res(x, b.y);
            for(int i = 0; i < x; i++){
                for(int j = 0; j < b.y; j++){
                    int mxk = min(y, b.x);
                    for(int k = 0; k < mxk; k++){
                        res.a[i][j] = (int)((res.a[i][j] + (long long)a[i][k] * b.a[k][j]) % Mod);
                    }
                }
            }
            return res;
        }


        void _t(Matrix &res, const Matrix &b, const bool flag = false) {
            //            static Matrix res(x, b.y);
            //            if(!flag){
            //                res = Matrix(x, b.y);
            //            }
            for(int i = 0; i < x; i++){
                for(int j = 0; j < b.y; j++){
                    int mxk = min(y, b.x);
                    res.a[i][j] = 0;
                    for(int k = 0; k < mxk; k++){
                        res.a[i][j] = (int)((res.a[i][j] + (long long)a[i][k] * b.a[k][j]) % Mod);
                    }
                }
            }
            //            memcpy()
            for(int i = 0; i < x; i++){
                for(int j = 0; j < b.y; j++){
                    a[i][j] = res.a[i][j];
                }
            }
        }


    };

    class Func{
    public:
        static int fib(long long k){
            if(k <= 2){
                return 1;
            }
            k -= 2;
            //            const int Base[2][2] = {{1, 1}, {1, 0}}, Ans[1][2] = {{1, 1}};
            //            TODO 如何传入二维数组
            const int Base[4] = {1, 1, 1, 0}, Ans[2] = {1, 1};
            Matrix ans(1, 2, Ans), base(2, 2, Base);
            Matrix res_ans(1, 2), res_base(2, 2);
            while(k){
                if(k&1){
                    ans._t(res_ans, base, true);
                }
                base._t(res_base, base, true);
                k >>= 1;
            }
            return ans.a[0][0];
        }

        static int inv_pow(int x){
            int s = 1, k = Mod-2;
            while(k){
                if(k&1){
                    s = (int)((long long)s * x % Mod);
                }
                x = (int)((long long)x * x % Mod);
                k >>= 1;
            }
            return s;
        }
    };

    //    freopen("t.in", "r", stdin);

    static int inv[M + 5];
    int T;
    read(T);

    inv[1] = 1;
    for(int i = 2; i <= M; i++){
        inv[i] = (int)((long long)(Mod-Mod/i) * (inv[Mod%i]) % Mod);
    }

    while(T--){
        long long n;
        int m;
        read(n), read(m);
        int ans = Func::fib(n+2), i = 0, tmp = 1;
        if(m == 1){
            ans = (ans - 1 + Mod) % Mod;
        }else while(i < m && i <= n-i+1){
//                TODO wait to understand again
                ans = (ans - tmp + Mod) % Mod;
                tmp = (int)( (long long)tmp *
                             ( (n + 1 - (i << 1)) % Mod ) % Mod *
                             ( (n - (i << 1)) % Mod ) % Mod *
                             inv[i+1] % Mod * Func::inv_pow((int)((n+1-i) % Mod)) % Mod );
                i++;
            }
        printf("%d\n", ans);
    }

    //    fclose(stdin);
}

template<typename F>

void read(F &x){
    F s = 0, w = 1, c = getchar();
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