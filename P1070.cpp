//
// Created by kibi on 2022/8/17.
//
//28pts
#include <bits/stdc++.h>
using namespace std;
int n, m, p;
int v[1005][1005], w[1005];
int d[1005];

int main(){
    scanf("%d %d %d", &n, &m, &p);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            scanf("%d", &v[i][j]);
        }
    }
    for(int j = 1; j <= m; j++){
        v[0][j] = v[n][j];
    }
    for(int i = 1; i <= n; i++){
        scanf("%d", &w[i]);
    }
    memset(d, 0xc0, sizeof d);
    //    for(int i = 1; i <= m; i++)
    //    {
    //        d[i] = 0;
    //    }
    d[0] = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 0; j < m; j++){
            if(d[j] != 0xc0){
                int s = 0;
                for(int k = 1; k <= p && j+k<=m; k++){
                    //            int loc = i+k-1;
                    s += v[(i+k-1)%n][k+j];
                    d[j+k] = max(d[j+k], d[j]+s-w[i]);
                }
            }
        }
    }
    printf("%d", d[m]);
}