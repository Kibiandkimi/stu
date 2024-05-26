//
// Created by kibi on 22-8-22.
//
#include <bits/stdc++.h>
using namespace std;
int n, m, t, k;
int v[4005][4005];
int d[4005][4005];
int dq[4005], loc_dq[4005];

int main(){
    scanf("%d %d %d %d", &n, &m, &k, &t);
    for(int i = 1; i <= k; i++){
        int x, y, w;
        scanf("%d %d %d", &x, &y, &w);
        v[x][y] = w;
    }
    for(int i = 1; i <= n; i++){
        int l = 1, r = 0;
        for(int j = 1; j <= t; j++){
            while (r >= l && dq[r] <= d[i-1][j]){
                r--;
            }
            dq[++r] = d[i-1][j];
            loc_dq[r] = j;
        }
        for(int j = 1; j <= m; j++) {
            while(loc_dq[l]<j-t&&r>=l){
                l++;
            }
            if(j+t<=m) {
                while (r >= l && dq[r] <= d[i - 1][j + t]) {
                    r--;
                }
                dq[++r] = d[i - 1][j+t];
                loc_dq[r] = j+t;
            }

            d[i][j] = dq[l]+v[i][j];
        }
    }
    int ans = 0;
    for(int i = 1; i <= m; i++){
        ans = max(ans, d[n][i]);
    }
    printf("%d", ans);
}