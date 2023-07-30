//
// Created by kibi on 23-7-30.
//
#include <bits/stdc++.h>
using namespace std;

const int N = 300, M = 300;

void read(int&);

int main(){

    class Graph{
        int head[2*N]
    };

    int T;
    read(T);
    while(T--){
        int n, m;
        read(n), read(m);

        static int b[N + 5][M + 5];

        for(int i = 1; i < n; i++){
            for(int j = 1; j < m; j++){
                read(b[i][j]);
            }
        }

        static int a[N + 5][M + 5];

        for(int i = n; i >= 1; i--){
            for(int j = m; j >= 1; j--){
                a[i][j] = b[i][j] - a[i+1][j] - a[i][j+1] - a[i+1][j+1];
            }
        }


    }
}