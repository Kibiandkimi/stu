//
// Created by kibi on 2021/8/12.
//
#include <bits/stdc++.h>
using namespace std;
int n,a[125][125],f[125][125],mx = -1e9;
int main(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            scanf("%d", &a[i][j]);
        }
    }
    for(int i = 1; i <= n; i++){
        for(int m = 0; m <= n-i; m++) {
            int t[125] = {}, f[125] = {};
            for (int j = 1; j <= n; j++) {
                for (int k = 1; k <= i; k++) {
                    t[j] += a[m+k][j];
                }
            }
            f[1] = t[1];
            for(int j = 2; j <= n; j++){
                f[j] = max(f[j-1]+t[j], t[j]);
                mx = max(f[j], mx);
            }
        }
    }
    cout << mx;
}