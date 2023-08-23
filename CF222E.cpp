//
// Created by kibi on 23-8-23.
//
#include <bits/stdc++.h>
using namespace std;

int main(){

    static const int Mod = 1000000007, M = 52;

    class Tools{
    public:
        static void read(int &x){
            int s = 0, w = 1, c = ::getchar();
            while(c < '0' || '9' < c){
                if(c == '-'){
                    w = -1;
                }
                c = ::getchar();
            }
            while('0' <= c && c <= '9'){
                s = s * 10 + c - '0';
                c = ::getchar();
            }
            x = s * w;
        }

        static void read(long long &x){
            long long s = 0, w = 1, c = ::getchar();
            while(c < '0' || '9' < c){
                if(c == '-'){
                    w = -1;
                }
                c = ::getchar();
            }
            while('0' <= c && c <= '9'){
                s = s * 10 + c - '0';
                c = ::getchar();
            }
            x = s * w;
        }

        static int getchar(){
            int c = ::getchar();
            while(!('a' <= c && c <= 'z' || 'A' <= c && c <= 'Z')){
                c = ::getchar();
            }
            return 'a' <= c && c <= 'z' ? c - 'a' + 1 : c - 'A' + 27;
        }
    };

    class Matrix{
        int x, y;
        vector<vector<int>> data;

    public:
        Matrix(int x, int y, const int *data):x(x), y(y), data(x, vector<int>(y)){
            for(int i = 0; i < x; i++){
                for(int j = 0; j < y; j++){
                    this->data[i][j] = data[i * y + j];
                }
            }
        }

        int operator [](const int &pos){
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
                        tmp[i][j] = (int)(((long long)tmp[i][j] + (long long)data[i][k] * b.data[k][j]) % Mod);
                    }
                }
            }
            data = tmp;
        }
    };

    auto get = Tools::getchar;

    long long n;
    int m, k;
    Tools::read(n), Tools::read(m), Tools::read(k);

    static int Res[M + 5], Base[(M + 5) * (M + 5)];

    for(int i = 0; i < m; i++){
        Res[i] = 1;
    }

    for(int i = 0; i < m; i++){
        for(int j = 0; j < m; j++){
            Base[i * m + j] = 1;
        }
    }

    for(int i = 1; i <= k; i++){
        int a, b;
        a = get() - 1, b = get() - 1;
        Base[a * m + b] = 0;
    }

    Matrix res(1, m, Res), base(m, m, Base);

    n--;

    while(n){
        if(n & 1){
            res *= base;
        }
        base *= base;
        n >>= 1;
    }

    int ans = 0;

    for(int i = 0; i < m; i++){
        ans = (int)(((long long)ans + res[i]) % Mod);
    }

    printf("%d\n", ans);

}