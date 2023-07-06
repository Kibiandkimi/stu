//
// Created by kibi on 22-10-25.
//
#include <bits/stdc++.h>
static const double inf = 1e20;
using namespace std;
int n, loc[155][2];
double g[155][155];
int vis[155];

int id;
void f(int u){
    vis[u] = id;
    for(int i = 1; i <= n; i++){
        if(g[u][i] < inf && !vis[i]){
            f(i);
        }
    }
}

double pow(double a){
    return a * a;
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d %d", &loc[i][0], &loc[i][1]);
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            static int t;
            scanf("%1d", &t);
            if((i<j && t)||i==j){
                g[i][j] = g[j][i] = sqrt(pow(loc[i][0]-loc[j][0]) + pow(loc[i][1] - loc[j][1]));
            }else if(!t){
                g[i][j] = g[j][i] = inf;
            }
        }
    }
    for(int i = 1; i <= n; i++){
        if(!vis[i]){
            id++;
            f(i);
        }
    }
    for(int k = 1; k <= n; k++){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                g[i][j] = min(g[i][k] + g[k][j], g[i][j]);
            }
        }
    }
    static double mxD[155], diaD[155];
    for(int i = 1; i <= n; i++){
        mxD[i] = 0;
        for(auto &j : g[i]){
            mxD[i] = max(mxD[i], j< inf ?j:0);
        }
        diaD[vis[i]] = max(diaD[vis[i]], mxD[i]);
    }
    double mx, mn = inf;
    for(int i = 1; i <= n; i++){
        for(int j = i+1; j <= n; j++){
            if(vis[i] != vis[j]){
                mx = max(max(diaD[vis[i]], diaD[vis[j]]), mxD[i] + sqrt(pow(loc[i][0]-loc[j][0]) + pow(loc[i][1] - loc[j][1])) + mxD[j]);
                mn = min(mn, mx);
            }
        }
    }
    printf("%.6lf", mn);
}