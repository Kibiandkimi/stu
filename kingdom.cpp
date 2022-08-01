//
// Created by kibi on 2022/3/26.
//
#include <bits/stdc++.h>
using namespace std;
int n,m;
int a[1005][1005];
int ans[1005];
int sum;
int main(){
    freopen("kingdom.in", "r", stdin);
    freopen("kingdom.out", "w",stdout);
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            scanf("%d", &a[j][i]);
        }
    }
    for(int i = 1; i <= n; i++){
        scanf("%d", &ans[i]);
        int t = 0;
        for(int j = 1; j <= m; j++){
            t += a[i][j];
        }
        if(ans[i]){
            if (t>m/2){
                sum++;
            }
        }else{
            if(t<=m/2){
                sum++;
            }
        }
    }
    printf("%d", sum);
    fclose(stdin);
    fclose(stdout);
}