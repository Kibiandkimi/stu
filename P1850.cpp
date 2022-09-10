//
// Created by kibi on 2022/9/9.
//
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2005, MAXV = 305;
int n, m, v, e, a[MAXN], b[MAXN];
double p[MAXN], d[MAXN][MAXN][2], g[MAXV][MAXV];
//struct node{
//    int v, w;
//};
//vector<node> r[MAXV];

void read(int &x);
void read(double &x);

int main(){
    read(n), read(m), read(v), read(e);
    for(int i = 1; i <= n; i++){
        read(a[i]);
    }
    for(int i = 1; i <= n; i++){
        read(b[i]);
    }
    for(int i = 1; i <= n; i++){
        read(p[i]);
        //        scanf("%lf", &p[i]);
    }

    memset(g, 0x43, sizeof g);
    for(int i = 1; i <= e; i++){
        int u, v, w;
        read(u), read(v), read(w);
        g[u][v] = g[v][u] = min((double)w, g[u][v]);
    }
    for(int k = 1; k <= v; k++){
        for(int i = 1; i <= v; i++){
            for(int j = 1; j <= v; j++){
                g[i][j] = min(g[i][j], g[i][k]+g[k][j]);
            }
        }
    }
    for(int i = 1; i <= v; i++){
        g[i][0] = g[0][i] = g[i][i] = 0;
    }
    memset(d, 0x43, sizeof d);
    d[1][0][0] = d[1][1][1] = 0;
    for(int i = 2; i <= n; i++){
        d[i][0][0] = d[i-1][0][0] + g[a[i-1]][a[i]];
        int sj = min(m, i);
        for(int j = 1; j <= sj; j++){
            d[i][j][0] = min(d[i][j][0], min(d[i-1][j][0]+g[a[i-1]][a[i]], d[i-1][j][1]+g[a[i-1]][a[i]]*(1-p[i-1])+g[b[i-1]][a[i]]*p[i-1]));
            d[i][j][1] = min(d[i][j][1], min(d[i-1][j-1][0] + g[ a[i-1] ][ a[i] ]*(1-p[i]) + g[a[i-1]][b[i]]*p[i], d[i-1][j-1][1] + g[ a[i-1] ][ a[i] ] * (1-p[i]) * (1-p[i-1]) + g[ a[i-1] ][ b[i] ] * (1-p[i-1]) * (p[i]) + g[ b[i-1] ][ a[i] ] * p[i-1] * (1-p[i]) + g[ b[i-1] ][ b[i] ] * p[i-1] * p[i]));
        }
    }
    double ans = 10843961455707782;
    //    memset(&ans, 0x43, sizeof ans);
    for(int i = 0; i <= m; i++){
        ans = min(ans, min(d[n][i][0], d[n][i][1]));
    }
    printf("%.2lf", ans);
    return 0;
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
        if(c == '-'){
            w *= getchar();
        }
        c = getchar();
    }
    while('0'<=c&&c<='9'){
        s = s*10 + c-'0';
        c = getchar();
    }
    x = s*w;
}

void read(double &x){
    int s = 0, c = getchar();
    while(c < '0' || '9' < c){
        c = getchar();
    }
    if(c == '0'){
        if(getchar() != '.'){
            x = 0;
            return;
        }
        c = getchar();
    }else{
        while((c = getchar())<='9' && c >= '0' || c == '.'){}
        x = 1;
        return;
    }
    double w = 1;
    while('0'<=c&&c<='9'){
        w *= 0.1;
        s = s*10 + c-'0';
        c = getchar();
    }
    x = s*w;
    //    while(x > 1){
    //        x *= 0.1;
    //    }
}