//
// Created by kibi on 23-7-5.
//
#include <bits/stdc++.h>
using namespace std;

const int S = 100, N = 100, M = 20000;

void read(int &x);
bool cmp(int a, int b);

class Castle{
public:
    int i, w[S+5], v[S+5];
};

int main(){
    int s, n, m;
    read(s), read(n), read(m);
    static Castle castle[N+5];
    for(int i = 1; i <= s; i++){
        for(int j = 1; j <= n; j++){
            read(castle[j].w[i]);
        }
    }

    for(int i = 1; i <= n; i++){
        castle[i].i = i;
        sort(castle[i].w+1, castle[i].w+s+1, cmp); // w升序排列
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= s; j++){
            castle[i].v[j] = j*castle[i].i;
        }
    }

    static int f[N+5][M+5];
    memset(f, 0, sizeof f);
    for(int i = 1; i <= n; i++){ // n:100 (1*10^2)
        for(int j = 1; j <= m; j++){ // m:20000 (2*10^4)
            for(int k = 1; k <= s; k++) { // s:100 (1*10^2)
                //            i：城堡 j：士兵 k：玩家
                if(j <= castle[i].w[k]*2){
                    f[i][j] = max(f[i][j], f[i-1][j]);
                    break;
                }
                f[i][j] = max(f[i][j], max(f[i - 1][j], f[i - 1][j - castle[i].w[k]*2 - 1] + castle[i].v[k]));
            }
        }
    }
    printf("%d", f[n][m]);
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

bool cmp(int a, int b){
    return a < b;
}