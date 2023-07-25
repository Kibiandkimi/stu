//
// Created by kibi on 22-8-16.
//
#include <bits/stdc++.h>
using namespace std;
int n, m;
int a[60][60];
int d[120][60][60];

int main(){
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            scanf("%d", &a[i][j]);
        }
    }
    memset(d, -1, sizeof d);
    d[2][1][1] = 0;
    for(int k = 3; k < m+n; k++){
        for(int i = 1; i < m; i++){
            for(int j = i+1; j <= m; j++){
                int s = max(max(d[k-1][i][j], d[k-1][i-1][j]),max(d[k-1][i][j-1], d[k-1][i-1][j-1]));
                s = max(d[k][i][j], s);
                if(s == -1){
                    continue;
                }
                d[k][i][j] = s+a[k-i][i]+a[k-j][j];
            }
        }
    }
    printf("%d", d[m+n-1][m-1][m]);
}

// 2023/7/23

/*
#include <bits/stdc++.h>
using namespace std;

const int M = 50, N = 50;

void read(int&);

int main(){
    int m, n;
    static int v[M + 5][N + 5], f[M + N + 5][M + 5][M + 5];

    read(m), read(n);
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            read(v[i][j]);
        }
    }

    memset(f, 0xc0, sizeof f);

    int inf = f[0][0][0];

    f[2][1][1] = 0;

    for(int i = 3; i < m+n; i++){
        for(int j = 1; j < i-1; j++){
            for(int k = j+1; k < i; k++){
                int s = max(max(max(f[i-1][j][k], f[i-1][j-1][k]), f[i-1][j][k-1]), f[i-1][j-1][k-1]);
                if(s == inf){
                    continue;
                }
                f[i][j][k] = s + v[i-j][j] + v[i-k][k];
            }
        }
    }

    printf("%d\n", f[m+n-1][n-1][n]);

}

void read(int &x){
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
 * */