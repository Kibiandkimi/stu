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