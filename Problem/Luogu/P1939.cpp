//
// Created by kibi on 23-9-28.
//
#include <bits/stdc++.h>
using namespace std;

int main(){

    const int Mod = 1000000007;

    class Matrix{
        vector<vector<int>> data;

    public:
        Matrix(int x, int y, const int *data):data(x, vector<int>(y)){
            for(int i = 0; i < x; i++){
                for(int j = 0; j < y; j++){
                    this->data[i][j] = data[i * y + j];
                }
            }
        }
        Matrix() = default;

        void operator *= (const Matrix &b){
            const int x = (int)data.size(), y = (int)b.data[0].size(), z = (int)b.data.size();
            vector<vector<int>> res(x, vector<int>(y));
            for(int i = 0; i < x; i++){
                for(int j = 0; j < y; j++){
                    for(int k = 0; k < z; k++){
                        res[i][j] = (int)((res[i][j] + (long long)data[i][k] * b.data[k][j]) % Mod);
                    }
                }
            }
            data.swap(res);
        }

        int operator [] (const int &x){
            return data[x / data[0].size()][x % data[0].size()];
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

        static Matrix pow(Matrix raw, int p){
            const int Res[9] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
            Matrix res{3, 3, Res};
            while(p){
                if(p & 1){
                    res *= raw;
                }
                raw *= raw;
                p >>= 1;
            }
            return res;
        }
    };

    auto read = Tools::read;

    int T;
    read(T);

    while(T--){
        int n;
        read(n);
        if(n <= 3){
            printf("1\n");
            continue;
        }
        n -= 3;
        const int Raw[3] = {1, 1, 1}, Nxt[9] = {0, 0, 1,
                                                1, 0, 0,
                                                0, 1, 1};
        Matrix raw = {1, 3, Raw}, nxt = {3, 3, Nxt};
        raw *= Tools::pow(nxt, n);
        printf("%d\n", raw[2]);
    }
}