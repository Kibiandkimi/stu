//
// Created by kibi on 22-9-22.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
    //    freopen("t.in", "r", stdin);
    int n = 0, c = getchar(), d[55][55], s[55];
    while('A' <= c && c <= 'Z'){
        s[++n] = c;
        c = getchar();
    }
    memset(d, 0x3f, sizeof d);
    for(int i = 1; i <= n; i++){
        d[i][i] = 1;
    }
    for(int l = 1; l < n; l++){
        for(int i = 1, j = 1+l; j <= n; i++, j++){
            if(s[i] == s[j]){
                d[i][j] = min(d[i+1][j], d[i][j-1]);
            }else{
                for(int k = i; k < j; k++){
                    d[i][j] = min(d[i][j], d[i][k] + d[k+1][j]);
                }
            }
        }
    }
    printf("%d", d[1][n]);
    //    fclose(stdin);
}