//
// Created by kibi on 2022/7/22.
//
#include <bits/stdc++.h>
using namespace std;
int Q;
int n, m;
int c[105];
int d[10005];
int main(){
    scanf("%d", &Q);
    for(int i = 1; i <= 100; i++){
        c[i] = i*i;
    }
    while(Q--){
        scanf("%d %d", &n, &m);
        memset(d, 0x3f, n*sizeof (int));
        for(int i = 1; i <= m; i++){
            int t = c[i];
            d[t] = 1;
            for(int j = t; j <= n; j++){
                d[j] = min(d[j], d[j-t]+1);
            }
        }
        printf("%d\n", d[n]);
    }
}