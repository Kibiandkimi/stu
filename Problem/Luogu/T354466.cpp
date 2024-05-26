//
// Created by kibi on 23-7-21.
//
#include <bits/stdc++.h>
using namespace std;

const int N = 5000, M = 5000;
const int Mod = 998244353;

void read(int&);

void calc(int n, const int *p, int (*f)[N+5]);
int get(int (*f)[M+5], int x, int _x, int y, int _y);

int main(){

    int n, m;
    static int a[N+5], b[M+5], p_a[N+5], p_b[M+5], f_a[N+5][N+5], f_b[N+5][N+5];

    read(n), read(m);

    for(int i = 1; i <= n; i++){
        read(a[i]);
        p_a[i] = i;
        while(--p_a[i] && a[p_a[i]] != a[i]);
    }
    for(int i = 1; i <= m; i++){
        read(b[i]);
        p_b[i] = i;
        while(--p_b[i] && b[p_b[i]] != b[i]);
    }

    calc(n, p_a, f_a);
    calc(m, p_b, f_b);

    long long ans = 0;

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= min(i-1, m); j++){
            ans = (ans + (long long)f_a[n][i] * f_b[m][j]) % Mod; // c, 没有Mod, 看半天
        }
    }

    //    if(ans < 0){
    //        return 0;
    //    }

    static int f[N+5][M+5], g[N+5][M+5], h[N+5][M+5];

    for(int i = 0; i <= n; i++){
        f[i][0] = 1;
    }
    for(int i = 0; i <= m; i++){
        f[0][i] = 1;
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(a[i] == b[j]){
                f[i][j] = (f[i][j] + get(f, p_a[i], i - 1, p_b[j], j - 1)) % Mod;
            }
            if(a[i] > b[j]){
                g[i][j] = get(f, p_a[i], i-1, p_b[j], j-1);
            }
            h[i][j] = (g[i][j] + get(h, p_a[i], i-1, p_b[j], j-1))%Mod;
            f[i][j] = (int)((( (long long)f[i][j] + f[i-1][j] + f[i][j-1] - f[i-1][j-1]) % Mod + Mod) % Mod);
            g[i][j] = (int)((( (long long)g[i][j] + g[i-1][j] + g[i][j-1] - g[i-1][j-1]) % Mod + Mod) % Mod);
            h[i][j] = (int)((( (long long)h[i][j] + h[i-1][j] + h[i][j-1] - h[i-1][j-1]) % Mod + Mod) % Mod);
        }
    }

    ans = (ans + h[n][m]) % Mod;

    printf("%lld\n", ans);

}

void calc(int n, const int *p, int (*f)[N+5]){
    for(int i = 1, t = 0; i <= n; i++){
        f[i][1] = p[i] ? t : ++t;
    }
    for(int j = 1; j < n; j++){
        for(int k = j+1; k <= n; k++){
            if(p[k]){
                f[k][j+1] = (f[k-1][j] - f[p[k]-1][j] + Mod) % Mod;
            }else{
                f[k][j+1] = f[k-1][j];
            }
            f[k][j+1] = (f[k][j+1] + f[k-1][j+1]) % Mod;
        }
    }
}

int get(int (*f)[M+5], int x, int _x, int y, int _y) {
    if(!x && !y){
        return f[_x][_y];
    }
    if(!x){
        return (f[_x][_y] - f[_x][y-1] + Mod) % Mod;
    }
    if(!y){
        return (f[_x][_y] - f[x-1][_y] + Mod) % Mod;
    }
    return int((((long long)f[_x][_y] - f[x-1][_y] - f[_x][y-1] + f[x-1][y-1]) % Mod + Mod) % Mod);
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