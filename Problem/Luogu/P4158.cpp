//
// Created by Kibi on 24-4-14.
//
#include <bits/stdc++.h>
using namespace std;


int main(){
    auto read = [](int &x){
        int c = getchar(), s = 0, w = 1;
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

    auto read_single = [](int &x){
        int c = getchar();
        while(c < '0' || '9' < c){
            c = getchar();
        }
        x = c - '0';
    };

    int n, m, t;
    read(n), read(m), read(t);

    int data[n][m], f[n][m][t + 1];
    for(auto &i : data){
        for(auto &j : i){
            read_single(j);
        }
    }

    memset(f, 0, sizeof f);

    for(int id = 0; id < n; id++){
        auto nd = data[id]; // now data
        auto nf = f[id]; // now f
        for(auto &j : nf[0]){
            j = 1;
        }
        nf[0][0] = 0;
        for(int j = 1; j < m; j++){
            for(int nt = 1; nt <= t; nt++) { // now t
                static int nr, nb; // num red, num blue
                nr = nb = 0;
                for (int k = j; k > 0; k--) {
                    nr += !nd[k], nb += nd[k];
                    nf[j][nt] = max(nf[j][nt], nf[k - 1][nt - 1] + max(nr, nb));
                }
                nr += !nd[0], nb += nd[0];
                nf[j][nt] = max(nf[j][nt], max(nr, nb));
            }
        }
    }

    int f2[n][t + 1];
    memset(f2, 0, sizeof f2);
    for(int i = 0; i <= t; i++){
        f2[0][i] = f[0][m - 1][i];
    }
    for(int i = 1; i < n; i++){ // now n
        for(int j = 1; j <= t; j++){ // now t
            for(int k = 0; k <= j; k++){
                f2[i][j] = max(f2[i][j], f2[i - 1][k] + f[i][m - 1][j - k]);
            }
        }
    }

    printf("%d\n", f2[n - 1][t]);
}