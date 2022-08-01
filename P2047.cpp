//
// Created by kibi on 2021/10/13.
//
#include <bits/stdc++.h>
using namespace std;
// struct node{
//     int v;
//     long long w;
//     int i;
// };
int n,m;
long long dis[105][105];
// vector<long long> a[105];
long long a[105][105];
double as[105];
int main(){
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            dis[i][j] = dis[j][i] = 1e9;
        }
    }
    for(int i = 1; i <= m; i++){
        int u,v;
        long long w;
        scanf("%d %d %lld", &u, &v, &w);
        dis[u][v] = dis[v][u] = w;
        a[u][v] = a[v][u] = 1;
    }

    for(int k = 1; k <= n; k++){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                if(dis[i][k]==1e9&&dis[k][j]==1e9){
                    continue;
                }
                if(dis[i][k] + dis[k][j] < dis[i][j]){
                    dis[i][j] = dis[i][k] + dis[k][j];
                    a[i][j] = a[i][k] * a[k][j];
                    continue;
                }
                if(dis[i][k] + dis[k][j] == dis[i][j]){
                    a[i][j] += a[i][k] * a[k][j];
                }
            }
        }
    }
    for(int k = 1; k <= n; k++){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                if(i==j||j==k||k==i){
                    continue;
                }
                if(dis[i][k]+dis[k][j]==dis[i][j]){
                    as[k] += (1.0*a[i][k]*a[k][j])/a[i][j];
                }
            }
        }
    }
    for(int i = 1; i <= n; i++){
        printf("%.3lf\n", as[i]);
    }
}