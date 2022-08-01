//
// Created by kibi on 2021/9/25.
//
#include <bits/stdc++.h>
using namespace std;
int n,m,a[15],b[15],c[15],d[15],f[10005];
int main(){
    cin >> n >> m >> c[0] >> d[0];
    for(int i = 1; i <= m; i++){
        scanf("%d %d %d %d", &a[i], &b[i], &c[i], &d[i]);
    }
    for(int i = c[0]; i <= n; i++){
        f[i] = i/c[0]*d[0];
    }
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= (a[i]/b[i]); j++){
            for(int k = n; k >= c[i]; k--){
                f[k] = max(f[k], f[k-c[i]]+d[i]);
            }
        }
    }
    cout << f[n];
}