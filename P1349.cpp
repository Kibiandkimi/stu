//
// Created by kibi on 23-8-10.
//
#include <bits/stdc++.h>
using namespace std;

int main(){

    class Matrix{
        int x, y, Mod;
        vector<vector<int>> data;

    public:
        Matrix(const int x, const int y, const int Mod):x(x), y(y), Mod(Mod), data(x, vector<int>(y)){}

        Matrix(const int x, const int y, const int Mod, const int *data):x(x), y(y), Mod(Mod), data(x, vector<int>(y)){
            for(int i = 0; i < x; i++){
                for(int j = 0; j < y; j++){
                    this -> data[i][j] = data[i*y + j] % Mod;
                }
            }
        }

        int get_x() const{
            return x;
        }

        int get_y() const{
            return y;
        }

        int operator [] (const int &pos) const{
            return data[pos/y][pos%y];
        }

        vector<vector<int>> tmp;

        void operator *= (const Matrix &b){
            tmp.resize(x);
            for(int i = 0; i < x; i++){
                tmp[i].resize(b.y);
                for(int j = 0; j < b.y; j++){
                    int mxk = min(y, b.x);
                    tmp[i][j] = 0;
                    for(int k = 0; k < mxk; k++){
                        tmp[i][j] = (int)((tmp[i][j] + (long long)data[i][k] * b.data[k][j]) % Mod);
                    }
                }
            }
            data = tmp;
        }
    };

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

        static void multi_read(int l, int *data){
            for(int i = 0; i < l; i++){
                read(data[i]);
            }
        }

        static int fib(long long k, int a1, int a2, int p, int q, const int Mod){
            const int Ans[2] = {a2, a1}, Base[4] = {p, 1, q, 0};
            Matrix ans(1, 2, Mod, Ans), base(2, 2, Mod, Base);
            while(k){
                if(k & 1){
                    ans *= base;
                }
                base *= base;
                k >>= 1;
            }
            return ans[0];
        }
    };

    //	auto read = Tools::read;

    int raw[6];

    Tools::multi_read(6, raw);

    auto [p, q, a1, a2, n, m] = raw;

    printf("%d\n", Tools::fib(n-2, a1, a2, p, q, m));

}