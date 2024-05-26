//
// Created by kibi on 23-7-22.
//
#include <bits/stdc++.h>
using namespace std;

const int N = 5000;
const int Mod = 100000000;

void read(int&);

int main(){

    int n = 0, m = 0;
    static int x[N+5], y[N+5];

    while(true){
        int t;
        read(t);
        if(t == '.'){
            break;
        }
        x[++n] = t;
    }

    while(true){
        int t;
        read(t);
        if(t == '.'){
            break;
        }
        y[++m] = t;
    }

    static int pre_mf[N + 5], pre_f[N + 5], f[N + 5], mf[N + 5];

    int *i_pf = pre_f, *i_pmf = pre_mf, *i_f = f, *i_mf = mf;

    i_f[0] = 1;

    for(int i = 0; i <= n; i++){
        swap(i_pf, i_f);
        swap(i_pmf, i_mf);
        i_f[0] = i_pf[0];
        for(int j = 1; j <= m; j++){
            i_f[j] = 0;
            i_mf[j] = max(max(x[i] == y[j] ? i_pmf[j-1]+1 : -1, i_pmf[j]), i_mf[j-1]);
            if((x[i] == y[j] ? i_pmf[j-1]+1 : -1) == i_mf[j]){
                i_f[j] = (i_f[j] + i_pf[j-1]) % Mod;
            }else if(i_pmf[j-1] == i_mf[j] && i != 0){
                i_f[j] = (i_f[j] - i_pf[j-1] + Mod) % Mod;
            }
            if(i_pmf[j] == i_mf[j]){
                i_f[j] = (i_f[j] + i_pf[j]) % Mod;
            }
            if(i_mf[j-1] == i_mf[j]){
                i_f[j] = (i_f[j] + i_f[j-1]) % Mod;
            }
        }
    }

    printf("%d\n%d\n", i_mf[m], i_f[m]);

}

void read(int &x){
    int c = getchar();

    while((c < 'A' || 'Z' < c) && c != '.'){
        c = getchar();
    }
    x = c;
}